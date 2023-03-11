package com.ubb.model;

import java.util.Objects;

public class RaceEntry extends Identifiable<Long> {
    private Participant participant;
    private Race race;

    public RaceEntry(Long ID, Participant participant, Race race) {
        setID(ID);
        this.participant = participant;
        this.race = race;
    }

    public Participant getParticipant() {
        return participant;
    }

    public Race getRace() {
        return race;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        RaceEntry raceEntry = (RaceEntry) o;
        return getParticipant().equals(raceEntry.getParticipant()) && getRace().equals(raceEntry.getRace());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getParticipant(), getRace());
    }
}
