package org.example.server;

import lombok.val;
import org.example.server.consumer.ConsumerThread;
import org.example.server.leaderboard.CustomLinkedList;
import org.example.server.leaderboard.CustomQueue;
import org.example.server.leaderboard.LeaderboardsHelper;
import org.example.server.producer.ProducerThread;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.concurrent.CopyOnWriteArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicLong;

public class Server {
    private final static int PORT = 12345;
    private static int p_consumers = 4;
    private static int p_producers = 4;
    private static int p_clients = 5;
    private static long delta = 100;
    private static AtomicInteger connectionsCount;
    private static CustomQueue customQueue;
    private static CustomLinkedList players;
    private static Set<String> bannedPlayers;
    private static ExecutorService threadPool;
    private static ConsumerThread[] threads;
    private static LeaderboardsHelper leaderboardsHelper;
    private static List<String> currentCountryLeaderboardCache;
    private static AtomicLong timeWhenTheCountryLeaderboardWasSent;


    public static void main(String[] args) {
        if (args.length == 3) {
            try {
                p_consumers = Integer.parseInt(args[0]);
                p_producers = Integer.parseInt(args[1]);
                delta = Integer.parseInt(args[2]);
                // in test cases p_consumer=p_r, p_producer=p_w and delta=time
                System.out.println("args:" + p_consumers + " " + p_producers + " " + delta);

                connectionsCount = new AtomicInteger(p_clients);
                customQueue = new CustomQueue(100, p_consumers);
                players = new CustomLinkedList();
                bannedPlayers = new HashSet<>();
                threadPool = Executors.newFixedThreadPool(p_producers);
                threads = new ConsumerThread[p_consumers];
                leaderboardsHelper = new LeaderboardsHelper(players);
                currentCountryLeaderboardCache = new CopyOnWriteArrayList<>();
                timeWhenTheCountryLeaderboardWasSent = new AtomicLong(0);
            } catch (NumberFormatException e) {
                System.err.println("Invalid arguments");
            }
        }
        val startTime = System.nanoTime();
        startConsumers();

        try {
            val serverSocket = new ServerSocket(PORT);
            System.out.println("Started Server on port " + PORT);

            val clientSockets = new ArrayList<Socket>();

            for (int i=0;i<p_clients;i++) {
                val clientSocket = serverSocket.accept();
                clientSockets.add(clientSocket);
                System.out.println("Client has connected: " + clientSocket.getInetAddress());

                val producerThread = getProducerThread(clientSocket);
                threadPool.submit(producerThread);
            }
            threadPool.shutdown();

            while (!threadPool.isTerminated()) { }
            joinConsumers();

            for (val clientSocket : clientSockets) {
                System.out.println("Final leaderboard is sending");

                val outputStream = new DataOutputStream(clientSocket.getOutputStream());

                sendFile("src/main/java/org/example/server/resources/Clasament_tari.txt", outputStream);
                sendFile("src/main/java/org/example/server/resources/Clasament_conc.txt", outputStream);

                clientSocket.close();
            }

            val endTime = System.nanoTime();
            val elapsedTime = TimeUnit.NANOSECONDS.toMillis(endTime - startTime);
            System.out.println("Elapsed time: " + elapsedTime + " milliseconds");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static ProducerThread getProducerThread(Socket clientSocket) throws IOException {
        val output = new ObjectOutputStream(clientSocket.getOutputStream());
        output.flush();
        val input = new ObjectInputStream(clientSocket.getInputStream());

        // Create a new thread to handle the client
        return new ProducerThread(
                clientSocket,
                customQueue,
                connectionsCount,
                leaderboardsHelper,
                input,
                output,
                currentCountryLeaderboardCache,
                timeWhenTheCountryLeaderboardWasSent,
                delta
        );
    }

    private static void startConsumers() {
        for (int i = 0; i < p_consumers; i++) {
            threads[i] = new ConsumerThread(players, bannedPlayers, customQueue, connectionsCount, leaderboardsHelper);
            threads[i].start();
        }
    }

    private static void joinConsumers() {
        for (int i = 0; i < p_consumers; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    private static void sendFile(String filePath, DataOutputStream outputStream) throws IOException {
        val file = new File(filePath);
        val fileSize = file.length();

        // Send the size of the file
        outputStream.writeLong(fileSize);

        try (val fis = new FileInputStream(file);
             val bis = new BufferedInputStream(fis)) {

            val buffer = new byte[4096];
            int bytesRead;
            while ((bytesRead = bis.read(buffer)) != -1) {
                outputStream.write(buffer, 0, bytesRead);
            }
            outputStream.flush();
        }
    }
}
