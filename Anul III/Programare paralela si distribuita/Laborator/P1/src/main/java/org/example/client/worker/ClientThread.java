package org.example.client.worker;

import lombok.val;
import org.example.networking.request.FinishRequest;
import org.example.networking.request.IntermediateRequest;
import org.example.networking.request.Request;
import org.example.networking.request.SendPointsRequest;
import org.example.networking.response.FinishResponse;
import org.example.networking.response.IntermediateResponse;
import org.example.networking.response.Response;

import java.io.*;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

public class ClientThread extends Thread {
    private Socket socket;
    private ObjectInputStream inputStream;
    private ObjectOutputStream outputStream;
    private static final int PORT = 12345;
    private static final String SERVER_ADDRESS = "localhost";
    private final String country;
    private final List<String> fileNames;

    private final int deltaX = 1000;

    public ClientThread(String country, List<String> fileNames) {
        this.country = country;
        this.fileNames = fileNames;
    }

    @Override
    public void run() {
        try {
            openConnection();

            for (val fileName : fileNames) {
                try (val reader = new BufferedReader(new FileReader(fileName))) {
                    String line;
                    val scores = new ArrayList<String>();
                    while ((line = reader.readLine()) != null) {
                        scores.add(line);
                        if (scores.size() == 20) {
                            Thread.sleep(deltaX);   //Simuleaza interactiune cu interfata

                            //Trimite punctaje
                            sendRequest(new SendPointsRequest(country, scores.toArray(new String[0])));
                            getResponse();
                            scores.clear();
                        }
                    }
                }

                //primire clasament tari
                sendRequest(new IntermediateRequest());
                val intermediateResponse = (IntermediateResponse) getResponse();
                if (intermediateResponse != null) {
                    System.out.println("Country " + country + " Async result:" + intermediateResponse.data());
                }
            }
            sendRequest(new FinishRequest());
            val responseFinal = (FinishResponse) getResponse();

            val inputStream = new DataInputStream(socket.getInputStream());

            val countryLeaderboardPathFormat = String.format("src/main/java/org/example/client/resources/Clasament_tari_%s.txt", country);
            val participantsLeaderboardPathFormat = String.format("src/main/java/org/example/client/resources/Clasament_conc_%s.txt", country);

            receiveFile(countryLeaderboardPathFormat, inputStream);
            System.out.println("Received final country leaderboard");

            receiveFile(participantsLeaderboardPathFormat, inputStream);
            System.out.println("Received participants final leaderboard");

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    private void openConnection() throws IOException {
        socket = new Socket(SERVER_ADDRESS, PORT);
        outputStream = new ObjectOutputStream(socket.getOutputStream());
        outputStream.flush();
        inputStream = new ObjectInputStream(socket.getInputStream());
    }

    private void sendRequest(Request request) {
        try {
            outputStream.writeObject(request);
            outputStream.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private Response getResponse() {
        try {
            return (Response) inputStream.readObject();
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }


    private void receiveFile(String filePath, DataInputStream dataStream) throws IOException {
        try (val fileOutput = new FileOutputStream(filePath);
             val outputStream = new BufferedOutputStream(fileOutput)) {

            // Read the file size
            val fileSize = dataStream.readLong();
            var totalRead = 0;
            val buffer = new byte[4096];
            int bytesRead;
            while (totalRead < fileSize
                    && (bytesRead = dataStream.read(buffer, 0, (int) Math.min(buffer.length, fileSize - totalRead))) != -1) {
                outputStream.write(buffer, 0, bytesRead);
                totalRead += bytesRead;
            }
            outputStream.flush();
        }
    }
}
