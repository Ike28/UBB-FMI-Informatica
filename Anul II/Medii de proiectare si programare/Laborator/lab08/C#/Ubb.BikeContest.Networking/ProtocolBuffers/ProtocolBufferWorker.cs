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

using User = Ubb.BikeContest.Model.User;
using Participant = Ubb.BikeContest.Model.Participant;
using Race = Ubb.BikeContest.Model.Race;
using RaceEntry = Ubb.BikeContest.Model.RaceEntry;
using Team = Ubb.BikeContest.Model.Team;
using RaceDTO = Ubb.BikeContest.Model.data.RaceDto;
using Google.Protobuf;

namespace Ubb.BikeContest.Networking.ProtocolBuffers
{
    public class ProtocolBufferWorker : IMainObserver
    {
        private readonly IContestServices _server;
        private readonly TcpClient _connection;
        private readonly NetworkStream _stream;
        private volatile bool _connected;

        public ProtocolBufferWorker(IContestServices server, TcpClient connection)
        {
            _server = server;
            _connection = connection;

            try
            {
                _stream = _connection.GetStream();
                _connected = true;
            }
            catch (Exception e)
            {
                Console.WriteLine(e.StackTrace);
            }
        }

        public virtual void ParticipantAdded(Participant participant)
        {
            try
            {
                SendResponse(ProtocolBuilderUtils.CreateNewParticipantResponse(participant));
            }
            catch (Exception e)
            {
                Console.WriteLine("Error while sending response object: " + e.Message);
            }
        }

        public virtual void RaceEntriesAdded(List<RaceDto> races)
        {
            try
            {
                SendResponse(ProtocolBuilderUtils.CreateUpdatedRacesResponse(races));
            }
            catch (Exception e)
            {
                Console.WriteLine("Error while sending response object: " + e.Message);
            }
        }

        private BikeContestResponse HandleRequest(BikeContestRequest request)
        {
            BikeContestRequest.Types.Type type = request.Type;

            switch (type)
            {
                case BikeContestRequest.Types.Type.Login:
                    Console.WriteLine("> handling login request...");
                    string username = ProtocolBuilderUtils.GetUsername(request);
                    string passwordToken = ProtocolBuilderUtils.GetPasswordToken(request);

                    try
                    {
                        lock (_server)
                        {
                            User connectedUser = _server.Login(username, passwordToken, this);
                            return ProtocolBuilderUtils.CreateOkResponse(connectedUser);
                        }
                    }
                    catch (Exception e)
                    {
                        _connected = false;
                        return ProtocolBuilderUtils.CreateErrorResponse(e.Message);
                    }

                case BikeContestRequest.Types.Type.Logout:
                    Console.WriteLine("> handling logout request...");
                    User user = ProtocolBuilderUtils.GetUser(request);

                    try
                    {
                        lock (_server)
                        {
                            _server.Logout(user, this);
                        }

                        _connected = false;
                        return ProtocolBuilderUtils.CreateOkResponse();
                    }
                    catch (Exception e)
                    {
                        return ProtocolBuilderUtils.CreateErrorResponse(e.Message);
                    }

                case BikeContestRequest.Types.Type.CreateParticipant:
                    Console.WriteLine("> handling create participant request...");
                    Participant participant = ProtocolBuilderUtils.GetParticipant(request);

                    try
                    {
                        lock (_server)
                        {
                            _server.SaveParticipant(participant);

                            return ProtocolBuilderUtils.CreateNewParticipantResponse(
                                _server.GetParticipantByData(participant));
                        }
                    }
                    catch (Exception e)
                    {
                        return ProtocolBuilderUtils.CreateErrorResponse(e.Message);
                    }

                case BikeContestRequest.Types.Type.CreateRace:
                    Console.WriteLine("> handling create race request...");
                    Race race = ProtocolBuilderUtils.GetRace(request);

                    try
                    {
                        lock (_server)
                        {
                            _server.SaveRace(race);
                            Race createdRace = _server.GetRaceByName(race.Name);
                            List<RaceEntry> entries = _server.GetEntriesByRace(createdRace.Id);

                            return ProtocolBuilderUtils.CreateNewRaceResponse(
                                new RaceDTO(createdRace.Name, createdRace.EngineCapacity, entries.Count));
                        }
                    }
                    catch (Exception e)
                    {
                        return ProtocolBuilderUtils.CreateErrorResponse(e.Message);
                    }

                case BikeContestRequest.Types.Type.CreateRaceEntries:
                    Console.WriteLine("> handling create race entries request...");
                    List<RaceEntry> raceEntries = ProtocolBuilderUtils.GetRaceEntries(request);

                    try
                    {
                        lock (_server)
                        {
                            _server.SaveRaceEntries(raceEntries);

                            return ProtocolBuilderUtils.CreateUpdatedRacesResponse(
                                _server.GetRacesWithParticipantCount());
                        }
                    }
                    catch (Exception e)
                    {
                        return ProtocolBuilderUtils.CreateErrorResponse(e.Message);
                    }

                case BikeContestRequest.Types.Type.GetEntriesByRace:
                    Console.WriteLine("> handling get entries by race request...");
                    long raceId = ProtocolBuilderUtils.GetRaceId(request);

                    try
                    {
                        lock (_server)
                        {
                            List<RaceEntry> entries = _server.GetEntriesByRace(raceId);
                            return ProtocolBuilderUtils.CreateEntriesByRaceResponse(entries);
                        }
                    }
                    catch (Exception e)
                    {
                        return ProtocolBuilderUtils.CreateErrorResponse(e.Message);
                    }

                case BikeContestRequest.Types.Type.GetParticipantByData:
                    Console.WriteLine("> handling get participant by data request...");
                    Participant data = ProtocolBuilderUtils.GetParticipant(request);

                    try
                    {
                        lock (_server)
                        {
                            return ProtocolBuilderUtils.CreateParticipantResponse(
                                _server.GetParticipantByData(data));
                        }
                    }
                    catch (Exception e)
                    {
                        return ProtocolBuilderUtils.CreateErrorResponse(e.Message);
                    }

                case BikeContestRequest.Types.Type.GetParticipantsByTeam:
                    Console.WriteLine("> handling get participants by team request...");
                    long teamId = ProtocolBuilderUtils.GetTeamId(request);

                    try
                    {
                        lock (_server)
                        {
                            List<Participant> participants = _server.GetParticipantsByTeam(teamId);
                            return ProtocolBuilderUtils.CreateParticipantsByTeamResponse(participants);
                        }
                    }
                    catch (Exception e)
                    {
                        return ProtocolBuilderUtils.CreateErrorResponse(e.Message);
                    }

                case BikeContestRequest.Types.Type.GetParticipants:
                    Console.WriteLine("> handling get participants request...");

                    try
                    {
                        lock (_server)
                        {
                            List<Participant> participants = _server.FindAllParticipants();

                            return ProtocolBuilderUtils.CreateAllParticipantsResponse(participants);
                        }
                    }
                    catch (Exception e)
                    {
                        return ProtocolBuilderUtils.CreateErrorResponse(e.Message);
                    }

                case BikeContestRequest.Types.Type.GetRaceByName:
                    Console.WriteLine("> handling get race by name request...");
                    string raceName = ProtocolBuilderUtils.GetRaceName(request);

                    try
                    {
                        lock (_server)
                        {
                            Race res = _server.GetRaceByName(raceName);

                            return ProtocolBuilderUtils.CreateGetRaceByNameResponse(res);
                        }
                    }
                    catch (Exception e)
                    {
                        return ProtocolBuilderUtils.CreateErrorResponse(e.Message);
                    }

                case BikeContestRequest.Types.Type.GetRacesByEngineCapacity:
                    Console.WriteLine("> handling get races by engine capacity request...");
                    int capacity = ProtocolBuilderUtils.GetEngineCapacity(request);

                    try
                    {
                        lock (_server)
                        {
                            List<Race> races = _server.GetRacesByEngineCapacity(capacity);

                            return ProtocolBuilderUtils.CreateGetRacesByCapacityResponse(races);
                        }
                    }
                    catch (Exception e)
                    {
                        return ProtocolBuilderUtils.CreateErrorResponse(e.Message);
                    }

                case BikeContestRequest.Types.Type.GetRacesWithParticipantCount:
                    Console.WriteLine("> handling get races with participant count request...");

                    try
                    {
                        lock (_server)
                        {
                            List<RaceDTO> races = _server.GetRacesWithParticipantCount();

                            return ProtocolBuilderUtils.CreateGetRacesWithParticipantsResponse(races);
                        }
                    }
                    catch (Exception e)
                    {
                        return ProtocolBuilderUtils.CreateErrorResponse(e.Message);
                    }

                case BikeContestRequest.Types.Type.GetTeamByName:
                    Console.WriteLine("> handling get team by name request...");
                    string teamName = ProtocolBuilderUtils.GetTeamName(request);

                    try
                    {
                        lock (_server)
                        {
                            Team team = _server.GetTeamByName(teamName);

                            return ProtocolBuilderUtils.CreateGetTeamResponse(team);
                        }
                    }
                    catch (Exception e)
                    {
                        return ProtocolBuilderUtils.CreateErrorResponse(e.Message);
                    }

                case BikeContestRequest.Types.Type.GetTeams:
                    Console.WriteLine("> handling get teams request...");

                    try
                    {
                        lock (_server)
                        {
                            List<Team> teams = _server.FindAllTeams();

                            return ProtocolBuilderUtils.CreateAllTeamsResponse(teams);
                        }
                    }
                    catch (Exception e)
                    {
                        return ProtocolBuilderUtils.CreateErrorResponse(e.Message);
                    }

                case BikeContestRequest.Types.Type.GetUnregisteredRaces:
                    Console.WriteLine("> handling get unregistered races request...");
                    long participandId = ProtocolBuilderUtils.GetParticipantId(request);
                    int engineCapacity = ProtocolBuilderUtils.GetEngineCapacity(request);

                    try
                    {
                        lock (_server)
                        {
                            List<Race> races = _server.GetRacesWhereNotRegisteredAndEngineCapacity(participandId, engineCapacity);

                            return ProtocolBuilderUtils.CreateGetRacesByCapacityResponse(races);
                        }
                    }
                    catch (Exception e)
                    {
                        return ProtocolBuilderUtils.CreateErrorResponse(e.Message);
                    }
            }
            return null;
        }

        private void SendResponse(BikeContestResponse response)
        {
            Console.WriteLine("Sending response: " + response);

            lock (_stream)
            {
                response.WriteDelimitedTo(_stream);
                _stream.Flush();
            }
        }

        public virtual void Run()
        {
            while (_connected)
            {
                try
                {
                    BikeContestRequest request = BikeContestRequest.Parser.ParseDelimitedFrom(_stream);
                    BikeContestResponse response = HandleRequest(request);

                    if (response != null)
                    {
                        SendResponse(response);
                    }
                }
                catch (Exception e)
                {
                    Console.WriteLine(e.StackTrace);
                }

                try
                {
                    Thread.Sleep(1000);
                }
                catch (Exception e)
                {
                    Console.WriteLine(e.StackTrace);
                }
            }

            try
            {
                _stream.Close();
                _connection.Close();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.StackTrace);
            }
        }
    }
}
