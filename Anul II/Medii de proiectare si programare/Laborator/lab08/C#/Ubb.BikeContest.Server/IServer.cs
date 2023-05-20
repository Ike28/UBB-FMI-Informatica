using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Threading;
using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Networking
{
    public abstract class IServer
    {
        private readonly TcpListener server;
        private readonly string host;
        private readonly int port;
        public IServer(string host, int port)
        {
            this.host = host;
            this.port = port;
            IPAddress adr = IPAddress.Parse(host);
            IPEndPoint ep = new IPEndPoint(adr, port);
            server = new TcpListener(ep);
        }
        public void Start()
        {
            server.Start();
            while (true)
            {
                Console.WriteLine("Waiting for clients ...");
                TcpClient client = server.AcceptTcpClient();
                Console.WriteLine("Client connected ...");
                ProcessRequest(client);
            }
        }

        public abstract void ProcessRequest(TcpClient client);
    }
}
