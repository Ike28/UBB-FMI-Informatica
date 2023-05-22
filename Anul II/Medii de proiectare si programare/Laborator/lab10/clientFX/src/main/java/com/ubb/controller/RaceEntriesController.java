package com.ubb.controller;

import com.ubb.IContestServices;
import com.ubb.exceptions.ContestDataException;
import com.ubb.model.Participant;
import com.ubb.model.Race;
import com.ubb.model.RaceEntry;
import com.ubb.model.User;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.image.Image;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

public class RaceEntriesController extends AnchorPane {
    private IContestServices server;
    private Stage currentStage;
    private Participant currentParticipant;
    private User currentUser;

    @FXML
    private ComboBox<Participant> participantBox;

    @FXML
    private ListView<Race> racesView;

    @FXML
    private Label racesFoundLabel;

    @FXML
    private Button confirmButton;

    @FXML
    protected void onConfirmClicked() {
        ObservableList<Race> racesSelected = racesView.getSelectionModel().getSelectedItems();
        List<RaceEntry> raceEntries = new ArrayList<>();
        for (Race race : racesSelected) {
            raceEntries.add(new RaceEntry(currentParticipant, race));
        }
        try {
            server.saveRaceEntries(raceEntries);
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

    @FXML
    protected void onParticipantSelected() {
        currentParticipant = participantBox.getValue();
        loadRaces();
    }

    public void init(IContestServices server, Stage currentStage, User currentUser) {
        try {
            this.server = server;
            this.currentStage = currentStage;
            this.currentUser = currentUser;
            setParticipants();
            racesView.getSelectionModel().setSelectionMode(SelectionMode.MULTIPLE);
            loadRaces();
        } catch (ContestDataException contestDataException) {
            AlertController.showError(currentStage, contestDataException.getMessage());
        }
    }

    private void setParticipants() throws ContestDataException {
        participantBox.getItems().clear();
        Collection<Participant> participants = server.findAllParticipants();
        participantBox.getItems().addAll(participants);
        participantBox.getSelectionModel().clearAndSelect(0);
        currentParticipant = participantBox.getValue();
    }

    private void loadRaces() {
        try {
            racesView.getItems().clear();
            Collection<Race> races = server
                    .getRacesWhereNotRegisteredAndEngineCapacity(
                            currentParticipant.getId(), currentParticipant.getEngineCapacity());
            racesView.getItems().addAll(races);
            if (races.size() > 0) {
                racesFoundLabel.setText(races.size() + " races found, "
                        + currentParticipant.getEngineCapacity() + "cc class");
            } else {
                racesFoundLabel.setText("No races found for " + currentParticipant.getEngineCapacity() + "cc class");
            }
        } catch (ContestDataException contestDataException) {
            AlertController.showError(currentStage, contestDataException.getMessage());
        }
    }
}
