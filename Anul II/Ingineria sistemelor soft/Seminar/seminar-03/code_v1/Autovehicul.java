import java.util.Collections;
import java.util.HashSet;
import java.util.Set;

public class Autovehicul 
{
	private String nrInmatriculare;
	private String marca;
	private String model;
	private int anFabricatie;
	
	private Persoana proprietar;
	private Set<Persoana> soferi;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public Autovehicul(String nrInmatriculare, String marca, String model, Integer anFabricatie, Persoana proprietar)
	//pre: proprietar != null & ...
	{
		this.nrInmatriculare = nrInmatriculare;
		this.marca = marca;
		this.model = model;
		this.anFabricatie = anFabricatie;
		
		this.proprietar = proprietar;
		this.proprietar.basicAddToAutoDetinute(this);
		soferi = new HashSet<Persoana>();
	}

	public String getNrInmatriculare() 
	{
		return nrInmatriculare;
	}

	public void setNrInmatriculare(String nrInmatriculare) 
	{
		this.nrInmatriculare = nrInmatriculare;
	}

	public String getMarca() 
	{
		return marca;
	}

	public void setMarca(String marca) 
	{
		this.marca = marca;
	}

	public String getModel() 
	{
		return model;
	}

	public void setModel(String model) 
	{
		this.model = model;
	}

	public int getAnFabricatie() 
	{
		return anFabricatie;
	}

	public void setAnFabricatie(int anFabricatie) 
	{
		this.anFabricatie = anFabricatie;
	}
	
	public Persoana getProprietar()
	{
		return proprietar;
	}
	
	public void setProprietar(Persoana persoana)
	//pre: persoana != null & persoana != proprietar
	{
		Persoana proprietarVechi = this.proprietar;
		Persoana proprietarNou = persoana;
		proprietarVechi.basicRemoveFromAutoDetinute(this);
		proprietarNou.basicAddToAutoDetinute(this);
		this.basicSetProprietar(proprietarNou); //this.proprietar = proprietarNou; 
	}
	
	public Set<Persoana> getSoferi()
	{
		return Collections.unmodifiableSet(soferi);
	}
	
	public void addToSoferi(Persoana persoana)
	{
		this.basicAddToSoferi(persoana); //this.soferi.add(persoana); 
		persoana.basicAddToAutoConduse(this);
	}
	
	public void removeFromSoferi(Persoana persoana)
	{
		this.basicRemoveFromSoferi(persoana); //this.soferi.remove(persoana); 
		persoana.basicRemoveFromAutoConduse(this);
	}
	
	///////////////////////////////////////////////
	void basicSetProprietar(Persoana persoana)
	{
		this.proprietar = persoana;
	}
	
	void basicAddToSoferi(Persoana persoana)
	{
		this.soferi.add(persoana);
	}
	
	void basicRemoveFromSoferi(Persoana persoana)
	{
		this.soferi.remove(persoana);
	}
	
	/////////
	@Override
	public String toString()
	{
		return "Autovehicul: " + nrInmatriculare + ", proprietar " + proprietar.getCnp();
	}

}
