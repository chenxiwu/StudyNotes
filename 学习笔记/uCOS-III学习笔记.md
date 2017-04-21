# uCOS-III学习笔记

#
*作者：SY*
*2016/12/19 17:03:52*
##


+ # 常见问题：
	+ 如果在某个任务中，使用了 `while(1);` 会不会阻塞其他进程，
	导致不能进行任务切换？ 
	+ 解答：
		这要看当前阻塞的任务优先级是否为最高。如果不是，则比他优先级高的任务仍然执行，比他优先级低的任务则不能执行。

	+ 总结：
		因此，在uCOS的每个任务中，都需要使用系统提供的延时函数，这样可以使比他优先级低的任务执行。

	+ 滴答定时器需不需要配置为最高优先级？ 
	+ 解答：
		根据实际情况，如果外设频繁进入中断，则建议配置为最高优先级。
		同时外设也需要配置为最高优先级。
		实测，调试CAN模块时，如果定时器为最高优先级，而CAN不是，
		则CAN模块收到大量数据包时，由于无法实时响应接收中断，
		导致进入硬件中断。如果将定时器设置为最低优先级，CAN设置为最高优先级，
		同样也会进入硬件中断。
		但不是由于CAN模块无法响应中断导致的，如果将定时器优先级调为最高，
		则不存在问题。可能uCOS不能切换任务导致的。

	+ uCOS怎么实现 `CPU_CRITICAL_ENTER()/CPU_CRITICAL_EXIT()` 
	嵌套使用？	
	+ 解答：
	```C	
	{
		CPU_SR_ALLOC();					(1)			
		CPU_CRITICAL_ENTER();			(2)		
		
		{
			CPU_SR_ALLOC();				(3)		
		CPU_CRITICAL_ENTER();			(4)				
		CPU_CRITICAL_EXIT();			(5)		
		}
		
		CPU_CRITICAL_EXIT();			(6)		
	}
	```
	执行语句(1)后，在堆栈中分配一个局部变量
	执行语句(2)后，最先运行 CPU_CRITICAL_ENTER() ，
	```C
	#define  CPU_CRITICAL_ENTER()  do { CPU_INT_DIS();        
		CPU_IntDisMeasStart(); }  while (0)
	```										
	该语句调用 CPU_INT_DIS()，
	```C									
	#define  CPU_INT_DIS()    do { cpu_sr = CPU_SR_Save(); 
							} while (0)
	```
	该语句调用 CPU_SR_Save()，
	```C
	CPU_SR_Save
			MRS     R0, PRIMASK                   ; Set prio int mask to mask all (except faults)
			CPSID   I
			BX      LR
	```
	第一句，首先读取 PRIMASK 寄存器的值，该寄存器只有1个位，
	可以手动设置该位为1，关闭所有可屏蔽中断。
	或者当所有可屏蔽异常关闭后，改位被硬件置1。
	因为当前我们没有关闭中断，所以该位为0，-> R0 = 0。 
	然后执行“CPSID   I”，关闭中断，
	PRIMASK将由硬件置1。
	执行语句(3)后，在堆栈中分配一个局部变量。
	执行语句(4)后，此时 PRIMASK = 1,-> R0 = 1; 
	再次执行“CPSID   I”，PRIMASK由硬件置1。
	执行语句(5)后，最先运行 CPU_CRITICAL_EXIT()，
	```C
	#define  CPU_CRITICAL_EXIT()   do { CPU_IntDisMeasStop(); 
		CPU_INT_EN();          }  while (0)
	```
	该语句调用 CPU_INT_EN(),
	```C
	#define  CPU_INT_EN()          do { CPU_SR_Restore(cpu_sr); 
									} while (0)
	```
	该语句调用 CPU_SR_Restore()，
	```C
	CPU_SR_Restore                             ; See Note #2.
	MSR     PRIMASK, R0
	BX      LR
	```
	首先，读取 R0 的值放入到 PRIMASK 中，由于此时 R0 的值为1，
	因此，PRIMASK = 1，
	中断仍然处于关闭状态。
	执行语句(6)后，最先运行 CPU_CRITICAL_EXIT()，	
	此时，读取 R0 的值放入到 PRIMASK中，由于此时 R0 的值为0，因此，PRIMASK = 1，中断处于打开状态。这样就实现了中断嵌套。
	不会因为内部临界段使用 CPU_CRITICAL_EXIT(); 而误打开中断。
	+ 总结：
	可以使用该语句实现中断嵌套，使用语法：							
	```C
	void  Task (void  *p_arg)
	{
	       CPU_SR_ALLOC();                     /* Allocate storage for CPU status register */
	           :
	           :
	       CPU_CRITICAL_ENTER();               /* cpu_sr = CPU_SR_Save();                  */
	           :
	           :
	       CPU_CRITICAL_EXIT();                /* CPU_SR_Restore(cpu_sr);                  */
	           :
	}
	```

	+ 在uCOS-III + enWin的项目中，经常遇到切换页面。进入硬件中断，
	但是在裸机中没有遇到这个问题。
	还有一个项目，使用uCOS-III，读取flash会出错。但是裸机中不会出错？
	解答：
		1. 由于任务中断延时太短，设置为周期1ms。而系统周期也是1ms。