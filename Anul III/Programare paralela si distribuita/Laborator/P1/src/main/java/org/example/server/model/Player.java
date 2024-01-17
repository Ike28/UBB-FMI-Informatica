package org.example.server.model;

import lombok.Getter;

@Getter
public class Player {
    private final String id;
    private int score;
    private final String country;

    public Player(String id, int score, String country) {
        this.id = id;
        this.score = score;
        this.country = country;
    }

    public void addScore(int score) {
        this.score += score;
    }

    @Override
    public boolean equals(Object obj) {
        return obj instanceof Player && this.id.equals(((Player) obj).id);
    }

    @Override
    public String toString() {
        return id + " " + score + " " + country;
    }
}
