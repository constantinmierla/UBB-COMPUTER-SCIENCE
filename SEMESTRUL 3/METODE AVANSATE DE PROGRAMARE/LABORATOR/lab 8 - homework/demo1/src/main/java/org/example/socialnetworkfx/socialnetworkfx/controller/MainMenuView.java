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
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import org.example.socialnetworkfx.socialnetworkfx.domain.Friendship;
import org.example.socialnetworkfx.socialnetworkfx.domain.FriendshipRequest;
import org.example.socialnetworkfx.socialnetworkfx.domain.User;
import org.example.socialnetworkfx.socialnetworkfx.domain.event.FriendshipEntityChange;
import org.example.socialnetworkfx.socialnetworkfx.service.FriendshipRequestService;
import org.example.socialnetworkfx.socialnetworkfx.service.FriendshipService;
import org.example.socialnetworkfx.socialnetworkfx.service.MessageService;
import org.example.socialnetworkfx.socialnetworkfx.service.UserService;
import org.example.socialnetworkfx.socialnetworkfx.utils.observer.Observer;
import org.example.socialnetworkfx.socialnetworkfx.utils.paging.Page;
import org.example.socialnetworkfx.socialnetworkfx.utils.paging.Pageable;

import java.io.IOException;
import java.util.ArrayList;

public class MainMenuView implements Observer<FriendshipEntityChange>{
    @FXML
    public TableColumn<User,String> firstnameColumn;
    @FXML
    public TableView<User> tableView;
    @FXML
    public TableColumn<User,String> lastnameColumn;
    @FXML
    public TableColumn<User, String> sinceColumn;
    @FXML
    public Label userNameField;
    @FXML
    public ImageView chatImage;
    @FXML
    public ImageView settingImage;
    @FXML
    public ImageView addImage;
    @FXML
    public ImageView deleteImage;
    @FXML
    public ImageView editImage;
    @FXML
    public Label numberOfRequests;
    @FXML
    public ImageView redDot;
    @FXML
    public Label errorMessage;
    @FXML
    public Button lastPage;
    @FXML
    public Button nextPage;
    @FXML
    public Label pageText;


    private Long IDUser;
    private UserService userService;
    private FriendshipService friendshipService;
    private FriendshipRequestService requestService;
    private MessageService messageService;
    private Stage stage;
    ObservableList<User> model = FXCollections.observableArrayList();

    private int currentPage=0;
    private int maxPages;
    private Pageable pageable;
    private Page<Friendship> page;

    public void setService(Long IDUser, UserService userService, FriendshipService friendshipService, FriendshipRequestService requestService, MessageService messageService, Stage stage) {
        this.IDUser = IDUser;
        this.userService = userService;
        this.friendshipService = friendshipService;
        this.requestService = requestService;
        this.messageService = messageService;
        this.stage = stage;
        this.pageable=new Pageable(0,3);
        this.page=friendshipService.findAllOnPage(pageable,IDUser);
        friendshipService.addObserver(this);
        initModel();
    }

    public void initialize() {

        firstnameColumn.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        lastnameColumn.setCellValueFactory(new PropertyValueFactory<>("lastName"));

        sinceColumn.setCellValueFactory(cellData -> {
            Long senderId = cellData.getValue().getID();
            Friendship sender = friendshipService.findOne(senderId, IDUser);
            return new SimpleStringProperty(sender != null ? sender.getDatesince() : "Unknown");
        });

        tableView.setItems(model);

    }

    private void initModel() {
       ArrayList<User> messages = friendshipService.getFriends(IDUser, friendshipService.findAll());
        setUser(IDUser);
        if (requestService.getNoNewRequest(IDUser) > 0) {
            redDot.setVisible(true);
            numberOfRequests.setVisible(true);
            numberOfRequests.setText(String.valueOf(requestService.getNoNewRequest(IDUser)));
        } else {
            redDot.setVisible(false);
            numberOfRequests.setVisible(false);
        }
        maxPages=messages.size()/ pageable.getPageSize();
        handlePageChange();

    }

    public void setUser(Long IDUser) {
        User user = userService.findOne(IDUser);
        String fullName = user.getFirstName() + " " + user.getLastName();
        userNameField.setText(fullName);
    }

    public void handleAcceptRequest(MouseEvent actionEvent) throws IOException {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("/org/example/socialnetworkfx/socialnetworkfx/accept-request.fxml"));

        AnchorPane root = (AnchorPane) loader.load();
        Scene scene = new Scene(root);
        Stage stage2 = new Stage();
        stage2.setScene(scene);
        stage2.setTitle("Mico App");

        AcceptRequest requestView = loader.getController();
        requestView.setService(requestService, userService, friendshipService, IDUser);
        stage2.show();

    }

    @Override
    public void update(FriendshipEntityChange friendshipEntityChange) {
        initModel();
    }

    public void handleRemoveFriend(MouseEvent actionEvent) {
        try {
            User request = (User) tableView.getSelectionModel().getSelectedItem();
            Friendship friendship = friendshipService.findOne(request.getID(), IDUser);
            FriendshipRequest friendshipRequest = requestService.findByIDs(IDUser, request.getID());
            requestService.delete(friendshipRequest.getID());
            friendshipService.delete(friendship.getID());
        }catch(Exception e) {
            errorMessage.setVisible(true);
            errorMessage.setText("Please select a friend to remove!");
        }

    }

    public void handleRemoveUser(MouseEvent actionEvent) {
        friendshipService.removeAllByID(IDUser);
        requestService.removeAllByID(IDUser);
        messageService.removeByID(IDUser);
        userService.delete(IDUser);
        stage.close();

    }

    public void handleAccountSetting(MouseEvent actionEvent) throws IOException {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("/org/example/socialnetworkfx/socialnetworkfx/settings-view.fxml"));

        AnchorPane root = (AnchorPane) loader.load();
        Scene scene = new Scene(root);
        Stage stage2 = new Stage();
        stage2.setScene(scene);
        stage2.setTitle("Mico App");
        SettingsView settingsView = loader.getController();
        settingsView.setService(userService, IDUser);
        stage2.show();
    }

    public void handleChat(MouseEvent actionEvent) {
        try {
            User request = (User) tableView.getSelectionModel().getSelectedItem();

            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("/org/example/socialnetworkfx/socialnetworkfx/chat-view.fxml"));

            AnchorPane root = (AnchorPane) loader.load();
            Scene scene = new Scene(root);
            Stage stage2 = new Stage();
            stage2.setScene(scene);
            stage2.setTitle("Mico App");
            ChatView chatView = loader.getController();
            String name = request.getFirstName() + " " + request.getLastName();
            chatView.setService(messageService, userService, request.getID(), IDUser, name);
            stage2.show();
        } catch (Exception e) {
            errorMessage.setText("Please select a user to chat!");
            errorMessage.setVisible(true);
        }
    }
    private void handlePageChange() {
        ArrayList<User> usersOnNewPage = friendshipService.getFriends(IDUser, page.getElementsOnPage());
        model.clear();
        model.setAll(usersOnNewPage);
        pageText.setText("Page "+pageable.getPageNumber()+" of "+maxPages);
    }


    public void handleBackPage(ActionEvent actionEvent) {
        pageable.setPageNumber(Math.max((pageable.getPageNumber()-1),0));
        page=friendshipService.findAllOnPage(pageable,IDUser);
        handlePageChange();
    }

    public void handleNextPage(ActionEvent actionEvent) {
        pageable.setPageNumber(Math.min((pageable.getPageNumber()+1),maxPages));
        page=friendshipService.findAllOnPage(pageable,IDUser);
        handlePageChange();
    }
}
