package com.ubb.controller;

import com.ubb.IContestServices;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.Objects;

public class NewRaceController extends AnchorPane {
    private IContestServices server;
    private Stage currentStage;

    @FXML
    private TextField nameField;

    @FXML
    private TextField engineCapacityField;

    @FXML
    protected void onConfirmClicked() {
        if (!Objects.equals(nameField.getText(), "") && !Objects.equals(engineCapacityField.getText(), "")) {
            String name = nameField.getText();
            Integer engineCapacity = Integer.parseInt(engineCapacityField.getText().replace(",", ""));
            //raceService.save(new Race(name, engineCapacity));
        }

        try {
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/views/home.fxml"));
            Scene scene = new Scene(fxmlLoader.load());
            HomeController controller = fxmlLoader.getController();
            controller.init(server, currentStage);
            currentStage.setScene(scene);
            currentStage.getIcons().add(new Image(String.valueOf(getClass().getResource("/img/icon.png"))));
            currentStage.show();
        } catch (IOException ioException) {
            System.out.println(ioException.getMessage());
        }
    }

    public void init(IContestServices server, Stage currentStage) {
        currentStage.setTitle("MXGP - Register New Race");
        this.server = server;
        this.currentStage = currentStage;
        ControllerUtils.addInputNumberFormatter(engineCapacityField);
    }
}
