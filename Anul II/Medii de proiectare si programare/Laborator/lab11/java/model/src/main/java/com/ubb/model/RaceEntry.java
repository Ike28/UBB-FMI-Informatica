package com.ubb.model;

import java.util.Objects;

public class RaceEntry extends Identifiable<Long> {
    private final Participant participant;
    private final Race race;

    {
        setId(0L);
    }

    public RaceEntry(Participant participant, Race race) {
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

    @Override
    public String toString() {
        return participant.getFirstName() + " " + participant.getLastName() + " registered for '"
                + race.getName() + " " + race.getEngineCapacity() + "cc'";
    }
}
