# GIT学习笔记

#
*作者：SY*
*2016-9-22 10:41:48*
##

+ 文档
	+ BIT帮助文档：
		1. http://iissnan.com/progit/html/zh/ch1_0.html

+ 基本流程
	+ 配置GIT
	 	1. git config --global user.name "John Doe"
		2. git config --global user.email johndoe@example.com
	
	+ 创建本地仓库
		1. 创建项目文件夹
		2. git init 初始化本地仓库
		3. git add -A 添加所有修改的文件
		4. git commit -m +"简介"

	+ 创建远端仓库
		1. 登录 https://github.com/，点击"New repository"，创建远程仓库。
		2. 点击"Clone or download",复制HTTP地址，例如"https://github.com/xxx/xxx.git"
		3. 输入命令：git remote add origin + https://github.com/xxx/xxx.git，
		输入git remote -v，显示origin
	
	+ 推送到远端仓库
		1. 输入 git push origin master		
	
	+ 注意：创建远程地址，尽量使用HTTP地址，GIT地址经常挂掉，出现"fatal: Unable to look up github.com:dasuimao (port 9418) "错误。
			
+ 常用命令	
	+ push
		+ 添加远端主机名
			1. git remote add + "主机名" +"仓库"
	
	+ 删除远端主机名
		1. git remote rm + "主机名"
	
	+ 查看主机名
		1. git remote v
	
	+ commit
		1. git commit：默认调用vim编辑器，编写描述信息。
	
	+ git commit -m + "提交描述信息"：可以跳过编辑器。
	
	+ git commit -a -m + "提交描述信息"，可以跳过git add命令。
	
	+ status	
		+ git status：查看状态

	+ add
		+ git add -A 添加所有修改的文件
	
	+ log
		+ git log	查看日志

	+ clone
		+ git clone https://github.com/dasuimao/StudyNote.git 克隆一份远程仓库的拷贝到本地
	
	+ pull 
		+ git pull --rebase origin master 获取远程端最新的代码
		
	+ --rebase
		rebase 与 merge 很相似都是合并代码，merge操作会产生一个新的commit。而rebase则不会产生新的commit，
		他会将你的代码插入到服务器最新的commit的后面，看起来更加自然。

	+ tag 打标签
		1. 添加标签： git tag tagName
		2. 删除标签： git tag -d tagName
		3. 查看标签： git tag

+ 过滤器
	+ 忽略文件夹
		+ 新建文件 .gitignore
		+ 添加需要过滤的文件夹目录，如：/DTS-2500_HMI0030/OUTPUT/
		+ git add 添加该文件
		+ git commit

	+ 忽略文件
		+ 新建文件 .gitignore
		+ 添加需要过滤的文件类型，如：*.c 
		+ git add 添加该文件
		+ git commit

	+ 注意事项
	+ .gitignore只适用于尚未添加到git库的文件。如果已经添加了，则需用git rm移除后再重新commit。

+ 版本回退			
	+ 回滚到某一版本：
		1. git log，找到需要回退的 commit
		2. git reset --hard + <SHA>
				
+ 分支
	+ 新建分支
		1. git branch + <分支名>
	
	+ 切换分支
		1. git checkout + <分支名>
		
	+ 删除分支
		1. git branch -d + <分支名>
				如果当前分支已经执行过合并操作，通过上述命令可以直接删除。
				如果未执行过合并操作，执行上述命令，将提示是否删除。
			
		2. git branch -D + <分支名> 
				可以强制删除该分支。
			
		3. 注意：删除分支必须切换到其他分支，再执行删除命令。
				
	+ 合并分支
		+ git merge + <需要合并的分支>	
			merge是fast-forward的，即Git将master分支的指针直接移到dev的最前方。
			换句话说，如果顺着一个分支走下去可以到达另一个分支的话，那么Git在合并两者时，
			只会简单移动指针，所以这种合并成为快进式(Fast-forward),分支中的所有commit将会全部
			展现在master中。
		
		+ git merge --no-ff + <需要合并的分支> 
			会执行正常合并，在Master分支上生成一个新节点。为了保证版本演进的清晰，我们希望采用这种做法。
			但是生成的新节点没有名称，不方便查看当前合并的版本。
			步骤：
				1. 跳转到需要合并到的分支
				2. git merge --no-ff + <分支名>
				3. git push --force + origin
				由于合并后会产生冲突，可以手动修改冲突，也可以将本次变更强行推送至服务器。
				这样在服务器上的最后一次错误提交也彻底消失了。
				4. git push origin + <分支名>
				
		+ git merge --squash <需要合并的分支>
			用来把一些不必要commit进行压缩，比如说，你的feature在开发的时候写的commit很乱，
			那么我们合并的时候不希望把这些历史commit带过来，于是使用--squash进行合并，
			此时文件已经同合并后一样了，但不移动HEAD，不提交。需要进行一次额外的commit来“总结”一下，
			然后完成最终的合并。
			步骤：
				1. 跳转到需要合并到的分支
				2. git merge --squash + <分支名>
				3. git push --force + origin
				4. git push origin + <分支名>
					
		+ 注意：在合并分支时，通过 git checkout + <需要合并到的分支> ，再执行合并功能。
				
	+ 推送分支
		+ git push origin + <分支名>			
			1. 如果推送时出错，使用 `git pull --rebase origin master`先获取并合并服务器端的改动，再push操作。

+ 常见错误
	+ 推送到远端仓库错误？
		```C
		$ git push origin master
		To https://github.com/dasuimao/StudyNote.git
		! [rejected]        master -> master (non-fast-forward)
		error: failed to push some refs to 'https://github.com/dasuimao/StudyNote.git'
		hint: Updates were rejected because the tip of your current branch is behind
		hint: its remote counterpart. Integrate the remote changes (e.g.
		hint: 'git pull ...') before pushing again.
		hint: See the 'Note about fast-forwards' in 'git push --help' for details.
	
		```
		原因：由于本地推送时，本地仓库的代码比远端旧，因此推送会出现冲突。
		解决：
			1. 使用 `git pull --rebase origin master` 获取服务器最新的代码
			2. 再执行`git push origin master`即可。
			3. 如果在Pull时遇到冲突[同时修改一个文件的内容]，需要手动解决冲突。按照提示找到冲突的文件，修改后执行`git add + <冲突的文件>`，告诉git已经解决了冲突，再输入`git rebase --continue`继续执行。	 
		总结：工作流程是：修改代码→提交到本地仓库→拉取远程改动→推送
