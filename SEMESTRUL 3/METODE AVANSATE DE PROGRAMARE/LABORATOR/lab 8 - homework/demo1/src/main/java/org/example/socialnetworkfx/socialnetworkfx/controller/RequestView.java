package org.example.socialnetworkfx.socialnetworkfx.controller;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;
import org.example.socialnetworkfx.socialnetworkfx.domain.User;
import org.example.socialnetworkfx.socialnetworkfx.service.FriendshipRequestService;
import org.example.socialnetworkfx.socialnetworkfx.service.FriendshipService;

import java.util.List;
import java.util.function.Predicate;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class RequestView {

    @FXML
    public TableColumn<User,String> firstnameColumn;
    @FXML
    public TableColumn<User,String> lastnameColumn;
    @FXML
    public Button sendButton;
    @FXML
    public TableView<User> tableView;
    @FXML
    public TextField searchText;

    private FriendshipRequestService friendshipRequestService;
    private FriendshipService friendshipService;
    private Stage stage;
    private Long ID;
    ObservableList<User> allUsers= FXCollections.observableArrayList();

    public void setService(FriendshipRequestService friendshipRequestService, FriendshipService friendshipService, Long ID,Stage stage) {
        this.friendshipRequestService = friendshipRequestService;
        this.friendshipService= friendshipService;
        this.ID = ID;
        this.stage=stage;
        initModel();
    }

    public void initialize() {
        firstnameColumn.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        lastnameColumn.setCellValueFactory(new PropertyValueFactory<>("lastName"));
        searchText.textProperty().addListener(o->handleFilter());
        tableView.setItems(allUsers);

    }

    private void handleFilter() {
        String text=searchText.getText();
        Predicate<User> p1=user -> {
            return user.getFirstName().startsWith(text);
        };
        if(text.isEmpty()){
            initModel();
            return;
        }
        List<User> filtered=allUsers.stream().filter(p1).collect(Collectors.toList());
        allUsers.setAll(filtered);
    }

    public void initModel(){
        Iterable<User> messages = friendshipService.showNonFriends(ID);
        List<User> users = StreamSupport.stream(messages.spliterator(), false)
                .collect(Collectors.toList());
        allUsers.setAll(users);

    }
    public void handleSendRequest(ActionEvent actionEvent) {
        User selectedUser=(User) tableView.getSelectionModel().getSelectedItem();
        friendshipRequestService.sendRequest(ID,selectedUser.getID());

        stage.close();


    }



}
