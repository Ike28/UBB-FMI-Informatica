package com.ubb.protocol.request;

import com.ubb.model.User;

public class LogoutRequest implements Request {
    private final User user;

    public LogoutRequest(User user) {
        this.user = user;
    }

    public User getUser() {
        return user;
    }
}
