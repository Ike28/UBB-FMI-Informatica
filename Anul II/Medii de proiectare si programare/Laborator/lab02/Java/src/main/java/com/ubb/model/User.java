package com.ubb.model;

public class User extends Identifiable<Long> {
    private String username;
    private String fullName;

    public User(Long ID, String username, String fullName) {
        setID(ID);
        this.username = username;
        this.fullName = fullName;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getFullName() {
        return fullName;
    }

    public void setFullName(String fullName) {
        this.fullName = fullName;
    }
}
