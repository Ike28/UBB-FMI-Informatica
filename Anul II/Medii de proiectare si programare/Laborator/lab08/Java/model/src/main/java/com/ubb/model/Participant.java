package com.ubb.model;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import java.io.Serializable;
import java.util.Objects;

@Entity
public class Participant extends Identifiable<Long> implements Serializable {
    @Id
    @GeneratedValue
    private Long id;
    private String firstName;
    private String lastName;
    private Integer engineCapacity;
    private Long teamID;

    {
        teamID = null;
        setId(0L);
    }

    public Participant() {

    }

    public Participant(String firstName, String lastName, Integer engineCapacity) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.engineCapacity = engineCapacity;
    }

    @Override
    public Long getId() {
        return this.id;
    }

    @Override
    public void setId(Long id) {
        this.id = id;
    }

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String name) {
        this.firstName = name;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String name) {
        this.lastName = name;
    }

    public String getFullName() {
        return getFirstName() + " " + getLastName();
    }

    public Integer getEngineCapacity() {
        return engineCapacity;
    }

    public void setEngineCapacity(Integer engineCapacity) {
        this.engineCapacity = engineCapacity;
    }

    public Long getTeamID() {
        return teamID;
    }

    public void setTeamID(Long teamID) {
        this.teamID = teamID;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Participant that = (Participant) o;
        return getFirstName().equals(that.getFirstName()) && getLastName().equals(that.getLastName())
                && getEngineCapacity().equals(that.getEngineCapacity());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getFirstName(), getLastName(), getEngineCapacity());
    }

    @Override
    public String toString() {
        return getFullName();
    }
}
