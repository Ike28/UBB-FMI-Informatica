package com.ubb;

import com.ubb.exceptions.ContestDataException;
import com.ubb.model.Participant;
import com.ubb.dto.RaceDTO;

import java.util.List;

public interface IMainObserver {
    void raceAdded(RaceDTO race) throws ContestDataException;
    void participantAdded(Participant participant) throws ContestDataException;
    void raceEntriesAdded(List<RaceDTO> races) throws ContestDataException;
}
