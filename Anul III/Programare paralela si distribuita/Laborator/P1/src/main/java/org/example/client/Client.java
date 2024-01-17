package org.example.client;

import lombok.val;
import org.example.client.worker.ClientThread;

import java.io.File;
import java.util.ArrayList;

public class Client {
    private static final int problemsCount = 10;
    private static final int countriesCount = 5;
    private static final ClientThread[] clients = new ClientThread[countriesCount];

    private static void createClients() {
        for (int i = 1; i <= countriesCount; i++) {
            val fileNames = new ArrayList<String>();
            val country = "C" + i;
            for (int p = 1; p <= problemsCount; p++) {
                val filename = "src/main/java/org/example/client/resources/Rezultate" + country + "_P" + p + ".txt";
                val absolutePath = new File(filename).getAbsolutePath();
                System.out.println("Absolute Path: " + absolutePath);

                fileNames.add(filename);
            }
            clients[i - 1] = new ClientThread(country,fileNames);
        }
    }
    private static void startClients() {
        for (var client : clients) {
            client.start();
        }
    }
    private static void joinClients() {
        for (val clientThread : clients) {
            try {
                clientThread.join();
            } catch (Exception exception) {
                exception.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        createClients();
        startClients();
        joinClients();
    }
}
