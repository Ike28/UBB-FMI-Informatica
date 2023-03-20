package com.ubb.model;

public class User extends Identifiable<Long> {
    private String username;
    private String fullName;
    private String passwordToken;

    {
        setID(0L);
        passwordToken = null;
    }

    public User(String username, String fullName) {
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

    public String getPasswordToken() {
        return passwordToken;
    }

    public void setPasswordToken(String passwordToken) {
        this.passwordToken = passwordToken;
    }

    @Override
    public String toString() {
        return "username=" + getUsername() + ": " + getFullName();
    }
}
