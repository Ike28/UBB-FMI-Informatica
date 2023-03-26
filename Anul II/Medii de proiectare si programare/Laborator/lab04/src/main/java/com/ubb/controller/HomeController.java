package com.ubb.controller;

import com.ubb.model.Participant;
import com.ubb.model.Team;
import com.ubb.model.User;
import com.ubb.model.data.RaceDTO;
import com.ubb.repository.*;
import com.ubb.service.*;
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
import java.util.Properties;

public class HomeController extends AnchorPane {
    private User currentUser;
    private IRaceService raceService;
    private ITeamService teamService;
    private IParticipantService participantService;
    private Stage currentStage;
    private Properties properties;

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
    protected void onParticipantButtonClicked() {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/views/new_participant.fxml"));
            Scene scene = new Scene(fxmlLoader.load());
            NewParticipantController controller = fxmlLoader.getController();
            controller.init(properties, currentUser, currentStage);
            currentStage.setTitle("MXGP - New Participant");
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
            controller.init(properties, currentStage, currentUser);
            currentStage.setTitle("MXGP - Register to Races");
            currentStage.setScene(scene);
            currentStage.getIcons().add(new Image(String.valueOf(getClass().getResource("/img/icon.png"))));
            currentStage.show();
        } catch (IOException ioException) {
            System.out.println(ioException.getMessage());
        }
    }

    @FXML
    protected void onTeamBoxChanged() {
        participantsTable.getItems().clear();
        Team currentTeam = teamBox.getValue();
        Collection<Participant> participants = participantService.getParticipantsByTeam(currentTeam.getID());
        participantsTable.getItems().addAll(participants);
    }

    public void init(Properties properties, User currentUser, Stage currentStage) {
        this.currentUser = currentUser;
        IParticipantRepository participantRepository = new ParticipantDBRepository(properties);
        participantService = new ParticipantService(participantRepository);
        IRaceRepository raceRepository = new RaceDBRepository(properties);
        raceService = new RaceService(raceRepository,
                new RaceEntryDBRepository(properties, raceRepository, participantRepository));
        teamService = new TeamService(new TeamDBRepository(properties));
        this.currentStage = currentStage;
        this.properties = properties;

        usernameLabel.setText(currentUser.getFullName() + " (" + currentUser.getUsername() + ")");
        fillTeamBox();
        initialiseParticipantsTable();
        initialiseRaceTable();
    }

    private void fillTeamBox() {
        teamBox.getItems().clear();
        Collection<Team> teams = teamService.findAll();
        teamBox.getItems().addAll(teams);
    }

    private void initialiseParticipantsTable() {
        participantsTable.getItems().clear();
        participantsTable.setPlaceholder(new Label("No participants found"));
        participantName.setCellValueFactory(new PropertyValueFactory<>("fullName"));
        participantEngine.setCellValueFactory(new PropertyValueFactory<>("engineCapacity"));
        Collection<Participant> participants = participantService.findAll();
        participantsTable.getItems().addAll(participants);
    }

    private void initialiseRaceTable() {
        raceTable.getItems().clear();
        raceTable.setPlaceholder(new Label("No races found"));
        raceName.setCellValueFactory(new PropertyValueFactory<>("name"));
        raceEngine.setCellValueFactory(new PropertyValueFactory<>("engineCapacity"));
        raceParticipantCount.setCellValueFactory(new PropertyValueFactory<>("participants"));
        Collection<RaceDTO> races = raceService.getRacesWithParticipantCount();
        raceTable.getItems().addAll(races);
    }
}
