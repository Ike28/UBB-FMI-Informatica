package com.ubb.protocolbuffers;

import com.ubb.model.User;

public class ProtocolBuilderUtils {
    public static BikeContestProtocol.BikeContestRequest createLoginRequest(
            final String username, final String passwordToken) {
        BikeContestProtocol.BikeContestRequest request
                = BikeContestProtocol.BikeContestRequest.newBuilder()
                .setType(BikeContestProtocol.BikeContestRequest.Type.Login)
                .setUsername(username)
                .setPasswordToken(passwordToken)
                .build();

        return request;
    }

    public static BikeContestProtocol.BikeContestRequest createLogoutRequest(final User user) {
        BikeContestProtocol.User buildUser = BikeContestProtocol.User.newBuilder()
                .setId(user.getId()).setFullName(user.getFullName()).setUsername(user.getUsername())
                .setPasswordToken(user.getPasswordToken()).build();

        BikeContestProtocol.BikeContestRequest request
                = BikeContestProtocol.BikeContestRequest.newBuilder()
                .setType(BikeContestProtocol.BikeContestRequest.Type.Logout)
                .setUser(buildUser).build();

        return request;
    }

    public static BikeContestProtocol.BikeContestResponse createOkResponse() {
        BikeContestProtocol.BikeContestResponse response
                = BikeContestProtocol.BikeContestResponse.newBuilder()
                .setType(BikeContestProtocol.BikeContestResponse.Type.Ok).build();
        return response;
    }

    public static BikeContestProtocol.BikeContestResponse createOkResponse(final User user) {
        BikeContestProtocol.User buildUser = BikeContestProtocol.User.newBuilder()
                .setId(user.getId()).setFullName(user.getFullName()).setUsername(user.getUsername())
                .setPasswordToken(user.getPasswordToken()).build();

        BikeContestProtocol.BikeContestResponse response
                = BikeContestProtocol.BikeContestResponse.newBuilder()
                .setType(BikeContestProtocol.BikeContestResponse.Type.Ok)
                .setUser(buildUser).build();

        return response;
    }

    public static BikeContestProtocol.BikeContestResponse createErrorResponse(final String message) {
        BikeContestProtocol.BikeContestResponse response = BikeContestProtocol.BikeContestResponse.newBuilder()
                .setType(BikeContestProtocol.BikeContestResponse.Type.Error)
                .setErrorMessage(message).build();
        return response;
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
}
