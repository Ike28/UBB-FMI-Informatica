using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Threading.Tasks;
using Ubb.BikeContest.Model;
using Ubb.BikeContest.Model.data;
using Ubb.BikeContest.Networking.Protocol.Request;
using Ubb.BikeContest.Networking.Protocol.Response;
using Ubb.BikeContest.Services;
using Ubb.BikeContest.Services.src.Exceptions;

namespace Ubb.BikeContest.Networking.Protocol
{
    public class ClientWorker : IMainObserver
    {
        private IContestServices server;
        private TcpClient connection;
        private NetworkStream stream;
        private IFormatter formatter;
        private volatile bool connected;

        public ClientWorker(IContestServices server, TcpClient connection)
        {
            this.server = server;
            this.connection = connection;
            try
            {
                stream = connection.GetStream();
                formatter = new BinaryFormatter();
                connected = true;
            }
            catch (Exception exception)
            {
                Console.WriteLine(exception.StackTrace);
            }
        }

        public virtual void Run()
        {
            while (connected)
            {
                try
                {
                    object request = formatter.Deserialize(stream);
                    object response = HandleRequest((IRequest)request);
                    if (response != null)
                    {
                        SendResponse((IResponse)response);
                    }
                }
                catch (Exception exception)
                {
                    Console.WriteLine(exception.StackTrace);
                }

                try
                {
                    Thread.Sleep(1000);
                }
                catch (Exception exception)
                {
                    Console.WriteLine(exception.StackTrace);
                }
            }

            try
            {
                stream.Close();
                connection.Close();
            }
            catch (Exception exception)
            {
                Console.WriteLine("Error: " + exception);
            }
        }
        public void ParticipantAdded(Participant participant)
        {
            Console.WriteLine("Participant added: " + participant);
            try
            {
                SendResponse(new NewParticipantResponse(participant));
            }
            catch (Exception exception)
            {
                Console.WriteLine(exception.StackTrace);
            }
        }

        public void RaceEntriesAdded(List<RaceDto> races)
        {
            Console.WriteLine("Race entries added");
            try
            {
                SendResponse(new UpdatedRacesResponse(races));
            }
            catch (Exception exception)
            {
                Console.WriteLine(exception.StackTrace);
            }
        }

        private IResponse HandleRequest(IRequest request)
        {
            IResponse response = null;
            if (request is LoginRequest)
            {
                Console.WriteLine("Login request ... ");
                LoginRequest loginRequest = (LoginRequest)request;
                try
                {
                    lock (server)
                    {
                        User user = server.Login(loginRequest.Username, loginRequest.Token, this);
                        return new OkResponse(user);
                    }
                }
                catch (ContestDataException exception)
                {
                    connected = false;
                    return new ErrorResponse(exception.Message);
                }
            }

            if (request is LogoutRequest)
            {
                Console.WriteLine("Logout request");
                LogoutRequest logoutRequest = (LogoutRequest)request;
                try
                {
                    lock (server)
                    {
                        server.Logout(logoutRequest.User, this);
                    }
                    connected = false;
                    return new OkResponse(null);
                }
                catch (ContestDataException exception)
                {
                    return new ErrorResponse(exception.Message);
                }
            }

            if (request is CreateParticipantRequest)
            {
                Console.WriteLine("Create participant request");
                CreateParticipantRequest createRequest = (CreateParticipantRequest)request;
                try
                {
                    lock (server)
                    {
                        server.SaveParticipant(createRequest.Participant);
                    }
                }
                catch (ContestDataException exception)
                {
                    return new ErrorResponse(exception.Message);
                }
            }

            if (request is CreateRaceEntriesRequest)
            {
                Console.WriteLine("Create race entries request");
                CreateRaceEntriesRequest registerToRacesRequest = (CreateRaceEntriesRequest)request;
                try
                {
                    lock (server)
                    {
                        server.SaveRaceEntries(registerToRacesRequest.RaceEntries);
                    }
                }
                catch (ContestDataException exception)
                {
                    return new ErrorResponse(exception.Message);
                }
            }

            if (request is GetParticipantsByTeamRequest)
            {
                Console.WriteLine("Get participants by team request");
                GetParticipantsByTeamRequest participantsByTeamRequest = (GetParticipantsByTeamRequest)request;
                try
                {
                    lock (server)
                    {
                        var result = server.GetParticipantsByTeam(participantsByTeamRequest.TeamId);
                        return new GetParticipantsByTeamResponse(result);
                    }
                }
                catch (ContestDataException exception)
                {
                    return new ErrorResponse(exception.Message);
                }
            }

            if (request is GetAllParticipantsRequest)
            {
                Console.WriteLine("Get participants request");
                try
                {
                    lock (server)
                    {
                        var result = server.FindAllParticipants();
                        return new AllParticipantsResponse(result);
                    }
                }
                catch (ContestDataException exception)
                {
                    return new ErrorResponse(exception.Message);
                }
            }

            if (request is GetRacesWithParticipantCountRequest)
            {
                Console.WriteLine("Get races with participants count request");
                try
                {
                    lock (server)
                    {
                        var result = server.GetRacesWithParticipantCount();
                        return new RacesWithParticipantsResponse(result);
                    }
                }
                catch (ContestDataException exception)
                {
                    return new ErrorResponse(exception.Message);
                }
            }

            if (request is GetAllTeamsRequest)
            {
                Console.WriteLine("Get teams request");
                try
                {
                    lock (server)
                    {
                        var result = server.FindAllTeams();
                        return new AllTeamsResponse(result);
                    }
                }
                catch (ContestDataException exception)
                {
                    return new ErrorResponse(exception.Message);
                }
            }

            if (request is GetUnregisteredRacesRequest)
            {
                Console.WriteLine("Get unregistered races request");
                GetUnregisteredRacesRequest unregisteredRacesRequest = (GetUnregisteredRacesRequest)request;
                try
                {
                    lock (server)
                    {
                        var result = server.GetRacesWhereNotRegisteredAndEngineCapacity(unregisteredRacesRequest.ParticipantId, unregisteredRacesRequest.EngineCapacity);
                        return new UnregisteredRacesResponse(result);
                    }
                }
                catch (ContestDataException exception)
                {
                    return new ErrorResponse(exception.Message);
                }
            }

            return response;
        }

        private void SendResponse(IResponse response)
        {
            Console.WriteLine("sending response: " + response);
            formatter.Serialize(stream, response);
            stream.Flush();
        }
    }
}
