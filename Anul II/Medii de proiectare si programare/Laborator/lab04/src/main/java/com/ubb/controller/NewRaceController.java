package com.ubb.controller;

import com.ubb.model.Race;
import com.ubb.model.User;
import com.ubb.service.IRaceService;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.Properties;

public class NewRaceController extends AnchorPane {
    private IRaceService raceService;
    private Properties properties;
    private User currentUser;
    private Stage currentStage;

    @FXML
    private TextField nameField;

    @FXML
    private TextField engineCapacityField;

    @FXML
    protected void onConfirmClicked() {
        String name = nameField.getText();
        Integer engineCapacity = Integer.parseInt(engineCapacityField.getText().replace(",", ""));
        raceService.save(new Race(name, engineCapacity));

        try {
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/views/home.fxml"));
            Scene scene = new Scene(fxmlLoader.load());
            HomeController controller = fxmlLoader.getController();
            controller.init(properties, currentUser, currentStage);
            currentStage.setScene(scene);
            currentStage.getIcons().add(new Image(String.valueOf(getClass().getResource("/img/icon.png"))));
            currentStage.show();
        } catch (IOException ioException) {
            System.out.println(ioException.getMessage());
        }
    }

    public void init(Properties properties, IRaceService raceService, User currentUser, Stage currentStage) {
        currentStage.setTitle("MXGP - Register New Race");
        this.properties = properties;
        this.raceService = raceService;
        this.currentStage = currentStage;
        this.currentUser = currentUser;
        ControllerUtils.addInputNumberFormatter(engineCapacityField);
    }
}
