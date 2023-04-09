package com.ubb.controller;

import com.ubb.IContestServices;
import com.ubb.model.Participant;
import com.ubb.model.Team;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;

public class NewParticipantController extends AnchorPane {
    private IContestServices server;
    private Stage currentStage;

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
//        if (!Objects.equals(selected.getName(), "None")) {
//            newParticipant.setTeamID(selected.getID());
//        }
        //participantService.save(newParticipant);

        try {
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/views/add_entries.fxml"));
            Scene scene = new Scene(fxmlLoader.load());
            RaceEntriesController controller = fxmlLoader.getController();
//            Optional<Participant> currentParticipant = participantService.getParticipantByData(newParticipant);
//            if (currentParticipant.isPresent()) {
//                controller.init(server, currentStage);
//                currentStage.setScene(scene);
//                currentStage.getIcons().add(new Image(String.valueOf(getClass().getResource("/img/icon.png"))));
//                currentStage.show();
//            } else {
//                System.out.println("Error : could not retrieve created entity");
//            }
        } catch (IOException ioException) {
            System.out.println(ioException.getMessage());
        }
    }

    public void init(IContestServices server, Stage currentStage) {
        currentStage.setTitle("MXGP - New Participant");
        this.server = server;
        this.currentStage = currentStage;

        ControllerUtils.addInputNumberFormatter(engineCapacityField);
        clearFields();
        fillTeamBox();
    }

    private void clearFields() {
        firstnameField.clear();
        lastnameField.clear();
        engineCapacityField.clear();
        teamBox.getSelectionModel().clearSelection();
    }

    private void fillTeamBox() {
        teamBox.getItems().clear();
        teamBox.getItems().add(new Team("None"));
        //Collection<Team> teams = teamService.findAll();
        //teamBox.getItems().addAll(teams);
    }
}
