namespace Ubb.BikeContest.Model;

public class Race : Identifiable<long>
{
    private string _name;
    private int _engineCapacity;

    public Race(long id, string name, int engineCapacity)
    {
        Id = id;
        _name = name;
        _engineCapacity = engineCapacity;
    }

    public string Name
    {
        get => _name;
        set => _name = value;
    }

    public int EngineCapacity
    {
        get => _engineCapacity;
        set => _engineCapacity = value;
    }
}