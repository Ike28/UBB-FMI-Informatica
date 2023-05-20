package com.ubb.protocolbuffers;

import com.ubb.dto.RaceDTO;
import com.ubb.model.*;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

public class ProtocolBuilderUtils {
    public static BikeContestProtocol.BikeContestRequest createLoginRequest(
            final String username, final String passwordToken) {

        return BikeContestProtocol.BikeContestRequest.newBuilder()
        .setType(BikeContestProtocol.BikeContestRequest.Type.Login)
        .setUsername(username)
        .setPasswordToken(passwordToken)
        .build();
    }

    public static BikeContestProtocol.BikeContestRequest createLogoutRequest(final User user) {
        return BikeContestProtocol.BikeContestRequest.newBuilder()
        .setType(BikeContestProtocol.BikeContestRequest.Type.Logout)
        .setUser(buildUser(user)).build();
    }

    public static BikeContestProtocol.BikeContestRequest createNewParticipantRequest(final Participant participant) {
        return BikeContestProtocol.BikeContestRequest.newBuilder()
        .setType(BikeContestProtocol.BikeContestRequest.Type.CreateParticipant)
        .setParticipant(buildParticipant(participant)).build();
    }

    public static BikeContestProtocol.BikeContestRequest createNewRaceEntriesRequest(final List<RaceEntry> entries) {
        final List<BikeContestProtocol.RaceEntry> buildEntries = new ArrayList<>();
        entries.forEach((entry) -> buildEntries.add(buildRaceEntry(entry)));

        return BikeContestProtocol.BikeContestRequest.newBuilder()
                .setType(BikeContestProtocol.BikeContestRequest.Type.CreateRaceEntries)
                .addAllRaceEntries(buildEntries).build();
    }

    public static BikeContestProtocol.BikeContestRequest createNewRaceRequest(final Race race) {
        return BikeContestProtocol.BikeContestRequest.newBuilder()
                .setType(BikeContestProtocol.BikeContestRequest.Type.CreateRace)
                .setRace(buildRace(race)).build();
    }

    public static BikeContestProtocol.BikeContestRequest createGetEntriesByRaceRequest(final Long raceId) {
        return BikeContestProtocol.BikeContestRequest.newBuilder()
                .setType(BikeContestProtocol.BikeContestRequest.Type.GetEntriesByRace)
                .setRaceID(raceId).build();
    }

    public static BikeContestProtocol.BikeContestRequest createGetParticipantByDataRequest(
            final Participant participant) {
        return BikeContestProtocol.BikeContestRequest.newBuilder()
                .setType(BikeContestProtocol.BikeContestRequest.Type.GetParticipantByData)
                .setParticipant(buildParticipant(participant)).build();
    }

    public static BikeContestProtocol.BikeContestRequest createGetParticipantsByTeamRequest(final Long teamId) {
        return BikeContestProtocol.BikeContestRequest.newBuilder()
                .setType(BikeContestProtocol.BikeContestRequest.Type.GetParticipantsByTeam)
                .setTeamID(teamId).build();
    }

    public static BikeContestProtocol.BikeContestRequest createGetParticipantsRequest() {
        return BikeContestProtocol.BikeContestRequest.newBuilder()
                .setType(BikeContestProtocol.BikeContestRequest.Type.GetParticipants).build();
    }

    public static BikeContestProtocol.BikeContestRequest createGetRaceByNameRequest(final String raceName) {
        return BikeContestProtocol.BikeContestRequest.newBuilder()
                .setType(BikeContestProtocol.BikeContestRequest.Type.GetRaceByName)
                .setRaceName(raceName).build();
    }

    public static BikeContestProtocol.BikeContestRequest createGetRacesByEngineCapacityRequest(
            final Integer capacity) {
        return BikeContestProtocol.BikeContestRequest.newBuilder()
                .setType(BikeContestProtocol.BikeContestRequest.Type.GetRacesByEngineCapacity)
                .setEngineCapacity(capacity).build();
    }

    public static BikeContestProtocol.BikeContestRequest createGetRacesWithParticipantCount() {
        return BikeContestProtocol.BikeContestRequest.newBuilder()
                .setType(BikeContestProtocol.BikeContestRequest.Type.GetRacesByEngineCapacity).build();
    }

    public static BikeContestProtocol.BikeContestRequest createGetTeamByNameRequest(final String teamName) {
        return BikeContestProtocol.BikeContestRequest.newBuilder()
                .setType(BikeContestProtocol.BikeContestRequest.Type.GetTeamByName)
                .setTeamName(teamName).build();
    }

    public static BikeContestProtocol.BikeContestRequest createGetTeamsRequest() {
        return BikeContestProtocol.BikeContestRequest.newBuilder()
                .setType(BikeContestProtocol.BikeContestRequest.Type.GetTeams).build();
    }

    public static BikeContestProtocol.BikeContestRequest createGetUnregisteredRacesRequest(
            final Long participantId, final Integer engineCapacity) {
        return BikeContestProtocol.BikeContestRequest.newBuilder()
                .setType(BikeContestProtocol.BikeContestRequest.Type.GetUnregisteredRaces)
                .setParticipantID(participantId)
                .setEngineCapacity(engineCapacity).build();
    }

    public static BikeContestProtocol.BikeContestResponse createOkResponse() {
        return BikeContestProtocol.BikeContestResponse.newBuilder()
        .setType(BikeContestProtocol.BikeContestResponse.Type.Ok).build();
    }

    public static BikeContestProtocol.BikeContestResponse createOkResponse(final User user) {
        return BikeContestProtocol.BikeContestResponse.newBuilder()
        .setType(BikeContestProtocol.BikeContestResponse.Type.Ok)
        .setUser(buildUser(user)).build();
    }

    public static BikeContestProtocol.BikeContestResponse createErrorResponse(final String message) {
        return BikeContestProtocol.BikeContestResponse.newBuilder()
                .setType(BikeContestProtocol.BikeContestResponse.Type.Error)
                .setErrorMessage(message).build();
    }

    public static BikeContestProtocol.BikeContestResponse createAllParticipantsResponse(
            final List<Participant> participants) {
        final List<BikeContestProtocol.Participant> buildParticipants = new ArrayList<>();
        participants.forEach((participant -> buildParticipants.add(buildParticipant(participant))));

        return BikeContestProtocol.BikeContestResponse.newBuilder()
                .setType(BikeContestProtocol.BikeContestResponse.Type.AllParticipants)
                .addAllParticipants(buildParticipants).build();
    }

    public static BikeContestProtocol.BikeContestResponse createAllTeamsResponse(final List<Team> teams) {
        final List<BikeContestProtocol.Team> buildTeams = new ArrayList<>();
        teams.forEach((team) -> buildTeams.add(buildTeam(team)));

        return BikeContestProtocol.BikeContestResponse.newBuilder()
                .setType(BikeContestProtocol.BikeContestResponse.Type.AllTeams)
                .addAllTeams(buildTeams).build();
    }

    public static BikeContestProtocol.BikeContestResponse createEntriesByRaceResponse(
            final List<RaceEntry> raceEntries) {
        final List<BikeContestProtocol.RaceEntry> buildEntries = new ArrayList<>();
        raceEntries.forEach((entry) -> buildEntries.add(buildRaceEntry(entry)));

        return BikeContestProtocol.BikeContestResponse.newBuilder()
                .setType(BikeContestProtocol.BikeContestResponse.Type.EntriesByRace)
                .addAllEntries(buildEntries).build();
    }

    public static BikeContestProtocol.BikeContestResponse createParticipantsByTeamResponse(
            final List<Participant> participants) {
        final List<BikeContestProtocol.Participant> buildParticipants = new ArrayList<>();
        participants.forEach((participant -> buildParticipants.add(buildParticipant(participant))));

        return BikeContestProtocol.BikeContestResponse.newBuilder()
                .setType(BikeContestProtocol.BikeContestResponse.Type.GetParticipantsByTeam)
                .addAllParticipants(buildParticipants).build();
    }

    public static BikeContestProtocol.BikeContestResponse createNewParticipantResponse(
            final Participant createdParticipant) {
        return BikeContestProtocol.BikeContestResponse.newBuilder()
                .setType(BikeContestProtocol.BikeContestResponse.Type.NewParticipant)
                .setParticipant(buildParticipant(createdParticipant)).build();
    }

    public static BikeContestProtocol.BikeContestResponse createNewRaceResponse(final RaceDTO race) {
        return BikeContestProtocol.BikeContestResponse.newBuilder()
                .setType(BikeContestProtocol.BikeContestResponse.Type.NewRace)
                .setRaceDTO(buildRaceDto(race)).build();
    }

    public static BikeContestProtocol.BikeContestResponse createParticipantResponse(final Participant participant) {
        return BikeContestProtocol.BikeContestResponse.newBuilder()
                .setType(BikeContestProtocol.BikeContestResponse.Type.GetParticipant)
                .setParticipant(buildParticipant(participant)).build();
    }

    public static BikeContestProtocol.BikeContestResponse createGetRaceByNameResponse(final Race race) {
        return BikeContestProtocol.BikeContestResponse.newBuilder()
                .setType(BikeContestProtocol.BikeContestResponse.Type.RaceByName)
                .setRace(buildRace(race)).build();
    }

    public static BikeContestProtocol.BikeContestResponse createGetRacesByCapacityResponse(final List<Race> races) {
        final List<BikeContestProtocol.Race> buildRaces = new ArrayList<>();
        races.forEach((race) -> buildRaces.add(buildRace(race)));

        return BikeContestProtocol.BikeContestResponse.newBuilder()
                .setType(BikeContestProtocol.BikeContestResponse.Type.RacesByCapacity)
                .addAllRaces(buildRaces).build();
    }

    public static BikeContestProtocol.BikeContestResponse createGetRacesWithParticipantsResponse(
            final List<RaceDTO> races) {
        final List<BikeContestProtocol.RaceDTO> buildRaces = new ArrayList<>();
        races.forEach((race) -> buildRaces.add(buildRaceDto(race)));

        return BikeContestProtocol.BikeContestResponse.newBuilder()
                .setType(BikeContestProtocol.BikeContestResponse.Type.RacesWithParticipants)
                .addAllRacesDTO(buildRaces).build();
    }

    public static BikeContestProtocol.BikeContestResponse createGetTeamResponse(final Team team) {
        return BikeContestProtocol.BikeContestResponse.newBuilder()
                .setType(BikeContestProtocol.BikeContestResponse.Type.GetTeam)
                .setTeam(buildTeam(team)).build();
    }

    public static BikeContestProtocol.BikeContestResponse createUpdatedRacesResponse(
            final List<RaceDTO> races) {
        final List<BikeContestProtocol.RaceDTO> buildRaces = new ArrayList<>();
        races.forEach((race) -> buildRaces.add(buildRaceDto(race)));

        return BikeContestProtocol.BikeContestResponse.newBuilder()
                .setType(BikeContestProtocol.BikeContestResponse.Type.UpdatedRaces)
                .addAllRacesDTO(buildRaces).build();
    }

    public static String getErrorMessage(final BikeContestProtocol.BikeContestResponse response) {
        return response.getErrorMessage();
    }

    public static User getUser(final BikeContestProtocol.BikeContestRequest request) {
        final BikeContestProtocol.User user = request.getUser();

        final User result = new User(user.getUsername(), user.getFullName());
        result.setId(user.getId());
        return result;
    }

    public static User getUser(final BikeContestProtocol.BikeContestResponse response) {
        final BikeContestProtocol.User user = response.getUser();

        final User result = new User(user.getUsername(), user.getFullName());
        result.setId(user.getId());
        return result;
    }

    public static String getUsername(final BikeContestProtocol.BikeContestRequest request) {
        return request.getUsername();
    }

    public static String getPasswordToken(final BikeContestProtocol.BikeContestRequest request) {
        return request.getPasswordToken();
    }

    public static Long getParticipantId(BikeContestProtocol.BikeContestRequest request) {
        return request.getParticipantID();
    }

    public static Integer getEngineCapacity(BikeContestProtocol.BikeContestRequest request) {
        return request.getEngineCapacity();
    }

    public static String getTeamName(BikeContestProtocol.BikeContestRequest request) {
        return request.getTeamName();
    }

    public static String getRaceName(BikeContestProtocol.BikeContestRequest request) {
        return request.getRaceName();
    }

    public static Long getTeamId(BikeContestProtocol.BikeContestRequest request) {
        return request.getTeamID();
    }

    public static Participant getParticipant(BikeContestProtocol.BikeContestRequest request) {
        return unbuildParticipant(request.getParticipant());
    }

    public static Participant getParticipant(BikeContestProtocol.BikeContestResponse response) {
        return unbuildParticipant(response.getParticipant());
    }

    public static Long getRaceId(BikeContestProtocol.BikeContestRequest request) {
        return request.getRaceID();
    }

    public static List<RaceEntry> getRaceEntries(BikeContestProtocol.BikeContestRequest request) {
        final List<RaceEntry> result = new ArrayList<>();
        request.getRaceEntriesList().forEach((buildEntry) -> result.add(unbuildRaceEntry(buildEntry)));

        return result;
    }

    public static List<RaceEntry> getRaceEntries(BikeContestProtocol.BikeContestResponse response) {
        final List<RaceEntry> result = new ArrayList<>();
        response.getEntriesList().forEach((buildEntry) -> result.add(unbuildRaceEntry(buildEntry)));

        return result;
    }

    public static Race getRaceDto(BikeContestProtocol.BikeContestRequest request) {
        return unbuildRace(request.getRace());
    }

    public static Race getRace(BikeContestProtocol.BikeContestResponse response) {
        return unbuildRace(response.getRace());
    }

    public static RaceDTO getRaceDto(BikeContestProtocol.BikeContestResponse response) {
        return unbuildRaceDto(response.getRaceDTO());
    }

    public static List<RaceDTO> getRaceDTOs(BikeContestProtocol.BikeContestResponse response) {
        final List<RaceDTO> result = new ArrayList<>();
        response.getRacesDTOList().forEach((raceDTO) -> result.add(unbuildRaceDto(raceDTO)));

        return result;
    }


    public static List<Participant> getParticipants(BikeContestProtocol.BikeContestResponse response) {
        List<Participant> result = new ArrayList<>();
        response.getParticipantsList().forEach((participant) -> {
            result.add(unbuildParticipant(participant));
        });

        return result;
    }

    public static List<Race> getRaces(BikeContestProtocol.BikeContestResponse response) {
        List<Race> result = new ArrayList<>();
        response.getRacesList().forEach((race) -> {
            result.add(unbuildRace(race));
        });

        return result;
    }

    public static Team getTeam(BikeContestProtocol.BikeContestResponse response) {
        return unbuildTeam(response.getTeam());
    }

    public static List<Team> getTeams(BikeContestProtocol.BikeContestResponse response) {
        List<Team> result = new ArrayList<>();
        response.getTeamsList().forEach((team) -> {
            result.add(unbuildTeam(team));
        });

        return result;
    }

    private static BikeContestProtocol.Participant buildParticipant(final Participant participant) {
        return BikeContestProtocol.Participant.newBuilder()
                .setId(participant.getId()).setFirstName(participant.getFirstName())
                .setLastName(participant.getLastName()).setEngineCapacity(participant.getEngineCapacity())
                .setTeamID(participant.getTeamID()).build();
    }

    private static BikeContestProtocol.User buildUser(final User user) {
        return BikeContestProtocol.User.newBuilder()
                .setId(user.getId()).setFullName(user.getFullName()).setUsername(user.getUsername())
                .setPasswordToken(user.getPasswordToken()).build();
    }

    private static BikeContestProtocol.Race buildRace(final Race race) {
        return BikeContestProtocol.Race.newBuilder()
                .setId(race.getId()).setName(race.getName()).setEngineCapacity(race.getEngineCapacity())
                .build();
    }

    private static BikeContestProtocol.RaceEntry buildRaceEntry(final RaceEntry raceEntry) {
        return BikeContestProtocol.RaceEntry.newBuilder()
                .setId(raceEntry.getId()).setParticipant(buildParticipant(raceEntry.getParticipant()))
                .setRace(buildRace(raceEntry.getRace())).build();
    }

    private static BikeContestProtocol.Team buildTeam(final Team team) {
        return BikeContestProtocol.Team.newBuilder()
                .setId(team.getId()).setName(team.getName()).build();
    }

    private static BikeContestProtocol.RaceDTO buildRaceDto(final RaceDTO raceDTO) {
        return BikeContestProtocol.RaceDTO.newBuilder()
                .setName(raceDTO.getName()).setEngineCapacity(raceDTO.getEngineCapacity())
                .setParticipants(raceDTO.getParticipants()).build();
    }

    private static Participant unbuildParticipant(final BikeContestProtocol.Participant participant) {
        final Participant result = new Participant(
                participant.getFirstName(),
                participant.getLastName(),
                participant.getEngineCapacity()
        );
        result.setId(participant.getId());

        return result;
    }

    private static Race unbuildRace(final BikeContestProtocol.Race race) {
        final Race result = new Race(
                race.getName(),
                race.getEngineCapacity()
        );
        result.setId(race.getId());

        return result;
    }

    private static RaceDTO unbuildRaceDto(final BikeContestProtocol.RaceDTO raceDTO) {
        return new RaceDTO(
                raceDTO.getName(),
                raceDTO.getEngineCapacity(),
                raceDTO.getParticipants()
        );
    }

    private static RaceEntry unbuildRaceEntry(final BikeContestProtocol.RaceEntry raceEntry) {
        final RaceEntry entry = new RaceEntry(
                unbuildParticipant(raceEntry.getParticipant()),
                unbuildRace(raceEntry.getRace())
        );
        entry.setId(raceEntry.getId());

        return entry;
    }

    private static Team unbuildTeam(final BikeContestProtocol.Team team) {
        final Team result = new Team(
                team.getName()
        );
        result.setId(team.getId());
        return result;
    }
}
