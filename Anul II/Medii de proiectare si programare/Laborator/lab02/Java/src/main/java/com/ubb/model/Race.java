package com.ubb.model;

public class Race extends Identifiable<Long> {
    private String name;
    private Integer engineCapacity;

    public Race(Long ID, String name, Integer engineCapacity) {
        setID(ID);
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
}
