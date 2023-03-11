namespace Ubb.BikeContest.Model;

public class RaceEntry : Identifiable<long>
{
    private readonly Participant _participant;
    private readonly Race _race;

    public RaceEntry(long id, Participant participant, Race race)
    {
        Id = id;
        _participant = participant;
        _race = race;
    }

    public Participant Participant => _participant;

    public Race Race => _race;
}