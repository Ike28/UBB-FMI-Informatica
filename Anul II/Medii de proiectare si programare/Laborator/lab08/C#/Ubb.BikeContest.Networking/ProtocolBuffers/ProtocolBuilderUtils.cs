using Com.Ubb.Protocolbuffers;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Ubb.BikeContest.Model;

using protocol = Com.Ubb.Protocolbuffers;
using User = Ubb.BikeContest.Model.User;
using Participant = Ubb.BikeContest.Model.Participant;
using Race = Ubb.BikeContest.Model.Race;
using RaceEntry = Ubb.BikeContest.Model.RaceEntry;
using Team = Ubb.BikeContest.Model.Team;
using RaceDTO = Ubb.BikeContest.Model.data.RaceDto;
using System.Configuration;

namespace Ubb.BikeContest.Networking.ProtocolBuffers
{
    static class ProtocolBuilderUtils
    {
        public static BikeContestRequest CreateLoginRequest(string username, string passwordToken)
        {
            return new BikeContestRequest
            {
                Type = BikeContestRequest.Types.Type.Login,
                Username = username,
                PasswordToken = passwordToken
            };
        }

        public static BikeContestRequest CreateLogoutRequest(User user)
        {
            return new BikeContestRequest
            {
                Type = BikeContestRequest.Types.Type.Logout,
                User = BuildUser(user)
            };
        }

        public static BikeContestRequest CreateNewParticipantRequest(Participant participant)
        {
            return new BikeContestRequest
            {
                Type = BikeContestRequest.Types.Type.CreateParticipant,
                Participant = BuildParticipant(participant)
            };
        }

        public static BikeContestRequest CreateNewRaceEntriesRequest(List<RaceEntry> entries)
        {
            List<protocol.RaceEntry> buildEntries = new();
            entries.ForEach(entry => buildEntries.Add(BuildRaceEntry(entry)));

            return new BikeContestRequest
            {
                Type = BikeContestRequest.Types.Type.CreateRaceEntries,
                RaceEntries = { buildEntries }
            };
        }

        public static BikeContestRequest CreateNewRaceRequest(Race race)
        {
            return new BikeContestRequest
            {
                Type = BikeContestRequest.Types.Type.CreateRace,
                Race = BuildRace(race)
            };
        }

        public static BikeContestRequest CreateGetEntriesByRaceRequest(long raceId)
        {
            return new BikeContestRequest
            {
                Type = BikeContestRequest.Types.Type.GetEntriesByRace,
                RaceID = raceId
            };
        }

        public static BikeContestRequest CreateGetParticipantByDataRequest(Participant participant)
        {
            return new BikeContestRequest
            {
                Type = BikeContestRequest.Types.Type.GetParticipantByData,
                Participant = BuildParticipant(participant)
            };
        }

        public static BikeContestRequest CreateGetParticipantsByTeamRequest(long teamId)
        {
            return new BikeContestRequest
            {
                Type = BikeContestRequest.Types.Type.GetParticipantsByTeam,
                TeamID = teamId,
            };
        }

        public static BikeContestRequest CreateGetParticipantsRequest()
        {
            return new BikeContestRequest
            {
                Type = BikeContestRequest.Types.Type.GetParticipants
            };
        }

        public static BikeContestRequest CreateGetRaceByNameRequest(string raceName)
        {
            return new BikeContestRequest
            {
                Type = BikeContestRequest.Types.Type.GetRaceByName,
                RaceName = raceName,
            };
        }

        public static BikeContestRequest CreateGetRacesByEngineCapacityRequest(int capacity)
        {
            return new BikeContestRequest
            {
                Type = BikeContestRequest.Types.Type.GetRacesByEngineCapacity,
                EngineCapacity = capacity,
            };
        }

        public static BikeContestRequest CreateGetRacesWithParticipantCountRequest()
        {
            return new BikeContestRequest
            {
                Type = BikeContestRequest.Types.Type.GetRacesWithParticipantCount
            };
        }

        public static BikeContestRequest CreateGetTeamByNameRequest(string teamName)
        {
            return new BikeContestRequest
            {
                Type = BikeContestRequest.Types.Type.GetTeamByName,
                TeamName = teamName,
            };
        }

        public static BikeContestRequest CreateGetTeamsRequest()
        {
            return new BikeContestRequest
            {
                Type = BikeContestRequest.Types.Type.GetTeams
            };
        }

        public static BikeContestRequest CreateGetUnregisteredRacesRequest(
            long participantId, int engineCapacity)
        {
            return new BikeContestRequest
            {
                Type = BikeContestRequest.Types.Type.GetUnregisteredRaces,
                ParticipantID = participantId,
                EngineCapacity = engineCapacity
            };
        }

        public static BikeContestResponse CreateOkResponse()
        {
            return new BikeContestResponse
            {
                Type = BikeContestResponse.Types.Type.Ok
            };
        }

        public static BikeContestResponse CreateOkResponse(User user)
        {
            return new BikeContestResponse
            {
                Type = BikeContestResponse.Types.Type.Ok,
                User = BuildUser(user)
            };
        }

        public static BikeContestResponse CreateErrorResponse(string message)
        {
            return new BikeContestResponse
            {
                Type = BikeContestResponse.Types.Type.Error,
                ErrorMessage = message
            };
        }

        public static BikeContestResponse CreateAllParticipantsResponse(List<Participant> participants)
        {
            List<protocol.Participant> buildParticipants = new();
            participants.ForEach(participant => buildParticipants.Add(BuildParticipant(participant)));

            return new BikeContestResponse
            {
                Type = BikeContestResponse.Types.Type.AllParticipants,
                Participants = { buildParticipants }
            };
        }

        public static BikeContestResponse CreateAllTeamsResponse(List<Team> teams)
        {
            List<protocol.Team> buildTeams = new();
            teams.ForEach(team => buildTeams.Add(BuildTeam(team)));

            return new BikeContestResponse
            {
                Type = BikeContestResponse.Types.Type.AllTeams,
                Teams = { buildTeams }
            };
        }

        public static BikeContestResponse CreateEntriesByRaceResponse(List<RaceEntry> raceEntries)
        {
            List<protocol.RaceEntry> buildEntries = new();
            raceEntries.ForEach(entry => buildEntries.Add(BuildRaceEntry(entry)));

            return new BikeContestResponse
            {
                Type = BikeContestResponse.Types.Type.EntriesByRace,
                Entries = { buildEntries }
            };
        }

        public static BikeContestResponse CreateParticipantsByTeamResponse(List<Participant> participants)
        {
            List<protocol.Participant> buildParticipants = new();
            participants.ForEach(participant => buildParticipants.Add(BuildParticipant(participant)));

            return new BikeContestResponse
            {
                Type = BikeContestResponse.Types.Type.GetParticipantsByTeam,
                Participants = { buildParticipants }
            };
        }

        public static BikeContestResponse CreateNewParticipantResponse(Participant participant)
        {
            return new BikeContestResponse
            {
                Type = BikeContestResponse.Types.Type.NewParticipant,
                Participant = BuildParticipant(participant)
            };
        }

        public static BikeContestResponse CreateNewRaceResponse(RaceDTO race)
        {
            return new BikeContestResponse
            {
                Type = BikeContestResponse.Types.Type.NewParticipant,
                RaceDTO = BuildRaceDto(race)
            };
        }

        public static BikeContestResponse CreateParticipantResponse(Participant participant)
        {
            return new BikeContestResponse
            {
                Type = BikeContestResponse.Types.Type.GetParticipant,
                Participant = BuildParticipant(participant)
            };
        }

        public static BikeContestResponse CreateGetRaceByNameResponse(Race race)
        {
            return new BikeContestResponse
            {
                Type = BikeContestResponse.Types.Type.RaceByName,
                Race = BuildRace(race)
            };
        }

        public static BikeContestResponse CreateGetRacesByCapacityResponse(List<Race> races)
        {
            List<protocol.Race> buildRaces = new();
            races.ForEach(race => buildRaces.Add(BuildRace(race)));

            return new BikeContestResponse
            {
                Type = BikeContestResponse.Types.Type.RacesByCapacity,
                Races = { buildRaces }
            };
        }

        public static BikeContestResponse CreateGetRacesWithParticipantsResponse(List<RaceDTO> races)
        {
            List<protocol.RaceDTO> buildRaces = new();
            races.ForEach(race => buildRaces.Add(BuildRaceDto(race)));

            return new BikeContestResponse
            {
                Type = BikeContestResponse.Types.Type.RacesWithParticipants,
                RacesDTO = { buildRaces }
            };
        }

        public static BikeContestResponse CreateGetTeamResponse(Team team)
        {
            return new BikeContestResponse
            {
                Type = BikeContestResponse.Types.Type.GetTeam,
                Team = BuildTeam(team)
            };
        }

        public static BikeContestResponse CreateUpdatedRacesResponse(List<RaceDTO> races)
        {
            List<protocol.RaceDTO> buildRaces = new();
            races.ForEach(race => buildRaces.Add(BuildRaceDto(race)));

            return new BikeContestResponse
            {
                Type = BikeContestResponse.Types.Type.UpdatedRaces,
                RacesDTO = { buildRaces }
            };
        }

        public static string GetErrorMessage(BikeContestResponse response)
        {
            return response.ErrorMessage;
        }

        public static User GetUser(BikeContestRequest request)
        {
            protocol.User user = request.User;
            User result = new(user.Username, user.FullName, user.PasswordToken)
            {
                Id = user.Id
            };
            return result;
        }

        public static User GetUser(BikeContestResponse request)
        {
            protocol.User user = request.User;
            User result = new(user.Username, user.FullName, user.PasswordToken)
            {
                Id = user.Id
            };
            return result;
        }

        public static string GetUsername(BikeContestRequest request)
        {
            return request.Username;
        }

        public static string GetPasswordToken(BikeContestRequest request)
        {
            return request.PasswordToken;
        }

        public static long GetParticipantId(BikeContestRequest request)
        {
            return request.ParticipantID;
        }

        public static int GetEngineCapacity(BikeContestRequest request)
        {
            return request.EngineCapacity;
        }

        public static string GetTeamName(BikeContestRequest request)
        {
            return request.TeamName;
        }

        public static string GetRaceName(BikeContestRequest request)
        {
            return request.RaceName;
        }

        public static long GetTeamId(BikeContestRequest request)
        {
            return request.TeamID;
        }

        public static Participant GetParticipant(BikeContestRequest request)
        {
            return UnbuildParticipant(request.Participant);
        }

        public static Participant GetParticipant(BikeContestResponse response)
        {
            return UnbuildParticipant(response.Participant);
        }

        public static long GetRaceId(BikeContestRequest request)
        {
            return request.RaceID;
        }

        public static List<RaceEntry> GetRaceEntries(BikeContestRequest request)
        {
            List<RaceEntry> result = new();
            foreach (protocol.RaceEntry entry in request.RaceEntries)
            {
                result.Add(UnbuildRaceEntry(entry));
            }

            return result;
        }

        public static List<RaceEntry> GetRaceEntries(BikeContestResponse response)
        {
            List<RaceEntry> result = new();
            foreach (protocol.RaceEntry entry in response.Entries)
            {
                result.Add(UnbuildRaceEntry(entry));
            }

            return result;
        }

        public static Race GetRace(BikeContestRequest request)
        {
            return UnbuildRace(request.Race);
        }

        public static Race GetRace(BikeContestResponse response)
        {
            return UnbuildRace(response.Race);
        }

        public static RaceDTO GetRaceDto(BikeContestResponse response)
        {
            return UnbuildRaceDto(response.RaceDTO);
        }

        public static List<RaceDTO> GetRaceDtos(BikeContestResponse response)
        {
            List<RaceDTO> result = new();
            foreach (protocol.RaceDTO race in response.RacesDTO)
            {
                result.Add(UnbuildRaceDto(race));
            }

            return result;
        }

        public static List<Participant> GetParticipants(BikeContestResponse response)
        {
            List<Participant> result = new();
            foreach (protocol.Participant participant in response.Participants)
            {
                result.Add(UnbuildParticipant(participant));
            }

            return result;
        }

        public static List<Race> GetRaces(BikeContestResponse response)
        {
            List<Race> result = new();
            foreach (protocol.Race race in response.Races)
            {
                result.Add(UnbuildRace(race));
            }

            return result;
        }

        public static Team GetTeam(BikeContestResponse response)
        {
            return UnbuildTeam(response.Team);
        }

        public static List<Team> GetTeams(BikeContestResponse response)
        {
            List<Team> result = new();
            foreach (protocol.Team team  in response.Teams)
            {
                result.Add(UnbuildTeam(team));
            }

            return result;
        }

        private static protocol.Participant BuildParticipant(Participant participant)
        {
            return new protocol.Participant
            {
                Id = participant.Id,
                FirstName = participant.FirstName,
                LastName = participant.LastName,
                EngineCapacity = participant.EngineCapacity,
                TeamID = participant.Id
            };
        }

        private static protocol.User BuildUser(User user)
        {
            return new protocol.User
            {
                Id = user.Id,
                Username = user.Username,
                FullName = user.FullName,
                PasswordToken = user.Password
            };
        }

        private static protocol.Race BuildRace(Race race)
        {
            return new protocol.Race
            {
                Id = race.Id,
                Name = race.Name,
                EngineCapacity = race.EngineCapacity
            };
        }

        private static protocol.RaceEntry BuildRaceEntry(RaceEntry raceEntry)
        {
            return new protocol.RaceEntry
            {
                Id = raceEntry.Id,
                Participant = BuildParticipant(raceEntry.Participant),
                Race = BuildRace(raceEntry.Race)
            };
        }

        private static protocol.Team BuildTeam(Team team)
        {
            return new protocol.Team
            {
                Id = team.Id,
                Name = team.Name
            };
        }

        private static protocol.RaceDTO BuildRaceDto(RaceDTO raceDTO)
        {
            return new protocol.RaceDTO
            {
                Name = raceDTO.Name,
                EngineCapacity = raceDTO.EngineCapacity,
                Participants = raceDTO.Participants
            };
        }

        private static Participant UnbuildParticipant(protocol.Participant participant)
        {
            Participant result = new Participant(
                participant.FirstName, 
                participant.LastName, 
                participant.EngineCapacity);
            result.Id = participant.Id;
            result.TeamId = participant.TeamID;

            return result;
        }

        private static Race UnbuildRace(protocol.Race race)
        {
            Race result = new Race(
                race.Name, race.EngineCapacity);
            result.Id = race.Id;

            return result;
        }

        private static RaceDTO UnbuildRaceDto(protocol.RaceDTO raceDTO)
        {
            return new RaceDTO(
                raceDTO.Name, 
                raceDTO.EngineCapacity, 
                raceDTO.Participants);
        }

        private static RaceEntry UnbuildRaceEntry(protocol.RaceEntry raceEntry) 
        {
            RaceEntry result = new RaceEntry(
                UnbuildParticipant(raceEntry.Participant), 
                UnbuildRace(raceEntry.Race));
            result.Id = raceEntry.Id;

            return result;
        }

        private static Team UnbuildTeam(protocol.Team team)
        {
            Team result = new(team.Name)
            {
                Id = team.Id
            };

            return result;
        }
    }
}
