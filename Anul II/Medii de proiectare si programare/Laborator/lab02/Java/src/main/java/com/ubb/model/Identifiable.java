package com.ubb.model;

public class Identifiable<ID> {
    private ID id;

    public ID getID() {
        return id;
    }

    protected void setID(ID newID) {
        id = newID;
    }
}
