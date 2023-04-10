package com.ubb.protocol.response;

import com.ubb.model.User;

public class OKResponse implements Response {
    private final User user;

    public OKResponse(User user) {
        this.user = user;
    }

    public User getUser() {
        return user;
    }
}
