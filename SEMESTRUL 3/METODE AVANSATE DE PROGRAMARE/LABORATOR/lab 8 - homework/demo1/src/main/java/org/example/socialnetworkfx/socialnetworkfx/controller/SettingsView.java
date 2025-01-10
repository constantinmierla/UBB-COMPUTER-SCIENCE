package org.example.socialnetworkfx.socialnetworkfx.controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import org.example.socialnetworkfx.socialnetworkfx.service.UserService;

public class SettingsView {
    @FXML
    public TextField emailText;
    @FXML
    public PasswordField passwordText;
    @FXML
    public TextField firstnameText;
    @FXML
    public TextField lastnameText;
    @FXML
    public Button changeButton;

    private UserService userService;
    private Long ID;

    public void setService(UserService userService, Long ID) {
        this.userService = userService;
        this.ID = ID;
    }

    public void handleChange(ActionEvent actionEvent) {
        String email = emailText.getText();
        String password = passwordText.getText();
        String firstname = firstnameText.getText();
        String lastname = lastnameText.getText();
        try {
            userService.update(ID, firstname, lastname, email, password);
            emailText.clear();
            passwordText.clear();
            firstnameText.clear();
            lastnameText.clear();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
