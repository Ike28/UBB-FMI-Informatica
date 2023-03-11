namespace Ubb.BikeContest.Model;

public class User : Identifiable<long>
{
    private string _username;
    private string _fullName;

    public User(long id, string username, string fullName)
    {
        Id = id;
        _username = username;
        _fullName = fullName;
    }

    public string Username
    {
        get => _username;
        set => _username = value;
    }

    public string FullName
    {
        get => _fullName;
        set => _fullName = value;
    }
}