package com.ubb.model;

public class Race extends Identifiable<Long> {
    private String name;
    private Integer engineCapacity;

    {
        setId(0L);
    }
    
    public Race() {

    }

    public Race(String name, Integer engineCapacity) {
        this.name = name;
        this.engineCapacity = engineCapacity;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Integer getEngineCapacity() {
        return engineCapacity;
    }

    public void setEngineCapacity(Integer engineCapacity) {
        this.engineCapacity = engineCapacity;
    }

    @Override
    public String toString() {
        return getName();
    }
}
