package org.example.socialnetworkfx.socialnetworkfx;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import org.example.socialnetworkfx.socialnetworkfx.controller.LoginView;
import org.example.socialnetworkfx.socialnetworkfx.domain.User;
import org.example.socialnetworkfx.socialnetworkfx.domain.validation.FriendshipValidation;
import org.example.socialnetworkfx.socialnetworkfx.domain.validation.RequestValidation;
import org.example.socialnetworkfx.socialnetworkfx.domain.validation.UserValidation;
import org.example.socialnetworkfx.socialnetworkfx.repository.FriendshipDbRepository;
import org.example.socialnetworkfx.socialnetworkfx.repository.FriendshipRequestDbRepository;
import org.example.socialnetworkfx.socialnetworkfx.repository.NewRepository;
import org.example.socialnetworkfx.socialnetworkfx.repository.UserDbRepository;
import org.example.socialnetworkfx.socialnetworkfx.service.FriendshipRequestService;
import org.example.socialnetworkfx.socialnetworkfx.service.FriendshipService;
import org.example.socialnetworkfx.socialnetworkfx.service.UserService;
import javafx.scene.image.Image;
import java.awt.*;
import java.io.IOException;
import java.sql.SQLException;
import java.util.Objects;

public class HelloApplication extends Application {
    UserDbRepository userRepository;
    FriendshipDbRepository friendshipRepository;
    UserService userService;
    FriendshipService friendshipService;
    FriendshipRequestDbRepository friendshipRequestDbRepository;
    FriendshipRequestService friendshipRequestService;

    @Override
    public void start(Stage primaryStage) throws IOException, SQLException {
        String username = "postgres";
        String password = "costi";
        String url = "jdbc:postgresql://localhost:5432/postgres";
        userRepository = new UserDbRepository(url,username,password, new UserValidation());
        friendshipRepository = new FriendshipDbRepository(url,username, password, new FriendshipValidation());
        userService = new UserService(userRepository);
        friendshipService=new FriendshipService(friendshipRepository,userRepository);
        friendshipRequestDbRepository=new FriendshipRequestDbRepository(url,username,password,new RequestValidation());
        friendshipRequestService=new FriendshipRequestService(friendshipRequestDbRepository);

        initView(primaryStage);
        primaryStage.setWidth(600);
        primaryStage.show();
    }

    private void initView(Stage primaryStage) throws IOException {

        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("login-view.fxml"));

        AnchorPane userLayout = fxmlLoader.load();
        primaryStage.setScene(new Scene(userLayout));
        primaryStage.setTitle("Mico app");
        LoginView loginController = fxmlLoader.getController();
        loginController.setService(userService,friendshipService,friendshipRequestService);

    }

    public static void main(String[] args) {
        launch();
    }
}