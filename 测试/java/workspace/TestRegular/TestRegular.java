import java.util.regex.Matcher;
import java.util.regex.Pattern;


public class TestRegular {
	public static void main(String[] args) {
		/*
		//�ַ�ƥ��
		echo("���a".matches("..."));
		
		//����ƥ��
		echo("a123d33f".replaceAll("\\d", "-"));		
		
		//�ȱ�����ƥ���ٶȻ�졢�����ṩ�ܶ�ǿ��ķ���
		Pattern p = Pattern.compile("[a-z]{3}"); 
		Matcher m = p.matcher("fgs");
		echo(m.matches());
		*/
		/*
		echo("aaa".matches("a*"));
		echo("a".matches("a+"));
		echo("aaa".matches("a?"));
		echo("4782342487246".matches("\\d{3,100}"));
		echo("192.168.0.abc".matches("\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}"));
		*/
		/*
		echo("a".matches("[abc]"));
		echo("dd".matches("[^abc]"));
		echo("Z".matches("[a-zA-Z]"));
		echo("z".matches("[a-z]|[A-Z]"));
		echo("R".matches("[A-Z&&[RGB]]"));
		echo("\\".matches("\\\\"));
		*/
		/*
		//ƥ����h��ͷ���ַ�
		echo("hv".matches("^h.*"));
		//ƥ����lo��β���ַ�
		echo("hello".matches(".*lo$"));
		
		echo("hello world".matches("^h[a-z]{1,3}o\\b.*"));
		
		//�հ���
		echo(" 		   	\n".matches("^[\\s&&[^\\n]]*\\n$"));
		*/
		/*
		echo("aaa 8888c".matches(".*\\d{4}."));
		echo("aaa 8888c".matches(".*\\b\\d{4}."));
		echo("aaa8888c".matches(".*\\d{4}."));
		echo("aaa8888c".matches(".*\\b\\d{4}."));
		//ƥ��email��ַ
		echo("-1.d53_15@qq.com".matches("[\\w[.-]]+@[\\w[.-]]+\\.[\\w]+"));
		*/
		/*
		Pattern p = Pattern.compile("\\d{3,5}");
		String s = "139-5547-6538-22";
		Matcher m = p.matcher(s);
		echo(m.matches());
		
		m.reset();
		
		echo(m.find());
		echo(m.start() + "-" + m.end());
		echo(m.find());
		echo(m.find());
		echo(m.find());
		
		//��ͷ��ʼ����
		echo(m.lookingAt());
		*/
		
		/*
		Pattern p = Pattern.compile("java",Pattern.CASE_INSENSITIVE);
		Matcher m = p.matcher("java JAVA iloveJava you hate Java JaVa ass");
		
		echo(m.replaceAll("JAVA"));
		
		while(m.find()) {
			echo(m.group());		
		}
		
		int i = 0;
		StringBuffer sb = new StringBuffer(); 
		while(m.find()) {
			i++;
			if (i % 2 == 0) {
				m.appendReplacement(sb, "java");
			} else {
				m.appendReplacement(sb, "JAVA");
			}
		}
		m.appendTail(sb);
		
		echo(sb);
		*/
		/*
		Pattern p = Pattern.compile("(\\d{3,5})([a-z]{2})");
		Matcher m = p.matcher("123aa-34453bb-456dd-00");

		while(m.find()) {
			echo(m.group());
			echo(m.group(1));
			echo(m.group(2));
			echo("------");
		}
		*/

//		Pattern p = Pattern.compile("^/\\*(?!.*\\*/).*");
//		Matcher m = p.matcher("/* 1223273827 3ab */");
//		while (m.find()) {
//			echo(m.group());
//		}
		/*
		//Greedy:̰��ģʽ�������ܶ��ƥ��
		//Reluctant:��ǿģʽ����������ƥ��
		//Rossessive����ռģʽ��һ����ռ�������ַ���������ǰ���ַ���
		Pattern p = Pattern.compile("(.{3,10}+)[0-9]");
		String s = "aaaa5bbbb4";
		Matcher m = p.matcher(s);
		if (m.find()) {
			echo(m.start() + "-" + m.end());
		} else {
			echo("not match");
		}
		*/
		
		Pattern p = Pattern.compile("(?!a).{3}");
		Matcher m = p.matcher("444a66d");
		while (m.find()) {
			echo(m.group());
		}
	}
	
	private static void echo(Object o) {
		System.out.println(o);
	}
}
