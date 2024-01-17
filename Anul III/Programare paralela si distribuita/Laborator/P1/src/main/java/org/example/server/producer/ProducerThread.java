package org.example.server.producer;

import lombok.val;
import org.example.networking.request.FinishRequest;
import org.example.networking.request.IntermediateRequest;
import org.example.networking.request.Request;
import org.example.networking.request.SendPointsRequest;
import org.example.networking.response.FinishResponse;
import org.example.networking.response.IntermediateResponse;
import org.example.networking.response.ReceivedPointsResponse;
import org.example.networking.response.Response;
import org.example.server.leaderboard.CustomQueue;
import org.example.server.leaderboard.LeaderboardsHelper;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicLong;

public class ProducerThread implements Runnable {
    private final Socket socket;
    private boolean connected;
    private final AtomicInteger connections;
    private final ObjectInputStream input;
    private final ObjectOutputStream output;
    private final CustomQueue customQueue;
    private final LeaderboardsHelper leaderboardsHelper;
    private final AtomicLong timeOfLastCachedLeaderboard;
    private final List<String> currentCountryLeaderboardCache;

    private final long delta;

    public ProducerThread(Socket socket,
                          CustomQueue customQueue,
                          AtomicInteger connections,
                          LeaderboardsHelper leaderboardsHelper,
                          ObjectInputStream input,
                          ObjectOutputStream output,
                          List<String> currentCountryLeaderboardCache,
                          AtomicLong timeOfLastCachedLeaderboard,
                          long delta) {
        this.customQueue = customQueue;
        this.connections = connections;
        this.leaderboardsHelper = leaderboardsHelper;
        this.socket = socket;
        this.input = input;
        this.output = output;
        this.currentCountryLeaderboardCache = currentCountryLeaderboardCache;
        this.timeOfLastCachedLeaderboard = timeOfLastCachedLeaderboard;
        this.delta = delta;
        this.connected = true;
    }

    private Response handleRequest(Request request) throws InterruptedException {
        Response response=null;
        if (request instanceof SendPointsRequest newRequest) {
            for (String player : newRequest.data()) {
                val playerFormat = player + " " + newRequest.country();
                customQueue.produce(playerFormat);
            }

            response = new ReceivedPointsResponse();
        } else if (request instanceof IntermediateRequest) {
            val currentTime = System.nanoTime();
            val elapsedTime = TimeUnit.NANOSECONDS.toMillis(currentTime - timeOfLastCachedLeaderboard.get());
            if (currentCountryLeaderboardCache.isEmpty() || elapsedTime >= delta) {
                System.out.println("Current country leaderboard is sending");
                val futureResult = calculateCurrentCountryLeaderboard();

                // Wait for the CompletableFuture to complete
                val result = futureResult.join();
                // Set the response
                response = new IntermediateResponse(result);

                synchronized (currentCountryLeaderboardCache) {
                    currentCountryLeaderboardCache.clear();
                    currentCountryLeaderboardCache.addAll(result);
                }
                timeOfLastCachedLeaderboard.set(System.nanoTime());
                System.out.println(currentCountryLeaderboardCache);
            } else {
                System.out.println("The cached country leaderboard is sending");
                response = new IntermediateResponse(currentCountryLeaderboardCache);
                System.out.println(currentCountryLeaderboardCache);
            }
        } else if (request instanceof FinishRequest) {
            System.out.println("Final response");
            response = new FinishResponse();
            connected = false;
        }
        return response;
    }

    private CompletableFuture<List<String>> calculateCurrentCountryLeaderboard() {
        // Asynchronous task
        return CompletableFuture.supplyAsync(leaderboardsHelper::getCurrentCountryLeaderboard);
    }

    private void sendResponse(Response response) throws IOException {
        synchronized (output) {
            output.writeObject(response);
            output.flush();
        }
    }

    @Override
    public void run() {
        while (connected) {
            try {
                val request = input.readObject();
                val response = handleRequest((Request)request);
                if (response != null) {
                    sendResponse(response);
                }
            } catch (IOException | InterruptedException | ClassNotFoundException e) {
                e.printStackTrace();
            }
        }

        connections.decrementAndGet();
        System.out.println("Remaining clients:" + connections.get());
    }
}
