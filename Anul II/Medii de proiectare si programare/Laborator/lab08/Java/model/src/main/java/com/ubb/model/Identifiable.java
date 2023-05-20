package com.ubb.model;

import java.io.Serializable;

public class Identifiable<ID> implements Serializable {
    private ID id;

    public ID getId() {
        return id;
    }

    public void setId(ID newID) {
        id = newID;
    }
}
