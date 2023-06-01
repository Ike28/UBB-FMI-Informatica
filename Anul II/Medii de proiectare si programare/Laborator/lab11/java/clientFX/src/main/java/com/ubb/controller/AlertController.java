package com.ubb.controller;

import javafx.scene.control.Alert;
import javafx.stage.Stage;

public class AlertController {
    public static void showAlert(Stage owner, Alert.AlertType type, String header, String details) {
        Alert alert = new Alert(type);
        alert.setHeaderText(header);
        alert.setContentText(details);
        alert.initOwner(owner);
        Stage stage = (Stage) alert.getDialogPane().getScene().getWindow();
        stage.showAndWait();
    }

    public static void showError(Stage owner, String details) {
        Alert error = new Alert(Alert.AlertType.ERROR);
        error.initOwner(owner);
        error.setTitle("Eroare!");
        error.setContentText(details);
        Stage stage = (Stage) error.getDialogPane().getScene().getWindow();
        stage.showAndWait();
    }
}
