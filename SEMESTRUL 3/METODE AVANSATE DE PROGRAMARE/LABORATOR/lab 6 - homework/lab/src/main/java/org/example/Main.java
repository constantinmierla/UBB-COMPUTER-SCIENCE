package org.example;

import org.example.domain.User;
import org.example.domain.validators.FriendshipValidator;
import org.example.domain.validators.UserValidator;
import org.example.repository.UserDBRepository;
import org.example.repository.FriendshipDBRepository;
import org.example.service.UserService;
import org.example.service.FriendshipService;
import org.example.service.CommunityService;

import org.example.ui.UIfunctionalities;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class Main {
    private static final String DATABASE_URL = "jdbc:postgresql://localhost:5432/postgres";
    private static final String USERNAME = "postgres";
    private static final String PASSWORD = "costi";

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
