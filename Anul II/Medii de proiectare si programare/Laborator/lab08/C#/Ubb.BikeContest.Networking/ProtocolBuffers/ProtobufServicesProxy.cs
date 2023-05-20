using Com.Ubb.Protocolbuffers;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using Ubb.BikeContest.Model;
using Ubb.BikeContest.Model.data;
using Ubb.BikeContest.Services;
using Google.Protobuf;

using Participant = Ubb.BikeContest.Model.Participant;
using Team = Ubb.BikeContest.Model.Team;
using Race = Ubb.BikeContest.Model.Race;
using User = Ubb.BikeContest.Model.User;
using RaceEntry = Ubb.BikeContest.Model.RaceEntry;

namespace Ubb.BikeContest.Networking.ProtocolBuffers
{
    public class ProtobufServicesProxy : IContestServices
    {
        private readonly string _host;
        private readonly int _port;
        private IMainObserver _client;
        private NetworkStream _stream;
        private TcpClient _connection;

        private Queue<BikeContestResponse> _responses;
        private volatile bool _finished;
        private EventWaitHandle _waitHandle;

        public ProtobufServicesProxy(string host, int port)
        {
            _host = host;
            _port = port;
            _responses = new Queue<BikeContestResponse>();
        }

        public List<Participant> FindAllParticipants()
        {
            throw new NotImplementedException();
        }

        public List<Team> FindAllTeams()
        {
            throw new NotImplementedException();
        }

        public List<Participant> GetParticipantsByTeam(long id)
        {
            throw new NotImplementedException();
        }

        public List<Race> GetRacesWhereNotRegisteredAndEngineCapacity(long participantId, int engineCapacity)
        {
            throw new NotImplementedException();
        }

        public List<RaceDto> GetRacesWithParticipantCount()
        {
            throw new NotImplementedException();
        }

        public User Login(string username, string passwordToken, IMainObserver client)
        {
            InitialiseConnection();

            BikeContestRequest request = ProtocolBuilderUtils.CreateLoginRequest(username, passwordToken);
            SendRequest(request);

            BikeContestResponse response = ReadResponse();
            if (response.Type == BikeContestResponse.Types.Type.Error)
            {
                CloseConnection();
                throw new Exception(ProtocolBuilderUtils.GetErrorMessage(response));
            }
            else if (response.Type == BikeContestResponse.Types.Type.Ok)
            {
                this._client = client;
                return ProtocolBuilderUtils.GetUser(response);
            }
            else
            {
                throw new Exception("Error while reading response: expected Ok, got " + response.Type);
            }
        }

        public void Logout(User user, IMainObserver client)
        {
            BikeContestRequest request = ProtocolBuilderUtils.CreateLogoutRequest(user);
            SendRequest(request);

            BikeContestResponse response = ReadResponse();
            CloseConnection();

            if (response.Type == BikeContestResponse.Types.Type.Error)
            {
                throw new Exception(ProtocolBuilderUtils.GetErrorMessage(response));
            }
        }

        public void SaveParticipant(Participant newEntity)
        {
            throw new NotImplementedException();
        }

        public void SaveRaceEntries(List<RaceEntry> newEntities)
        {
            throw new NotImplementedException();
        }

        private void SendRequest(BikeContestRequest request)
        {
            Console.WriteLine("Sending request..." + request);
            request.WriteDelimitedTo(_stream);
            _stream.Flush();
            Console.WriteLine("Request sent.");
        }

        private BikeContestResponse ReadResponse()
        {
            BikeContestResponse response = null;
            try
            {
                _waitHandle.WaitOne();
                lock (_responses)
                {
                    response = _responses.Dequeue();
                }
            }
            catch (Exception e) 
            {
                Console.WriteLine(e.StackTrace);
            }
            return response;
        }

        private void InitialiseConnection()
        {
            try
            {
                _connection = new TcpClient(_host, _port);
                _stream = _connection.GetStream();
                _finished = false;
                _waitHandle = new AutoResetEvent(false);
                StartReader();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.StackTrace);
            }
        }

        private void CloseConnection()
        {
            _finished = true;
            try
            {
                _stream.Close();
                _connection.Close();
                _waitHandle.Close();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.StackTrace);
            }
        }

        private void StartReader()
        {
            Thread worker = new Thread(Run);
            worker.Start();
        }

        private bool IsUpdateResponse(BikeContestResponse response)
        {
            return response.Type == BikeContestResponse.Types.Type.NewParticipant
                || response.Type == BikeContestResponse.Types.Type.NewRace
                || response.Type == BikeContestResponse.Types.Type.NewTeam
                || response.Type == BikeContestResponse.Types.Type.UpdatedRaces;
        }

        private void HandleUpdate(BikeContestResponse response)
        {
            if (IsUpdateResponse(response))
            {
                try
                {
                    switch (response.Type)
                    {
                        case BikeContestResponse.Types.Type.NewParticipant:
                            break;
                        case BikeContestResponse.Types.Type.NewRace:
                            break;
                        case BikeContestResponse.Types.Type.NewTeam:
                            break;
                        case BikeContestResponse.Types.Type.UpdatedRaces:
                            break;
                    }
                }
                catch (Exception e)
                {
                    Console.WriteLine(e.StackTrace);
                }
            }
        }

        public virtual void Run()
        {
            while (!_finished)
            {
                try
                {
                    BikeContestResponse response = BikeContestResponse.Parser.ParseDelimitedFrom(_stream);
                    Console.WriteLine("Response received: " + response);

                    if (IsUpdateResponse(response))
                    {
                        HandleUpdate(response);
                    }
                    else
                    {
                        lock (_responses)
                        {
                            _responses.Enqueue(response);
                        }
                        _waitHandle.Set();
                    }
                }
                catch (Exception e)
                {
                    Console.WriteLine(e.StackTrace);
                }
            }
        }
    }
}
