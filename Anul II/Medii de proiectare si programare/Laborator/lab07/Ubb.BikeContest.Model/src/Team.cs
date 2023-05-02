namespace Ubb.BikeContest.Model;

[Serializable]
public class Team : Identifiable<long>
{
    public Team(string name)
    {
        Name = name;
    }
    
    public string Name { get; set; }

    public override string ToString()
    {
        return Name;
    }
}