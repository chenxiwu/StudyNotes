
public class TestToString {
	public static void main(String[] args) {
		Dog dog = new Dog();
		
		System.out.println(dog);
	}
}

class Dog {
	public String toString() {
		return "I m Hot Dog!";
	}
}
