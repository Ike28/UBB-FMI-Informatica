package com.ubb.model.data;

public class RaceDTO {
    private final String name;
    private final Integer engineCapacity;
    private final Integer participants;

    public RaceDTO(String name, Integer engineCapacity, Integer participants) {
        this.name = name;
        this.engineCapacity = engineCapacity;
        this.participants = participants;
    }

    public String getName() {
        return name;
    }

    public Integer getEngineCapacity() {
        return engineCapacity;
    }

    public Integer getParticipants() {
        return participants;
    }
}
