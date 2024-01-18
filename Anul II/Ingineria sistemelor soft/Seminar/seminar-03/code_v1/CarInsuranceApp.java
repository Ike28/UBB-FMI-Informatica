
public class CarInsuranceApp
{
	public static void main(String[] args) 
	{
		Persoana p1 = new Persoana("cnp1","nume1");
		Persoana p2 = new Persoana("cnp2","nume2");
		Persoana p3 = new Persoana("cnp3","nume3");
		
		Autovehicul m1 = new Autovehicul("m1","renault","clio",2000,p1);
		System.out.println(m1);
		System.out.println("---------");
		System.out.println(p1);
		System.out.println("//////////");
		
		Autovehicul m2 = new Autovehicul("m2","renault","symbol",2010,p2);
		System.out.println(m2);
		System.out.println("---------");
		System.out.println(p2);
		System.out.println("//////////");
		
		m1.setProprietar(p3);
		System.out.println(m1);
		System.out.println("---------");
		System.out.println(p1);
		System.out.println(p3);
		System.out.println("//////////");
		
		p2.addToAutoDetinute(m1);
		System.out.println(m1);
		System.out.println("---------");
		System.out.println(p2);
		System.out.println(p3);
		System.out.println("//////////");
	}

}
