namespace Ubb.BikeContest.Model;

public class User : Identifiable<long>
{
    public User(string username, string fullName)
    {
        Username = username;
        FullName = fullName;
    }

    public string Username { get; set; }

    public string FullName { get; set; }
}