import Student.Student;

class People {
	private int i;
	int j;
	protected int k;
	public int l;
}

class Student1 extends People {
	void access() {
		//Ĭ��Ȩ�ޣ��ڰ��ڲ��������м̳й�ϵ���Է���
		j = 0;
		k = 0;
	}
}

class Student2 {
	void access() {
		Student sunyu = new Student();
		
		//Ĭ��Ȩ�ޣ��ڰ��ⲿ�����ɷ���
		System.out.println(sunyu.i);
		
		//����Ȩ�ޣ��ڰ��ⲿ�����ɷ���
		System.out.println(sunyu.j);
	}
}

public class TestAccess extends Student {
	public static void main (String[] args) {
		People people = new People();
		
		//˽��Ȩ�ޣ�˽�г�Ա���ܿ������
		System.out.println(people.i);
		
		//Ĭ��Ȩ�ޣ����ڲ����Է���
		System.out.println(people.j);
		
		Student sunyu = new Student();
		
		//����Ȩ�ޣ��ڰ��ⲿ���м̳й�ϵ�����ɷ��ʣ�
		System.out.println(j);
		
		
	}
}
