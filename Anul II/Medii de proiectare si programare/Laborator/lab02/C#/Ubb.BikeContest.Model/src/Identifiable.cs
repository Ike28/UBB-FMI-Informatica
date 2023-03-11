namespace Ubb.BikeContest.Model;

public class Identifiable<TID>
{
    private TID id;

    public TID Id
    {
        get => id;
        protected set => id = value;
    }
}