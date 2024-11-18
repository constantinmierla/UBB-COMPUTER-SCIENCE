package org.example.socialnetworkfx.socialnetworkfx.controller;

import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import org.example.socialnetworkfx.socialnetworkfx.domain.Friendship;
import org.example.socialnetworkfx.socialnetworkfx.domain.FriendshipRequest;
import org.example.socialnetworkfx.socialnetworkfx.domain.User;
import org.example.socialnetworkfx.socialnetworkfx.domain.event.FriendshipEntityChange;
import org.example.socialnetworkfx.socialnetworkfx.service.FriendshipRequestService;
import org.example.socialnetworkfx.socialnetworkfx.service.FriendshipService;
import org.example.socialnetworkfx.socialnetworkfx.service.UserService;
import org.example.socialnetworkfx.socialnetworkfx.utils.Observer;

import java.io.IOException;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class MainMenuView implements Observer<FriendshipEntityChange> {
    @FXML
    public TableColumn firstnameColumn;
    @FXML
    public TableView tableView;
    @FXML
    public TableColumn lastnameColumn;
    @FXML
    public Button sendRequestButton;
    @FXML
    public Button acceptRequestButton;
    @FXML
    public TableColumn<User, String> sinceColumn;
    @FXML
    public Button removeFriendButton;
    @FXML
    public Button removeUser;
    @FXML
    public Button accountSettingsButton;
    @FXML
    public Label userNameField;

    private Long IDUser;
    private UserService userService;
    private FriendshipService friendshipService;
    private FriendshipRequestService requestService;
    private Stage stage;
    ObservableList<User> model = FXCollections.observableArrayList();

    public void setService(Long IDUser, UserService userService, FriendshipService friendshipService,FriendshipRequestService requestService,Stage stage) {
        this.IDUser = IDUser;
        this.userService = userService;
        this.friendshipService = friendshipService;
        this.requestService =requestService;
        this.stage = stage;
        friendshipService.addObserver(this);
        initModel();
    }
    public void initialize() {
        // Set first and last name columns
        firstnameColumn.setCellValueFactory(new PropertyValueFactory<User, String>("firstName"));
        lastnameColumn.setCellValueFactory(new PropertyValueFactory<User, String>("lastName"));

        sinceColumn.setCellValueFactory(cellData -> {
            Long senderId = cellData.getValue().getID(); // Get the ID of the user
            Friendship sender = friendshipService.findOne(senderId, IDUser); // Fetch the Friendship
            return new SimpleStringProperty(sender != null ? sender.getDatesince().toString() : "Unknown");
        });

        // Set the table items (the list of friendship requests or users)
        tableView.setItems(model);
    }

    private void initModel() {
        Iterable<User> messages = friendshipService.getFriends(IDUser);
        List<User> users = StreamSupport.stream(messages.spliterator(), false)
                .collect(Collectors.toList());
        model.setAll(users);
        setUser(IDUser);
    }

    public void setUser(Long IDUser) {
        User user = userService.findOne(IDUser);
        String fullName=user.getFirstName()+" "+user.getLastName();
        userNameField.setText(fullName);
    }

    public void handleSendRequest(ActionEvent actionEvent) throws IOException {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("../request-view.fxml"));

        AnchorPane root = (AnchorPane) loader.load();
        Scene scene = new Scene(root);
        Stage stage2 = new Stage();
        stage2.setScene(scene);
        stage2.setTitle("Yahoo Messenger");

        RequestView requestView = loader.getController();
        requestView.setService(requestService,userService,IDUser);
        stage2.show();
    }

    public void handleAcceptRequest(ActionEvent actionEvent) throws IOException {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("../accept-request.fxml"));

        AnchorPane root = (AnchorPane) loader.load();
        Scene scene = new Scene(root);
        Stage stage2 = new Stage();
        stage2.setScene(scene);
        stage2.setTitle("Yahoo Messenger");

        AcceptRequest requestView = loader.getController();
        requestView.setService(requestService,userService,friendshipService,IDUser);
        stage2.show();

    }

    @Override
    public void update(FriendshipEntityChange friendshipEntityChange) {initModel();
    }

    public void handleRemoveFriend(ActionEvent actionEvent) {
        User request = (User) tableView.getSelectionModel().getSelectedItem();
        System.out.println(request.getID());
        Friendship friendship = friendshipService.findOne(request.getID(), IDUser);
        System.out.println(friendship.getID());
        FriendshipRequest friendshipRequest=requestService.findByIDs(IDUser,request.getID());
        System.out.println(friendshipRequest.getID());
        requestService.delete(friendshipRequest.getID());
        friendshipService.delete(friendship.getID());

    }

    public void handleRemoveUser(ActionEvent actionEvent) {
        User user=userService.findOne(IDUser);

    }

    public void handleAccountSetting(ActionEvent actionEvent) {
    }
}
