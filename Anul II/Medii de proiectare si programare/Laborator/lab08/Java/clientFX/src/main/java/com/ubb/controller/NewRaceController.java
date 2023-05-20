package com.ubb.controller;

import com.ubb.IContestServices;
import com.ubb.exceptions.ContestDataException;
import com.ubb.model.Race;
import com.ubb.model.User;
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
    private User currentUser;

    @FXML
    private TextField nameField;

    @FXML
    private TextField engineCapacityField;

    @FXML
    protected void onConfirmClicked() {
        try {
            if (!Objects.equals(nameField.getText(), "") && !Objects.equals(engineCapacityField.getText(), "")) {
                String name = nameField.getText();
                Integer engineCapacity = Integer.parseInt(engineCapacityField.getText().replace(",", ""));
                server.saveRace(new Race(name, engineCapacity));
            }
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/views/home.fxml"));
            Scene scene = new Scene(fxmlLoader.load());
            MainController controller = fxmlLoader.getController();
            controller.init(server, currentStage, currentUser);
            currentStage.setScene(scene);
            currentStage.getIcons().add(new Image(String.valueOf(getClass().getResource("/img/icon.png"))));
            currentStage.show();
        } catch (IOException | ContestDataException exception) {
            AlertController.showError(currentStage, exception.getMessage());
        }
    }

    public void init(IContestServices server, Stage currentStage, User currentUser) {
        currentStage.setTitle("MXGP - Register New Race");
        this.server = server;
        this.currentStage = currentStage;
        this.currentUser = currentUser;
        ControllerUtils.addInputNumberFormatter(engineCapacityField);
    }
}
