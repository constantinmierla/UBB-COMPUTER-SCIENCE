package org.example.socialnetworkfx.socialnetworkfx.controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import org.example.socialnetworkfx.socialnetworkfx.domain.validation.ValidationException;
import org.example.socialnetworkfx.socialnetworkfx.service.UserService;

public class RegisterView {
    @FXML
    public Label errorMessage;
    @FXML
    public TextField firstnameText;
    @FXML
    public TextField lastnameText;
    @FXML
    public Button registerButton;
    @FXML
    public PasswordField passwordText;
    @FXML
    public TextField emailText;
    private UserService service;
    private Stage stage;

    public void setService(UserService service, Stage stage) {
        this.service = service;
        this.stage = stage;
    }

    public void handleRegisterButton(ActionEvent actionEvent) {
        String firstname = firstnameText.getText();
        String lastname = lastnameText.getText();
        String password = passwordText.getText();
        String email = emailText.getText();
        try {
            this.service.save(firstname, lastname, email, password);
            firstnameText.clear();
            lastnameText.clear();
            passwordText.clear();
            emailText.clear();
            stage.close();
        } catch (ValidationException e) {
            errorMessage.setText(e.getMessage());
        }
    }
}
