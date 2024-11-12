package org.example.demo;

import org.example.demo.domain.validators.FriendshipValidator;
import org.example.demo.domain.validators.UserValidator;
import org.example.demo.repository.FriendshipDBRepository;
import org.example.demo.repository.UserDBRepository;
import org.example.demo.service.CommunityService;
import org.example.demo.service.FriendshipService;
import org.example.demo.service.UserService;
import org.example.demo.ui.UIfunctionalities;

import java.io.IOException;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Properties;

public class Main {
    private static String DATABASE_URL;
    private static String USERNAME;
    private static String PASSWORD;

    static {
        Properties properties = new Properties();
        try (InputStream input = Main.class.getClassLoader().getResourceAsStream("config.properties")) {
            if (input == null) {
                System.out.println("Sorry, unable to find config.properties");
            }
            properties.load(input);
            DATABASE_URL = properties.getProperty("database.url");
            USERNAME = properties.getProperty("database.username");
            PASSWORD = properties.getProperty("database.password");
        } catch (IOException e) {
            System.err.println("Error loading configuration file: " + e.getMessage());
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        UIfunctionalities ui = new UIfunctionalities();

        UserDBRepository repoUsersDB = new UserDBRepository(DATABASE_URL,USERNAME,PASSWORD, new UserValidator());
        FriendshipDBRepository repoFriendsDB = new FriendshipDBRepository(DATABASE_URL,USERNAME, PASSWORD, new FriendshipValidator());

        UserService userService = new UserService(repoUsersDB, repoFriendsDB);
        FriendshipService friendshipService = new FriendshipService(repoUsersDB, repoFriendsDB);
        CommunityService communityService = new CommunityService(repoUsersDB, repoFriendsDB);

        Connection connection = null;
        PreparedStatement insertStmt = null;

        try {
            Class.forName("org.postgresql.Driver");

            connection = DriverManager.getConnection(DATABASE_URL, USERNAME, PASSWORD);
            System.out.println("Connected to database");

            while(true){
                ui.showMenu();
                var option = ui.getOption(0, 6);
                switch(option){
                    case 1 : {
                        var firstName = ui.getName("Firstname: ");
                        var lastName = ui.getName("Lastname: ");

                        var message = userService.addUser(firstName, lastName);
                        ui.showMessage(message);

                        break;
                    }
                    case 2: {
                        // remove user
                        var allUsers = userService.getAll();
                        ui.showAllUsers(allUsers);

                        long id = ui.getUserID("The id for the user that you want to delete: ");
                        var message = userService.deleteUser(id);
                        ui.showMessage(message);

                        break;
                    }
                    case 3: {
                        // add prieten
                        ui.showAllUsers(userService.getAll());

                        long id1 = ui.getUserID("The id for the first user: ");
                        long id2 = ui.getUserID("The id for the second user: ");

                        try {
                            var message = friendshipService.addFriendships(id1, id2);
                            ui.showMessage(message);
                        }
                        catch (Exception e) {
                            ui.showMessage(e.getMessage());
                        }
                        break;
                    }
                    case 4: {
                        // remove prieten
                        ui.showAllUsers(userService.getAll());

                        long id1 = ui.getUserID("The id for the first user: ") ;
                        ui.showAllUsers(friendshipService.getAllFriends(id1));

                        long id2 = ui.getUserID("The id for the second user: ");
                        String message = friendshipService.deleteFriendship(id1, id2);
                        ui.showMessage(message);

                        break;
                    }
                    case 5: {
                        var communities = communityService.getCommunityGraph();

                        try {
                            ui.showCommunities(repoUsersDB, communities);
                        }
                        catch (Exception e) {
                            ui.showMessage(e.getMessage());
                        }

                        break;
                    }
                    case 6: {
                        var mostSociableCommunity = communityService.biggestCommunity();

                        if(mostSociableCommunity.isEmpty())
                            ui.showMessage("there is no more sociable community");
                        else {
                            try {
                                ui.showBiggestCommunity(repoUsersDB, mostSociableCommunity);
                            } catch (Exception e) {
                                ui.showMessage(e.getMessage());
                            }
                        }

                        break;
                    }
                    case 0 : {
                        return ;
                    }
                    default : {
                        throw new RuntimeException();
                    }
                }
            }
        }
        catch (SQLException e) {
            System.out.println("SQL Exception: " + e.getMessage());
        }
        catch (ClassNotFoundException e) {
            System.out.println("Driver not found: " + e.getMessage());
        }
        finally {
            try {
                if (connection != null) connection.close();
                System.out.println("Database resources released");
            }
            catch (SQLException e) {
                System.out.println("Error closing resources: " + e.getMessage());
            }
        }
    }
}
