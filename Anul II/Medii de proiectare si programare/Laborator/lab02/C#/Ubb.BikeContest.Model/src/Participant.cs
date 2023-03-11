namespace Ubb.BikeContest.Model;

public class Participant : Identifiable<long>
{
    private string _firstName;
    private string _lastName;
    private int _engineCapacity;
    private Team? _team;

    public Participant(long id, string firstName, string lastName, int engineCapacity)
    {
        Id = id;
        _firstName = firstName;
        _lastName = lastName;
        _engineCapacity = engineCapacity;
    }

    public string FirstName
    {
        get => _firstName;
        set => _firstName = value;
    }

    public string LastName
    {
        get => _lastName;
        set => _lastName = value;
    }

    public int EngineCapacity
    {
        get => _engineCapacity;
        set => _engineCapacity = value;
    }

    public Team Team
    {
        get => _team ?? throw new ArgumentNullException();
        set => _team = value ?? throw new ArgumentNullException(nameof(value));
    }
}
    