package com.ubb.controller;

import com.ubb.model.User;
import com.ubb.repository.IUserRepository;
import com.ubb.repository.UserDBRepository;
import com.ubb.service.IUserService;
import com.ubb.service.UserService;
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
import java.util.Optional;
import java.util.Properties;

public class MainController extends AnchorPane {
    private IUserService userService;
    private Properties properties;
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
        Optional<User> user = userService.getLogin(username, password);
        if (user.isEmpty()) {
            System.out.println("User credentials invalid!");
            usernameField.clear();
            passwordField.clear();
        } else {
            try {
                FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/views/home.fxml"));
                Scene scene = new Scene(fxmlLoader.load());
                HomeController controller = fxmlLoader.getController();
                controller.init(properties, user.get(), currentStage);
                currentStage.setTitle("MXGP Admin Panel - Home");
                currentStage.setScene(scene);
                currentStage.getIcons().add(new Image(String.valueOf(getClass().getResource("/img/icon.png"))));
                currentStage.show();
            } catch (IOException ioException) {
                System.out.println(ioException.getMessage());
            }
        }
    }

    public void init(Properties properties, Stage currentStage) {
        IUserRepository userRepository = new UserDBRepository(properties);
        userService = new UserService(userRepository);
        this.properties = properties;
        this.currentStage = currentStage;
    }
}
