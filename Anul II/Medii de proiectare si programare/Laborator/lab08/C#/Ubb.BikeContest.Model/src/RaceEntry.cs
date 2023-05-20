namespace Ubb.BikeContest.Model;

[Serializable]
public class RaceEntry : Identifiable<long>
{
    private readonly Race _race;
    private readonly Participant _participant;

    public RaceEntry(Participant participant, Race race)
    {
        _participant = participant;
        _race = race;
    }

    public Participant Participant => _participant;

    public Race Race => _race;
}