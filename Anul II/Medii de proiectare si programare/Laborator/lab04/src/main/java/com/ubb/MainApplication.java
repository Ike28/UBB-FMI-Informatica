package com.ubb;

import com.ubb.controller.MainController;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.stage.Stage;

import java.io.FileReader;
import java.io.IOException;
import java.util.Properties;

public class MainApplication extends Application {
    @Override
    public void start(Stage primaryStage) {
        final Properties properties = new Properties();
        try {
            properties.load(new FileReader("bd.properties"));

            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/views/main-view.fxml"));
            Scene scene = new Scene(fxmlLoader.load());
            MainController controller = fxmlLoader.getController();
            controller.init(properties, primaryStage);
            primaryStage.setScene(scene);
            primaryStage.getIcons().add(new Image(String.valueOf(getClass().getResource("/img/icon.png"))));
            primaryStage.show();
        } catch (IOException ioException) {
            System.out.println(ioException.getMessage());
        }
    }

    public static void main(String[] args) {
        launch();
    }
}
