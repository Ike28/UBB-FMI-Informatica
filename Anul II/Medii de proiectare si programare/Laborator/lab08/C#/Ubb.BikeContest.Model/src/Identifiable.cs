namespace Ubb.BikeContest.Model;

[Serializable]
public class Identifiable<TId>
{
    public TId Id { get; set; }
}