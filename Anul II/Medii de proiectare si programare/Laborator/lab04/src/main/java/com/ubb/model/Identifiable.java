package com.ubb.model;

public class Identifiable<ID> {
    private ID id;

    public ID getID() {
        return id;
    }

    public void setID(ID newID) {
        id = newID;
    }
}
