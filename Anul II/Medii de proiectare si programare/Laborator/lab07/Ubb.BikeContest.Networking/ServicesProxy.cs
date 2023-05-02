using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Threading.Tasks;
using Ubb.BikeContest.Model;
using Ubb.BikeContest.Model.data;
using Ubb.BikeContest.Networking.Request;
using Ubb.BikeContest.Networking.Request.Request;
using Ubb.BikeContest.Networking.Response;
using Ubb.BikeContest.Networking.Response.Response;
using Ubb.BikeContest.Services;
using Ubb.BikeContest.Services.src.Exceptions;

namespace Ubb.BikeContest.Networking
{
    public class ServicesProxy : IContestServices
    {
        private readonly string host;
        private readonly int port;
        private IMainObserver client;
        private NetworkStream stream;
        private IFormatter formatter;
        private TcpClient connection;
        private readonly Queue<IResponse> responses;
        private volatile bool finished;
        private EventWaitHandle _waitHandle;

        public ServicesProxy(string host, int port)
        {
            this.host = host;
            this.port = port;
            responses = new Queue<IResponse>();
            InitialiseConnection();
        }

        public virtual User Login(string username, string passwordToken, IMainObserver client)
        {
            SendRequest(new LoginRequest(username, passwordToken));
            IResponse response = ReadResponse();
            if (response is OkResponse)
            {
                this.client = client;
                return ((OkResponse)response).User;
            }
            if (response is ErrorResponse)
            {
                ErrorResponse error = (ErrorResponse)response;
                CloseConnection();
                throw new ContestDataException(error.Message);
            }
            return null;
        }

        public void Logout(User user, IMainObserver client)
        {
            SendRequest(new LogoutRequest(user));
            IResponse response = ReadResponse();
            CloseConnection();
            if (response is ErrorResponse)
            {
                ErrorResponse error = (ErrorResponse)response;
                throw new ContestDataException(error.Message);
            }
        }

        private void CloseConnection()
        {
            finished = true;
            try
            {
                stream.Close();
                connection.Close();
                _waitHandle.Close();
                client = null;
            }
            catch (Exception exception)
            {
                Console.WriteLine(exception.StackTrace);
            }
        }

        private void SendRequest(IRequest request)
        {
            try
            {
                formatter.Serialize(stream, request);
                stream.Flush();
            }
            catch (Exception exception)
            {
                throw new ContestDataException("Error sending object " + exception);
            }
        }

        private IResponse ReadResponse()
        {
            IResponse response = null;
            try
            {
                _waitHandle.WaitOne();
                lock (responses)
                {
                    response = responses.Dequeue();
                }
            }
            catch (Exception exception)
            {
                Console.WriteLine(exception.StackTrace);
            }
            return response;
        }

        private void InitialiseConnection()
        {
            try
            {
                connection = new TcpClient(host, port);
                stream = connection.GetStream();
                formatter = new BinaryFormatter();
                finished = false;
                _waitHandle = new AutoResetEvent(false);
                StartReader();
            }
            catch (Exception exception)
            {
                Console.WriteLine(exception.StackTrace);
            }
        }

        private void StartReader()
        {
            Thread threadWorker = new Thread(Run);
            threadWorker.Start();
        }

        private void HandleUpdate(UpdateResponse update)
        {
            if (update is NewParticipantResponse)
            {
                NewParticipantResponse response = (NewParticipantResponse)update;
                Console.WriteLine("New participant added: " + response.Participant);
                try
                {
                    client.ParticipantAdded(response.Participant);
                }
                catch (ContestDataException exception)
                {
                    Console.WriteLine(exception.StackTrace);
                }
            }

            if (update is UpdatedRacesResponse)
            {
                UpdatedRacesResponse response = (UpdatedRacesResponse)update;
                Console.WriteLine("Updated races");
                try
                {
                    client.RaceEntriesAdded(response.Races);
                }
                catch (ContestDataException exception)
                {
                    Console.WriteLine(exception.StackTrace);
                }
            }
        }

        public virtual void Run()
        {
            while (!finished)
            {
                try
                {
                    object response = formatter.Deserialize(stream);
                    Console.WriteLine("Response received: " + response);
                    if (response is UpdateResponse)
                    {
                        HandleUpdate((UpdateResponse)response);
                    }
                    else
                    {
                        lock (responses)
                        {
                            responses.Enqueue((IResponse)response);
                        }
                        _waitHandle.Set();
                    }
                }
                catch (Exception exception)
                {
                    Console.WriteLine("Reading error: " + exception);
                }
            }
        }

        public IEnumerable<RaceDto> GetRacesWithParticipantCount()
        {
            throw new NotImplementedException();
        }

        public IEnumerable<Team> FindAllTeams()
        {
            throw new NotImplementedException();
        }

        public IEnumerable<Participant> GetParticipantsByTeam(long id)
        {
            throw new NotImplementedException();
        }

        public IEnumerable<Participant> FindAllParticipants()
        {
            throw new NotImplementedException();
        }
    }
}
