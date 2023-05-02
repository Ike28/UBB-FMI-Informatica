using System.Net.Sockets;
using Ubb.BikeContest.Networking;

namespace Ubb.BikeContest.Services
{
    public abstract class ConcurrentServer : IServer
    {
        public ConcurrentServer(string host, int port) : base(host, port)
        { }

        public override void ProcessRequest(TcpClient client)
        {
            Thread t = CreateWorker(client);
            t.Start();
        }

        protected abstract Thread CreateWorker(TcpClient client);
    }
}
