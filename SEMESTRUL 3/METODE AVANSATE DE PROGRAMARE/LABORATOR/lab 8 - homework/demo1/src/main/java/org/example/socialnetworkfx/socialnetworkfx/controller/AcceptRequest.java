package org.example.socialnetworkfx.socialnetworkfx.controller;

import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import org.example.socialnetworkfx.socialnetworkfx.domain.FriendshipRequest;
import org.example.socialnetworkfx.socialnetworkfx.domain.RequestStatus;
import org.example.socialnetworkfx.socialnetworkfx.domain.User;
import org.example.socialnetworkfx.socialnetworkfx.service.FriendshipRequestService;
import org.example.socialnetworkfx.socialnetworkfx.service.FriendshipService;
import org.example.socialnetworkfx.socialnetworkfx.service.UserService;

import java.sql.Timestamp;
import java.time.LocalDateTime;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class AcceptRequest {
    @FXML
    public TableColumn<FriendshipRequest, String> statusColumn;
    @FXML
    public Label showMessage;
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
    public TableView tableView;

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
    }

    public void handleAccept(ActionEvent actionEvent) {
        FriendshipRequest request = (FriendshipRequest) tableView.getSelectionModel().getSelectedItem();
        System.out.println(request.getSender() + " " + request.getReceiver());
        if (request != null) {
            if (request.getStatus().equals("PENDING")) {
                friendshipRequestService.acceptRequest(request.getSender(), request.getReceiver());
                System.out.println("Inainte de add"+request.getSender() + " " + request.getReceiver());
                friendshipService.save(request.getSender(), request.getReceiver());
                showMessage.setText("You added a new friend!");
                showMessage.setVisible(true);
            }
            initModel();
        }
    }

    public void handleDecline(ActionEvent actionEvent) {
        FriendshipRequest request = (FriendshipRequest) tableView.getSelectionModel().getSelectedItem();
        System.out.println(request.getSender() + " " + request.getReceiver());
        if (request != null) {
            if (request.getStatus().equals("PENDING")) {
                friendshipRequestService.declineRequest(request.getSender(), request.getReceiver());
                showMessage.setText("You declined the friendship!");
                showMessage.setVisible(true);
            }
            initModel();
        }
    }
    }


