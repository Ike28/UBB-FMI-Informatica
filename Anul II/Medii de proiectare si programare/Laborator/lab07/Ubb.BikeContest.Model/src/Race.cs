namespace Ubb.BikeContest.Model;

[Serializable]
public class Race : Identifiable<long>
{
    public Race(string name, int engineCapacity)
    {
        Name = name;
        EngineCapacity = engineCapacity;
    }

    public string Name { get; set; }

    public int EngineCapacity { get; set; }
}