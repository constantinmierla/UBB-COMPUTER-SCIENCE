package org.example.socialnetworkfx.socialnetworkfx.controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import org.example.socialnetworkfx.socialnetworkfx.HelloApplication;
import org.example.socialnetworkfx.socialnetworkfx.domain.Friendship;
import org.example.socialnetworkfx.socialnetworkfx.domain.User;
import org.example.socialnetworkfx.socialnetworkfx.service.FriendshipRequestService;
import org.example.socialnetworkfx.socialnetworkfx.service.FriendshipService;
import org.example.socialnetworkfx.socialnetworkfx.service.UserService;

import java.io.IOException;
import java.util.Optional;

import static javafx.application.Application.launch;

public class LoginView {
    @FXML
    public TextField emailText;
    @FXML
    public Button loginButton;
    @FXML
    public Button registerButton;
    @FXML
    public PasswordField passwordText;
    @FXML
    public Label errorMessage;
    @FXML
    public ImageView yahooLogo;
    private UserService userService;
    private FriendshipService friendshipService;
    private FriendshipRequestService requestService;

    public void handleRegisterButton(ActionEvent actionEvent) throws IOException {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("../register-view.fxml"));

        AnchorPane root = (AnchorPane) loader.load();
        Scene scene = new Scene(root);
        Stage stage = new Stage();
        stage.setScene(scene);
        stage.setTitle("Yahoo Messenger");
        //yahooLogo.setImage(Image.fromPlatformImage("../images/yahoo.png"));

        RegisterView registerView = loader.getController();
        registerView.setService(userService, stage);
        stage.show();


    }

    public void setService(UserService userService,FriendshipService friendshipService,FriendshipRequestService requestService) {
        this.userService = userService;
        this.friendshipService = friendshipService;
        this.requestService = requestService;
    }

    public void handleLoginButton(ActionEvent actionEvent) throws IOException {
        String email = emailText.getText();
        String password = passwordText.getText();
        User loggedIn = userService.findByEmail(email, password);
        if (loggedIn != null) {

            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("../main-menu-view.fxml"));
            AnchorPane root = (AnchorPane) loader.load();
            Scene scene = new Scene(root);
            Stage stage = new Stage();
            stage.setScene(scene);
            stage.setTitle("Yahoo Messenger");
            MainMenuView mainMenuView = loader.getController();
            mainMenuView.setService(loggedIn.getID(),userService,friendshipService,requestService,stage);
            errorMessage.setVisible(false);
            stage.show();

        }
        else{
            emailText.clear();
            passwordText.clear();
            errorMessage.setText("Invalid email or password");
            errorMessage.setVisible(true);
        }
    }
}
