package com.ubb.model;

public class Team extends Identifiable<Long> {
    private String name;

    public Team(Long ID, String name) {
        setID(ID);
        this.name = name;
    }
}
