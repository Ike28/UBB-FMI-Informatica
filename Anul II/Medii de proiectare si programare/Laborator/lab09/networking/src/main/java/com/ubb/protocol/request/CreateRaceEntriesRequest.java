package com.ubb.protocol.request;

import com.ubb.model.RaceEntry;

import java.util.List;

public class CreateRaceEntriesRequest implements Request {
    private final List<RaceEntry> raceEntries;

    public CreateRaceEntriesRequest(List<RaceEntry> raceEntries) {
        this.raceEntries = raceEntries;
    }

    public List<RaceEntry> getRaceEntries() {
        return raceEntries;
    }
}
