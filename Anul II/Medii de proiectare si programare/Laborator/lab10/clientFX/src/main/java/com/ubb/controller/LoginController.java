package com.ubb.controller;

import com.ubb.IContestServices;
import com.ubb.exceptions.ContestDataException;
import com.ubb.model.User;
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

public class LoginController extends AnchorPane {
    private IContestServices server;
    private Stage currentStage;

    @FXML
    private TextField usernameField;

    @FXML
    private PasswordField passwordField;

    @FXML
    private Button loginButton;

    @FXML
    protected void onLoginButtonClicked() {
        String username = usernameField.getText();
        String password = Hasher.hash(passwordField.getText());
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/views/home.fxml"));
            Scene scene = new Scene(fxmlLoader.load());
            MainController controller = fxmlLoader.getController();
            User user = server.login(username, password, controller);
            controller.init(server, currentStage, user);
            currentStage.setScene(scene);
            currentStage.getIcons().add(new Image(String.valueOf(getClass().getResource("/img/icon.png"))));
            currentStage.show();
        } catch (IOException | ContestDataException exception) {
            AlertController.showError(currentStage, exception.getMessage());
        }
    }

    public void init(IContestServices server, Stage currentStage) {
        currentStage.setTitle("MXGP Admin Panel - Login");
        this.server = server;
        this.currentStage = currentStage;
    }
}
