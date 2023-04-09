package com.ubb.controller;

import com.ubb.IContestServices;
import com.ubb.model.Participant;
import com.ubb.model.Race;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.image.Image;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;

public class RaceEntriesController extends AnchorPane {
    private IContestServices server;
    private Stage currentStage;

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
            //raceService.saveRaceEntry(new RaceEntry(currentParticipant, race));
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

    @FXML
    protected void onParticipantSelected() {
        //currentParticipant = participantBox.getValue();
        loadRaces();
    }

    public void init(IContestServices server, Stage currentStage) {
        initialise(server, currentStage);
        setParticipants();
        racesView.getSelectionModel().setSelectionMode(SelectionMode.MULTIPLE);
        loadRaces();
    }

    public void init(IContestServices server, Stage currentStage, Participant currentParticipant) {
        currentStage.setTitle("MXGP - Register to Races");
        initialise(server, currentStage);
        setNewlyCreatedParticipant(currentParticipant);
        racesView.getSelectionModel().setSelectionMode(SelectionMode.MULTIPLE);
        loadRaces();
    }

    private void initialise(IContestServices server, Stage currentStage) {
        this.server = server;
        this.currentStage = currentStage;
    }

    private void setNewlyCreatedParticipant(Participant participant) {
        //currentParticipant = participant;
        participantBox.getItems().clear();
        //participantBox.getItems().add(currentParticipant);
        participantBox.getSelectionModel().clearAndSelect(0);
    }

    private void setParticipants() {
        participantBox.getItems().clear();
        //Collection<Participant> participants = participantService.findAll();
        //participantBox.getItems().addAll(participants);
        participantBox.getSelectionModel().clearAndSelect(0);
        //currentParticipant = participantBox.getValue();
    }

    private void loadRaces() {
        racesView.getItems().clear();
//        Collection<Race> races = raceService
//                .getRacesWhereNotRegisteredAndEngineCapacity(
//                        currentParticipant.getID(), currentParticipant.getEngineCapacity());
//        racesView.getItems().addAll(races);
//        if (races.size() > 0) {
//            racesFoundLabel.setText(races.size() + " races found, "
//                    + currentParticipant.getEngineCapacity() + "cc class");
//        } else {
//            racesFoundLabel.setText("No races found for " + currentParticipant.getEngineCapacity() + "cc class");
//        }
    }
}
