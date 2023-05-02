namespace Ubb.BikeContest.Model;

[Serializable]
public class User : Identifiable<long>
{
    public User(string username, string fullName, string password)
    {
        Username = username;
        FullName = fullName;
        Password = password;
    }

    public string Username { get; set; }

    public string FullName { get; set; }
    
    public string Password { get; set; }
}