package com.ubb.controller;

import com.ubb.IContestServices;
import com.ubb.IMainObserver;
import com.ubb.exceptions.ContestDataException;
import com.ubb.model.Participant;
import com.ubb.model.data.RaceDTO;
import com.ubb.utils.Hasher;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.List;

public class MainController extends AnchorPane implements IMainObserver {
    private IContestServices server;
    private Stage currentStage;

    @FXML
    private TextField usernameField;

    @FXML
    private PasswordField passwordField;

    @FXML
    private Button loginButton;

    @FXML
    protected void onLoginButtonClicked() throws ContestDataException {
        String username = usernameField.getText();
        String password = Hasher.hash(passwordField.getText());
        server.login(username, password, this);
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
        currentStage.setTitle("MXGP Admin Panel - Login");
        this.server = server;
        this.currentStage = currentStage;
    }

    @Override
    public void raceAdded(RaceDTO race) throws ContestDataException {

    }

    @Override
    public void participantAdded(Participant participant) throws ContestDataException {

    }

    @Override
    public void raceEntriesAdded(List<RaceDTO> races) throws ContestDataException {

    }
}
