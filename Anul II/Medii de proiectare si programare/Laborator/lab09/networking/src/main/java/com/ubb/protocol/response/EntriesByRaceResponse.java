package com.ubb.protocol.response;

import com.ubb.model.RaceEntry;

import java.util.Collection;

public class EntriesByRaceResponse implements Response {
    private final Collection<RaceEntry> entries;

    public EntriesByRaceResponse(Collection<RaceEntry> entries) {
        this.entries = entries;
    }

    public Collection<RaceEntry> getEntries() {
        return entries;
    }
}
