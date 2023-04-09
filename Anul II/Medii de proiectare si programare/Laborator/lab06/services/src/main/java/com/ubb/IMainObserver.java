package com.ubb;

import com.ubb.exceptions.RacesException;
import com.ubb.model.Participant;
import com.ubb.model.data.RaceDTO;

public interface IMainObserver {
    void raceAdded(RaceDTO race) throws RacesException;
    void participantAdded(Participant participant) throws RacesException;
    void raceEntriesAdded() throws RacesException;
}
