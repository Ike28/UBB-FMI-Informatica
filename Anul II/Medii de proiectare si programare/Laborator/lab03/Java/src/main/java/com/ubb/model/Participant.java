package com.ubb.model;

import java.util.Objects;
import java.util.Optional;

public class Participant extends Identifiable<Long> {
    private final String firstName;
    private final String lastName;
    private Integer engineCapacity;
    private Long teamID;

    {
        setID(0L);
        teamID = null;
    }

    public Participant(String firstName, String lastName, Integer engineCapacity) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.engineCapacity = engineCapacity;
    }

    public String getFirstName() {
        return firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public Integer getEngineCapacity() {
        return engineCapacity;
    }

    public void setEngineCapacity(Integer engineCapacity) {
        this.engineCapacity = engineCapacity;
    }

    public Optional<Long> getTeamID() {
        if (teamID != null) {
            return Optional.of(teamID);
        }
        return Optional.empty();
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
}
