package com.ubb;

import com.ubb.controller.MainController;
import com.ubb.protocol.ServicesProxyI;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.Properties;

public class StartClient extends Application {
    private static final int DEFAULT_PORT = 25564;
    private static final String DEFAULT_SERVER = "localhost";

    @Override
    public void start(Stage primaryStage) {
        final Properties clientProperties = new Properties();
        try {
            clientProperties.load(StartClient.class.getResourceAsStream("/client.properties"));
            System.out.println("Client properties set.");
            clientProperties.list(System.out);
        } catch (IOException ioException) {
            System.out.println("Cannot find client.properties: " + ioException.getMessage());
            return;
        }

        String serverIP = clientProperties.getProperty("server.host", DEFAULT_SERVER);
        int serverPort = DEFAULT_PORT;

        try {
            serverPort = Integer.parseInt(clientProperties.getProperty("server.port"));
        } catch (NumberFormatException numberFormatException) {
            System.out.println("Wrong port number: " + numberFormatException.getMessage());
            System.out.println("Using default port: " + DEFAULT_PORT);
        }

        System.out.println("Using IP " + serverIP + ":" + serverPort);
        IContestServices server = new ServicesProxyI(serverIP, serverPort);
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/views/main-view.fxml"));
            Scene scene = new Scene(fxmlLoader.load());
            MainController controller = fxmlLoader.getController();
            controller.init(server, primaryStage);
            primaryStage.setScene(scene);
            primaryStage.getIcons().add(new Image(String.valueOf(getClass().getResource("/img/icon.png"))));
            primaryStage.show();
        } catch (IOException ioException) {
            System.out.println(ioException.getMessage());
        }
    }

    public static void main(String[] args) {
        Application.launch();
    }
}
