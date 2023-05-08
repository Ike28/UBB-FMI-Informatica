package com.ubb.controller;

import com.ubb.IContestServices;
import com.ubb.IMainObserver;
import com.ubb.exceptions.ContestDataException;
import com.ubb.model.Participant;
import com.ubb.model.Team;
import com.ubb.model.User;
import com.ubb.dto.RaceDTO;
import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.image.Image;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.Collection;
import java.util.List;

public class HomeController extends AnchorPane implements IMainObserver {
    private IContestServices server;
    private Stage currentStage;
    private User currentUser;

    @FXML
    private Label usernameLabel;

    @FXML
    private TableView<RaceDTO> raceTable;
    @FXML
    private TableColumn<RaceDTO, String> raceName;
    @FXML
    private TableColumn<RaceDTO, Integer> raceEngine;
    @FXML
    private TableColumn<RaceDTO, Integer> raceParticipantCount;

    @FXML
    private TableView<Participant> participantsTable;
    @FXML
    private TableColumn<Participant, String> participantName;
    @FXML
    private TableColumn<Participant, Integer> participantEngine;

    @FXML
    private ComboBox<Team> teamBox;

    @FXML
    private Button newParticipantButton;

    @FXML
    private Button newRaceButton;

    @FXML
    private Button newEntryButton;

    @FXML
    protected void onRaceClicked() {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/views/new_race.fxml"));
            Scene scene = new Scene(fxmlLoader.load());
            NewRaceController controller = fxmlLoader.getController();
            controller.init(server, currentStage, currentUser);
            currentStage.setScene(scene);
            currentStage.getIcons().add(new Image(String.valueOf(getClass().getResource("/img/icon.png"))));
            currentStage.show();
        } catch (IOException ioException) {
            System.out.println(ioException.getMessage());
        }
    }

    @FXML
    protected void onLogoutClicked() {
        try {
            server.logout(currentUser, this);
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/views/main-view.fxml"));
            Scene scene = new Scene(fxmlLoader.load());
            MainController controller = fxmlLoader.getController();
            controller.init(server, currentStage);
            currentStage.setScene(scene);
            currentStage.getIcons().add(new Image(String.valueOf(getClass().getResource("/img/icon.png"))));
            currentStage.show();
        } catch (IOException | ContestDataException exception) {
            AlertController.showError(currentStage, exception.getMessage());
        }
    }

    @FXML
    protected void onParticipantButtonClicked() {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/views/new_participant.fxml"));
            Scene scene = new Scene(fxmlLoader.load());
            NewParticipantController controller = fxmlLoader.getController();
            controller.init(server, currentStage, currentUser);
            currentStage.setScene(scene);
            currentStage.getIcons().add(new Image(String.valueOf(getClass().getResource("/img/icon.png"))));
            currentStage.show();
        } catch (IOException ioException) {
            System.out.println(ioException.getMessage());
        }
    }

    @FXML
    protected void onNewEntryClicked() {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/views/add_entries.fxml"));
            Scene scene = new Scene(fxmlLoader.load());
            RaceEntriesController controller = fxmlLoader.getController();
            controller.init(server, currentStage, currentUser);
            currentStage.setScene(scene);
            currentStage.getIcons().add(new Image(String.valueOf(getClass().getResource("/img/icon.png"))));
            currentStage.show();
        } catch (IOException ioException) {
            System.out.println(ioException.getMessage());
        }
    }

    @FXML
    protected void onTeamBoxChanged() {
        try {
            participantsTable.getItems().clear();
            Team currentTeam = teamBox.getValue();
            Collection<Participant> participants = server.getParticipantsByTeam(currentTeam.getID());
            participantsTable.getItems().addAll(participants);
        } catch (ContestDataException contestDataException) {
            AlertController.showError(currentStage, contestDataException.getMessage());
        }
    }

    public void init(IContestServices server, Stage currentStage, User currentUser) {
        try {
            currentStage.setTitle("MXGP Admin Panel - Home");
            this.server = server;
            this.currentStage = currentStage;
            this.currentUser = currentUser;

            usernameLabel.setText(currentUser.getUsername());
            fillTeamBox();
            initialiseParticipantsTable();
            initialiseRaceTable();
        } catch (ContestDataException contestDataException) {
            AlertController.showError(currentStage, contestDataException.getMessage());
        }
    }

    private void fillTeamBox() throws ContestDataException {
        teamBox.getItems().clear();
        Collection<Team> teams = server.findAllTeams();
        teamBox.getItems().addAll(teams);
    }

    private void initialiseParticipantsTable() throws ContestDataException {
        participantsTable.getItems().clear();
        participantsTable.setPlaceholder(new Label("No participants found"));
        participantName.setCellValueFactory(new PropertyValueFactory<>("fullName"));
        participantEngine.setCellValueFactory(new PropertyValueFactory<>("engineCapacity"));
        Collection<Participant> participants = server.findAllParticipants();
        participantsTable.getItems().addAll(participants);
    }

    private void initialiseRaceTable() throws ContestDataException {
        raceTable.getItems().clear();
        raceTable.setPlaceholder(new Label("No races found"));
        raceName.setCellValueFactory(new PropertyValueFactory<>("name"));
        raceEngine.setCellValueFactory(new PropertyValueFactory<>("engineCapacity"));
        raceParticipantCount.setCellValueFactory(new PropertyValueFactory<>("participants"));
        Collection<RaceDTO> races = server.getRacesWithParticipantCount();
        raceTable.getItems().addAll(races);
    }

    @Override
    public void raceAdded(RaceDTO race) throws ContestDataException {
        Platform.runLater(() -> {
            raceTable.getItems().add(race);
        });
    }

    @Override
    public void participantAdded(Participant participant) throws ContestDataException {
        Platform.runLater(this::onTeamBoxChanged);
    }

    @Override
    public void raceEntriesAdded(List<RaceDTO> races) throws ContestDataException {
        Platform.runLater(() -> {
            raceTable.getItems().clear();
            raceTable.getItems().addAll(races);
        });
    }
}
