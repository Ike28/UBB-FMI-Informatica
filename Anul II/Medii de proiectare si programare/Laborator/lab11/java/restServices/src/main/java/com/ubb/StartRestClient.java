package com.ubb;

import com.ubb.client.RestClient;
import com.ubb.model.Race;

import java.util.Arrays;
import java.util.List;

public class StartRestClient {
    private final static RestClient restClient = new RestClient();
    private static Race updatedRace = null;

    public static void main(String[] args) {
        Race newRace = new Race("Grand Prix of Bacau", 1000);

        try {
            show(() -> {
                System.out.println("\n\nTest create:\n\n");
                try {
                    Race result = restClient.create(newRace);
                    System.out.println(result);
                    setCreatedRace(result);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            });

            show(() -> {
                System.out.println("\n\nTest find all");
                try {
                    List<Race> result = Arrays.stream(restClient.getAll()).toList();
                    result.forEach(System.out::println);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            });

            show(() -> {
                System.out.println("\n\nTest find by ID");
                try {
                    System.out.println(restClient.getById(updatedRace.getId()));
                } catch (Exception e) {
                    e.printStackTrace();
                }
            });

            show(() -> {
                System.out.println("\n\nTest update");
                try {
                    updatedRace.setEngineCapacity(900);
                    restClient.update(updatedRace);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            });

            show(() -> {
                System.out.println("\n\nTest delete");
                try {
                    restClient.delete(updatedRace.getId());
                } catch (Exception e) {
                    e.printStackTrace();
                }
            });
        } catch (Exception e) {
            System.out.println();
        }
    }

    private static void show(Runnable task) {
        try {
            task.run();
        } catch (Exception e) {
            System.out.println("Services exception: " + e);
        }
    }

    private static void setCreatedRace(Race race) {
        updatedRace = race;
    }
}
