namespace Ubb.BikeContest.Model;

public class Team : Identifiable<long>
{
    private string _name;

    public Team(long id, string name)
    {
        Id = id;
        _name = name;
    }
    
    public string Name
    {
        get => _name;
        set => _name = value;
    }
}