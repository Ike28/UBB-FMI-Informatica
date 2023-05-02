using System.Security.Cryptography;
using System.Text;

namespace Ubb.BikeContest.Model;

public class Hasher
{
    public static string hash(string input)
    {
        HashAlgorithm algorithm = new SHA256CryptoServiceProvider();
        Byte[] inputBytes = Encoding.UTF8.GetBytes(input);

        Byte[] hashedBytes = algorithm.ComputeHash(inputBytes);

        return BitConverter.ToString(hashedBytes);
    }
}
