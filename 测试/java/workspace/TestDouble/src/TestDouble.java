
public class TestDouble {
	public static void main(String[] args) {
		String s = "1,2;3,4,5;6,7,8";
		double[][] d;

		String[] stringFirst = s.split(";");		
		d = new double[stringFirst.length][];
		
		for (int i=0; i<stringFirst.length; ++i) {
			String[] stringSecond = stringFirst[i].split(",");
			d[i] = new double[stringSecond.length];
			
			for (int j=0; j<stringSecond.length; ++j) {
				d[i][j] = Double.parseDouble(stringSecond[j]);
			}
		}
		
		for (int i=0; i<d.length; ++i) {
			for (int j=0; j<d[i].length; ++j) {
				System.out.print(d[i][j] + " ");
			}
			System.out.println();
		}
		
	}
}
