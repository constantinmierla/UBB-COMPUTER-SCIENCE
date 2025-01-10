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
import org.example.socialnetworkfx.socialnetworkfx.domain.FriendshipRequest;
import org.example.socialnetworkfx.socialnetworkfx.domain.User;
import org.example.socialnetworkfx.socialnetworkfx.service.FriendshipRequestService;
import org.example.socialnetworkfx.socialnetworkfx.service.FriendshipService;
import org.example.socialnetworkfx.socialnetworkfx.service.UserService;

import java.io.IOException;
import java.sql.Timestamp;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class AcceptRequest {
    @FXML
    public TableColumn<FriendshipRequest, String> statusColumn;
    @FXML
    public Label showMessage;
    @FXML
    public Button sendRequestButton;
    @FXML
    private TableColumn<FriendshipRequest, String> firstnameColumn;
    @FXML
    private TableColumn<FriendshipRequest, String> lastnameColumn;
    @FXML
    private TableColumn<FriendshipRequest, Timestamp> dateColumn;
    @FXML
    public Button acceptButton;
    @FXML
    public Button rejectButton;
    @FXML
    public TableView<FriendshipRequest> tableView;

    private Long ID;
    private FriendshipRequestService friendshipRequestService;
    private FriendshipService friendshipService;
    private UserService userService;
    ObservableList<FriendshipRequest> model = FXCollections.observableArrayList();

    void setService(FriendshipRequestService friendshipRequestService, UserService userService, FriendshipService friendshipService, Long ID) {
        this.friendshipRequestService = friendshipRequestService;
        this.userService = userService;
        this.friendshipService = friendshipService;
        this.ID = ID;
        initModel();
    }

    public void initialize() {
        firstnameColumn.setCellValueFactory(cellData -> {
            Long senderId = cellData.getValue().getId_user1();
            User sender = userService.findOne(senderId);
            return new SimpleStringProperty(sender != null ? sender.getFirstName() : "Unknown");
        });

        lastnameColumn.setCellValueFactory(cellData -> {
            Long senderId = cellData.getValue().getId_user1();
            User sender = userService.findOne(senderId);
            return new SimpleStringProperty(sender != null ? sender.getLastName() : "Unknown");
        });

        dateColumn.setCellValueFactory(new PropertyValueFactory<>("datefrom"));
        statusColumn.setCellValueFactory(new PropertyValueFactory<>("status"));
        tableView.setItems(model);
    }

    private void initModel() {
        Iterable<FriendshipRequest> messages = friendshipRequestService.findByReceiver(ID);
        List<FriendshipRequest> users = StreamSupport.stream(messages.spliterator(), false)
                .collect(Collectors.toList());
        model.setAll(users);
        setSeen();
    }

    public void handleAccept(ActionEvent actionEvent) {
        FriendshipRequest request = (FriendshipRequest) tableView.getSelectionModel().getSelectedItem();
        if (request != null) {
            if (request.getStatus().equals("PENDING")) {
                friendshipRequestService.acceptRequest(request.getSender(), request.getReceiver());
                friendshipService.save(request.getSender(), request.getReceiver());
                showMessage.setText("You added a new friend!");
                showMessage.setVisible(true);
            }
            initModel();
        }
    }

    public void handleDecline(ActionEvent actionEvent) {
        FriendshipRequest request = (FriendshipRequest) tableView.getSelectionModel().getSelectedItem();
        if (request != null) {
            if (request.getStatus().equals("PENDING")) {
                friendshipRequestService.declineRequest(request.getSender(), request.getReceiver());
                showMessage.setText("You declined the friendship!");
                showMessage.setVisible(true);
            }
            initModel();
        }
    }

    public void handleSend(ActionEvent actionEvent) throws IOException {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("/org/example/socialnetworkfx/socialnetworkfx/request-view.fxml"));

        AnchorPane root = (AnchorPane) loader.load();
        Scene scene = new Scene(root);
        Stage stage2 = new Stage();
        stage2.setScene(scene);
        stage2.setTitle("Mico App");

        RequestView requestView = loader.getController();
        requestView.setService(friendshipRequestService,friendshipService,ID,stage2);
        stage2.show();
    }
    public void setSeen(){
        Iterable<FriendshipRequest> messages = friendshipRequestService.findByReceiver(ID);
        for (FriendshipRequest request : messages) {
            if(!request.isSeen()){
                request.setSeen(true);
                friendshipRequestService.update(request.getID(), true);
            }
        }
    }
}


