namespace Ubb.BikeContest.Model.data;

public class RaceDto
{
    private readonly string _name;
    private readonly int _engineCapacity;
    private readonly int _participant;

    public RaceDto(string name, int engineCapacity, int participant)
    {
        _name = name;
        _engineCapacity = engineCapacity;
        _participant = participant;
    }

    public string Name => _name;

    public int EngineCapacity => _engineCapacity;

    public int Participants => _participant;
}