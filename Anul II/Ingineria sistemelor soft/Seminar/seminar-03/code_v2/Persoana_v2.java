import java.util.Collections;
import java.util.HashSet;
import java.util.Set;

public class Persoana 
{
	private String cnp;
	private String nume;
	
	private Set<Autovehicul> autoConduse; 
	
	////////////////////////////////////////
	public Persoana(String cnp, String nume)
	{
		this.cnp = cnp;
		this.nume = nume;
		
		autoConduse = new HashSet<Autovehicul>();
	}

	public String getCnp()
	{
		return cnp;
	}

	public void setCnp(String cnp) 
	{
		this.cnp = cnp;
	}

	public String getNume() 
	{
		return nume;
	}

	public void setNume(String nume) 
	{
		this.nume = nume;
	}
	
	public Set<Autovehicul> getAutoConduse()
	{
		return Collections.unmodifiableSet(autoConduse);
	}
	
	public void addToAutoConduse(Autovehicul autovehicul)
	//pre: autovehicul != null
	{
		this.basicAddToAutoConduse(autovehicul); //this.autoConduse.add(autovehicul);
		autovehicul.basicAddToSoferi(this);
	}
	
	public void removeFromAutoConduse(Autovehicul autovehicul)
	//Pre: autovehicul != null
	{
		this.basicRemoveFromAutoConduse(autovehicul); //this.autoConduse.remove(autovehicul); 
		autovehicul.basicRemoveFromSoferi(this);
	}
	
	//////////////////////////////////////////////////
	void basicAddToAutoConduse(Autovehicul autovehicul)
	{
		this.autoConduse.add(autovehicul);
	}
	
	void basicRemoveFromAutoConduse(Autovehicul autovehicul)
	{
		this.autoConduse.remove(autovehicul);
	}
	
	/////////
	@Override
	public String toString()
	{
		String result = "Persoana: " + cnp;
		return result;
	}
}
