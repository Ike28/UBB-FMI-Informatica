package com.ubb.protocol.request;

public class GetRacesByEngineCapacityRequest implements Request {
    private final Integer engineCapacity;

    public GetRacesByEngineCapacityRequest(Integer engineCapacity) {
        this.engineCapacity = engineCapacity;
    }

    public Integer getEngineCapacity() {
        return engineCapacity;
    }
}
