import java.util.*;

public class TestContainerSet {
	public static void main(String[] args) {
		Set s1 = new HashSet();
		Set s2 = new HashSet();
		
		s1.add("a");
		s1.add("b");
		s1.add("c");
		
		s2.add("b");
		s2.add("d");
		
		//�������е�Ԫ��
		Set s3 = new HashSet(s1);
		s3.retainAll(s2);
		System.out.println(s3);
		
		//�������е�Ԫ��
		Set s4 = new HashSet(s1);
		s4.addAll(s2);
		System.out.println(s4);
	}
}
