package com.ubb.protocol.request;

public class LoginRequest implements Request {
    private final String username;
    private final String passwordToken;

    public LoginRequest(String username, String passwordToken) {
        this.username = username;
        this.passwordToken = passwordToken;
    }

    public String getUsername() {
        return username;
    }

    public String getToken() {
        return passwordToken;
    }
}
