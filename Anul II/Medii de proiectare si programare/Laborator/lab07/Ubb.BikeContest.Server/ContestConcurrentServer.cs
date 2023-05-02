using System.Net.Sockets;
using Ubb.BikeContest.Networking;

namespace Ubb.BikeContest.Services
{
    public class ContestConcurrentServer : ConcurrentServer
    {
        private readonly IContestServices server;
        private ClientWorker? worker;

        public ContestConcurrentServer(string host, int port, IContestServices server) : base(host, port)
        {
            this.server = server;
            Console.WriteLine("Server started...");
        }

        protected override Thread CreateWorker(TcpClient client)
        {
            worker = new ClientWorker(server, client);
            return new Thread(new ThreadStart(worker.Run));
        }
    }
}
