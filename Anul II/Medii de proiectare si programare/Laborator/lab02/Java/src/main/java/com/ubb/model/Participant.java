package com.ubb.model;

import java.util.Objects;
import java.util.Optional;

public class Participant extends Identifiable<Long> {
    private String firstName;
    private String lastName;
    private Integer engineCapacity;
    private Team team;

    public Participant(Long ID, String firstName, String lastName, Integer engineCapacity) {
        setID(ID);
        this.firstName = firstName;
        this.lastName = lastName;
        this.engineCapacity = engineCapacity;
        team = null;
    }

    public Participant(Long ID, String firstName, String lastName, Integer engineCapacity, Team team) {
        setID(ID);
        this.firstName = firstName;
        this.lastName = lastName;
        this.engineCapacity = engineCapacity;
        this.team = team;
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

    public Optional<Team> getTeam() {
        if (team != null) {
            return Optional.of(team);
        }
        return Optional.empty();
    }

    public void setTeam(Team team) {
        this.team = team;
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
