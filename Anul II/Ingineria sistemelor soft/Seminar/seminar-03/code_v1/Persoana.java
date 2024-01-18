import java.util.Collections;
import java.util.HashSet;
import java.util.Set;

public class Persoana 
{
	private String cnp;
	private String nume;
	
	private Set<Autovehicul> autoDetinute;
	private Set<Autovehicul> autoConduse; 
	
	////////////////////////////////////////
	public Persoana(String cnp, String nume)
	{
		this.cnp = cnp;
		this.nume = nume;
		
		autoDetinute = new HashSet<Autovehicul>();
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
	
	public Set<Autovehicul> getAutoDetinute()
	{
		return Collections.unmodifiableSet(autoDetinute);
	}
	
	public void addToAutoDetinute(Autovehicul autovehicul)
	//pre: autovehicul != null
	{
		Persoana proprietarVechi = autovehicul.getProprietar();
		Persoana proprietarNou = this;
		proprietarVechi.basicRemoveFromAutoDetinute(autovehicul); //proprietarVechi.autoDetinute.remove(autovehicul); 
		proprietarNou.basicAddToAutoDetinute(autovehicul); //proprietarNou.autoDetinute.add(autovehicul);   
		autovehicul.basicSetProprietar(proprietarNou);
	}
	
	//public void removeFromAutoDetinute(Auto autovehicul){}
	
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
	void basicAddToAutoDetinute(Autovehicul autovehicul)
	{
		this.autoDetinute.add(autovehicul);
	}
	
	void basicRemoveFromAutoDetinute(Autovehicul autovehicul)
	{
		this.autoDetinute.remove(autovehicul);
	}
	
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
		result += "\nAuto detinute:\n";
		for(Autovehicul m : autoDetinute)
			result += m + "\n";
		return result;
	}
}
