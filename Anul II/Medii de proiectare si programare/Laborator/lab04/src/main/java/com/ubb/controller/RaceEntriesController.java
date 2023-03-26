package com.ubb.controller;

import com.ubb.model.Participant;
import com.ubb.model.Race;
import com.ubb.model.RaceEntry;
import com.ubb.model.User;
import com.ubb.repository.*;
import com.ubb.service.IParticipantService;
import com.ubb.service.IRaceService;
import com.ubb.service.ParticipantService;
import com.ubb.service.RaceService;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.image.Image;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.Collection;
import java.util.Properties;

public class RaceEntriesController extends AnchorPane {
    private IRaceService raceService;
    private IParticipantService participantService;
    private Properties properties;
    private Participant currentParticipant;
    private Stage currentStage;
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
        for (Race race : racesSelected) {
            raceService.saveRaceEntry(new RaceEntry(currentParticipant, race));
        }

        try {
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/views/home.fxml"));
            Scene scene = new Scene(fxmlLoader.load());
            HomeController controller = fxmlLoader.getController();
            controller.init(properties, currentUser, currentStage);
            currentStage.setTitle("MXGP Admin Panel - Home");
            currentStage.setScene(scene);
            currentStage.getIcons().add(new Image(String.valueOf(getClass().getResource("/img/icon.png"))));
            currentStage.show();
        } catch (IOException ioException) {
            System.out.println(ioException.getMessage());
        }
    }

    @FXML
    protected void onParticipantSelected() {
        currentParticipant = participantBox.getValue();
        loadRaces();
    }

    public void init(Properties properties, Stage currentStage, User currentUser) {
        initialise(properties, currentStage, currentUser);
        setParticipants();
        racesView.getSelectionModel().setSelectionMode(SelectionMode.MULTIPLE);
        loadRaces();
    }

    public void init(Properties properties, Stage currentStage, Participant currentParticipant, User currentUser) {
        initialise(properties, currentStage, currentUser);
        setNewlyCreatedParticipant(currentParticipant);
        racesView.getSelectionModel().setSelectionMode(SelectionMode.MULTIPLE);
        loadRaces();
    }

    private void initialise(Properties properties, Stage currentStage, User currentUser) {
        this.currentUser = currentUser;
        this.properties = properties;
        final IRaceRepository raceRepository = new RaceDBRepository(properties);
        final IParticipantRepository participantRepository = new ParticipantDBRepository(properties);
        final IRaceEntryRepository raceEntryRepository =
                new RaceEntryDBRepository(properties, raceRepository, participantRepository);
        raceService = new RaceService(raceRepository, raceEntryRepository);
        participantService = new ParticipantService(participantRepository);
        this.currentStage = currentStage;
    }

    private void setNewlyCreatedParticipant(Participant participant) {
        currentParticipant = participant;
        participantBox.getItems().clear();
        participantBox.getItems().add(currentParticipant);
        participantBox.getSelectionModel().clearAndSelect(0);
    }

    private void setParticipants() {
        participantBox.getItems().clear();
        Collection<Participant> participants = participantService.findAll();
        participantBox.getItems().addAll(participants);
        participantBox.getSelectionModel().clearAndSelect(0);
        currentParticipant = participantBox.getValue();
    }

    private void loadRaces() {
        racesView.getItems().clear();
        Collection<Race> races = raceService
                .getRacesWhereNotRegisteredAndEngineCapacity(
                        currentParticipant.getID(), currentParticipant.getEngineCapacity());
        racesView.getItems().addAll(races);
        if (races.size() > 0) {
            racesFoundLabel.setText(races.size() + " races found, "
                    + currentParticipant.getEngineCapacity() + "cc class");
        } else {
            racesFoundLabel.setText("No races found for " + currentParticipant.getEngineCapacity() + "cc class");
        }
    }
}
