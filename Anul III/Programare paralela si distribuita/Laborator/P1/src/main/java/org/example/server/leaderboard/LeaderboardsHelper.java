package org.example.server.leaderboard;

import lombok.val;
import org.example.server.model.Player;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class LeaderboardsHelper {
    private final CustomLinkedList players;
    public LeaderboardsHelper(CustomLinkedList players) {
        this.players = players;
    }

    public List<String> getCurrentCountryLeaderboard() {

        val leaderboard = new HashMap<String, Integer>();

        //copy list so that it does not modify during iteration
        val playersCopy = players.copyToList();

        //System.out.println(playersCopy);
        var count = 0;
        for (Player player : playersCopy) {
            //System.out.println(player);
            count++;
            val country = player.getCountry();
            val score = player.getScore();

            // Check if the country is present in the leaderboard
            if (leaderboard.containsKey(country)) {
                // Update the score by adding the additional score
                val currentScore = leaderboard.get(country);
                val newScore = currentScore + score;
                leaderboard.put(country, newScore);
            } else
                leaderboard.put(country, score);
        }

        // Sort descending
        return leaderboard.entrySet().stream()
                .sorted(Map.Entry.<String, Integer>comparingByValue().reversed())
                .map(entry -> entry.getKey() + " " + entry.getValue())
                .collect(Collectors.toList());
    }

    public void writePlayerLeaderboardToFile() {
        try (val writer = new BufferedWriter(
                new FileWriter("src/main/java/org/example/server/resources/Clasament_conc.txt"))) {
            val playerList = new ArrayList<Player>();
            for (Player p : players) playerList.add(p);
            playerList.sort((o1, o2) -> o2.getScore() - o1.getScore());

            System.out.println("List players: " + playerList.size());
            for (val p : playerList) {
                writer.write(p.getId() + " " + p.getScore() + "\n");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void writeCountryLeaderboardToFile() {
        val countryLeaderboard = getCurrentCountryLeaderboard();
        try (val writer = new BufferedWriter(
                new FileWriter("src/main/java/org/example/server/resources/Clasament_tari.txt"))) {
            for (String country : countryLeaderboard) {
                writer.write(country);
                writer.newLine();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
