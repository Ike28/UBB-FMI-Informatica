namespace Ubb.BikeContest.Model;

public class Team : Identifiable<long>
{
    public Team(string name)
    {
        Name = name;
    }
    
    public string Name { get; set; }
}