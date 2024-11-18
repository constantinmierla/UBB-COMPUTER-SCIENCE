package org.example.socialnetworkfx.socialnetworkfx.controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import org.example.socialnetworkfx.socialnetworkfx.domain.User;
import org.example.socialnetworkfx.socialnetworkfx.domain.validation.ValidationException;
import org.example.socialnetworkfx.socialnetworkfx.repository.UserDbRepository;
import org.example.socialnetworkfx.socialnetworkfx.service.UserService;

import java.io.IOException;

public class RegisterView {

    private UserService service;
    private Stage stage;
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

    public void setService(UserService service, Stage stage) {
        this.service = service;
        this.stage = stage;
    }

    public void handleRegisterButton(ActionEvent actionEvent) {
        String firstname = firstnameText.getText();
        String lastname = lastnameText.getText();
        String password = passwordText.getText();
        String email = emailText.getText();
        System.out.println(firstname + " " + lastname + " " + password+ " " + email);
        try{
            this.service.save(firstname, lastname, email,password);
            firstnameText.clear();
            lastnameText.clear();
            passwordText.clear();
            emailText.clear();
        }catch (Exception e){
            e.printStackTrace();
        }
        stage.close();
    }
}
