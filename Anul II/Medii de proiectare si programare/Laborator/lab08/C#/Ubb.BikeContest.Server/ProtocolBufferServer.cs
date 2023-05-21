using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using Ubb.BikeContest.Networking.ProtocolBuffers;
using Ubb.BikeContest.Services;

namespace Ubb.BikeContest.Server
{
    public class ProtocolBufferServer : ConcurrentServer
    {
        private readonly IContestServices _server;
        private ProtocolBufferWorker _worker;

        public ProtocolBufferServer(string host, int port, IContestServices server) : base(host, port)
        {
            _server = server;
        }

        protected override Thread CreateWorker(TcpClient client)
        {
            _worker = new ProtocolBufferWorker(_server, client);
            return new Thread(new ThreadStart(_worker.Run));
        }
    }
}
