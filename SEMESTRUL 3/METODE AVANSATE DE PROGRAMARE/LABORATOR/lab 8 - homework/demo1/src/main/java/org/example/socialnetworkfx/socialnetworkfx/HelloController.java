//package org.example.org.example.socialnetworkfx.socialnetworkfx.org.example.socialnetworkfx.socialnetworkfx;
//
//import javafx.collections.FXCollections;
//import javafx.collections.ObservableList;
//import javafx.fxml.FXML;
//import javafx.fxml.FXMLLoader;
//import javafx.scene.Scene;
//import javafx.scene.control.Label;
//import javafx.scene.control.TableColumn;
//import javafx.scene.control.TableView;
//import javafx.scene.control.cell.PropertyValueFactory;
//import javafx.scene.layout.AnchorPane;
//import javafx.stage.Stage;
//import org.example.org.example.socialnetworkfx.socialnetworkfx.org.example.socialnetworkfx.socialnetworkfx.domain.User;
//import org.example.org.example.socialnetworkfx.socialnetworkfx.org.example.socialnetworkfx.socialnetworkfx.domain.validation.UserValidation;
//import org.example.org.example.socialnetworkfx.socialnetworkfx.org.example.socialnetworkfx.socialnetworkfx.repository.NewRepository;
//import org.example.org.example.socialnetworkfx.socialnetworkfx.org.example.socialnetworkfx.socialnetworkfx.repository.Repository;
//import org.example.org.example.socialnetworkfx.socialnetworkfx.org.example.socialnetworkfx.socialnetworkfx.repository.UserDbRepository;
//import org.example.org.example.socialnetworkfx.socialnetworkfx.org.example.socialnetworkfx.socialnetworkfx.service.FriendshipService;
//import org.example.org.example.socialnetworkfx.socialnetworkfx.org.example.socialnetworkfx.socialnetworkfx.service.UserService;
//
//import java.io.IOException;
//
//public class HelloController {
//    UserDbRepository userRepo;
//    FriendshipService friendshipService;
//    UserService userService;
//    FriendshipService friendshipService2;
//
//    @FXML
//    public TableView<User> tableUser;
//    @FXML
//    public TableColumn ID;
//    @FXML
//    public TableColumn<User,String> firstName;
//    @FXML
//    public TableColumn<User,String> lastName;
//    @FXML
//    private Label welcomeText;
//
//    private ObservableList<User> userList = FXCollections.observableArrayList();
//    public void start(Stage primaryStage) throws IOException {
//
//        String username="postgres";
//        String pasword="1mai1984";
//        String url="jdbc:postgresql://localhost:5432/postgres";
//        UserDbRepository userRepository =
//                new UserDbRepository(url,username, pasword,  new UserValidation());
//
//    }
//    @FXML
//    protected void onHelloButtonClick() {
//        welcomeText.setText("Welcome to JavaFX Application!");
//    }
//}