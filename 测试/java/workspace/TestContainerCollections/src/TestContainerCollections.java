import java.util.*;

public class TestContainerCollections {
	public static void main(String[] args) {
		List c = new LinkedList();
		for (int i=0; i<10; ++i) {
			c.add("A" + i);
		}		
		System.out.println(c);
		
		Collections.shuffle(c);
		System.out.println(c);
		
		Collections.swap(c, 1, 2);
		System.out.println(c);
		
		Collections.reverse(c);
		System.out.println(c);
		
		Collections.sort(c);
		System.out.println(c);
		
		int index = Collections.binarySearch(c, "A8");
		System.out.println(index);
	}
}
