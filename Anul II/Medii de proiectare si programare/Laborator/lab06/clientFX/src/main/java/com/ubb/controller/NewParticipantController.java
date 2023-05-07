package com.ubb.controller;

import com.ubb.IContestServices;
import com.ubb.exceptions.ContestDataException;
import com.ubb.model.Participant;
import com.ubb.model.Team;
import com.ubb.model.User;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.Collection;
import java.util.Objects;

public class NewParticipantController extends AnchorPane {
    private IContestServices server;
    private Stage currentStage;
    private User currentUser;

    @FXML
    private TextField firstnameField;

    @FXML
    private TextField lastnameField;

    @FXML
    private TextField engineCapacityField;

    @FXML
    private ComboBox<Team> teamBox;

    @FXML
    private Button confirmButton;

    @FXML
    protected void onConfirmClicked() {
        String firstName = firstnameField.getText();
        String lastName = lastnameField.getText();
        Integer engineCapacity = Integer.parseInt(engineCapacityField.getText().replace(",", ""));
        Team selected = teamBox.getValue();

        Participant newParticipant = new Participant(firstName, lastName, engineCapacity);
        if (!Objects.equals(selected.getName(), "None")) {
            newParticipant.setTeamID(selected.getID());
        }
        try {
            server.saveParticipant(newParticipant);
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
        try {
            currentStage.setTitle("MXGP - New Participant");
            this.server = server;
            this.currentStage = currentStage;
            this.currentUser = currentUser;

            ControllerUtils.addInputNumberFormatter(engineCapacityField);
            clearFields();
            fillTeamBox();
        } catch (ContestDataException contestDataException) {
            AlertController.showError(currentStage, contestDataException.getMessage());
        }
    }

    private void clearFields() {
        firstnameField.clear();
        lastnameField.clear();
        engineCapacityField.clear();
        teamBox.getSelectionModel().clearSelection();
    }

    private void fillTeamBox() throws ContestDataException {
        teamBox.getItems().clear();
        teamBox.getItems().add(new Team("None"));
        Collection<Team> teams = server.findAllTeams();
        teamBox.getItems().addAll(teams);
    }
}
