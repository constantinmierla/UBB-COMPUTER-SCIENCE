package org.example.socialnetworkfx.socialnetworkfx.ui;//package org.example.org.example.socialnetworkfx.socialnetworkfx.org.example.socialnetworkfx.socialnetworkfx.ui;
//
//import org.example.org.example.socialnetworkfx.socialnetworkfx.org.example.socialnetworkfx.socialnetworkfx.domain.User;
//import org.example.org.example.socialnetworkfx.socialnetworkfx.org.example.socialnetworkfx.socialnetworkfx.domain.validation.ValidationException;
//import org.example.org.example.socialnetworkfx.socialnetworkfx.org.example.socialnetworkfx.socialnetworkfx.service.CommunityService;
//import org.example.org.example.socialnetworkfx.socialnetworkfx.org.example.socialnetworkfx.socialnetworkfx.service.FriendshipService;
//import org.example.org.example.socialnetworkfx.socialnetworkfx.org.example.socialnetworkfx.socialnetworkfx.service.UserService;
//
//import java.util.List;
//import java.util.Scanner;
//import java.util.Set;
//
//public class Console {
//    private UserService userService;
//    private FriendshipService friendshipService;
//    private CommunityService communityService;
//
//    public Console(UserService userService, FriendshipService friendshipService, CommunityService communityService) {
//        this.userService = userService;
//        this.friendshipService = friendshipService;
//        this.communityService = communityService;
//    }
//
//    public void addUser() {
//        Scanner scanner = new Scanner(System.in);
//        System.out.print("Please enter user's first name: ");
//        String firstName = scanner.nextLine();
//        System.out.print("Please enter user's last name: ");
//        String lastName = scanner.nextLine();
//
//        try {
//            userService.save(firstName, lastName);
//            System.out.print("User was added successfully!\n");
//        } catch (ValidationException | IllegalArgumentException e) {
//            System.out.println(e.getMessage());
//        }
//    }
//
//    public void addFriendship() {
//        Scanner scanner = new Scanner(System.in);
//        System.out.print("Please enter first's user ID: ");
//        Long userId1 = scanner.nextLong();
//        System.out.print("Please enter second's user ID: ");
//        Long userId2 = scanner.nextLong();
//        try {
//            friendshipService.save(userId1, userId2);
//        } catch (ValidationException | IllegalArgumentException e) {
//            System.out.println(e.getMessage());
//        }
//    }
//
//    public void removeUser() {
//        Scanner scanner = new Scanner(System.in);
//        System.out.print("Please enter user's ID: ");
//        Long userId1 = scanner.nextLong();
//        try {
//            userService.delete(userId1);
//            System.out.print("User was deleted successfully!\n");
//        } catch (ValidationException | IllegalArgumentException e) {
//            System.out.println(e.getMessage());
//        }
//    }
//
//    public void removeFriendship() {
//        Scanner scanner = new Scanner(System.in);
//        System.out.println("Please enter friendship's ID: ");
//        Long friendshipID = scanner.nextLong();
//        try {
//            friendshipService.delete(friendshipID);
//            System.out.print("Friendship with ID " + friendshipID + " was deleted successfully!\n");
//        } catch (ValidationException | IllegalArgumentException e) {
//            System.out.println(e.getMessage());
//        }
//    }
//
//    public void showUsers() {
//        Iterable<User> allUsers = userService.findAll();
//        allUsers.forEach(user -> System.out.println(user.getID() + " " + user.getFirstName() + " " + user.getLastName() + "\n"));
//    }
//
//    public void showFriendships() {
//        Iterable<User> allUsers = userService.findAll();
//        allUsers.forEach(user -> {
//            System.out.print(user.getFirstName() + "'s friendships: ");
//            userService.getFriends(user.getID())
//                    .forEach(user1 -> {
//                                System.out.print(user1.getFirstName() + " " + user1.getLastName() + ",");
//                            }
//                    );
//            System.out.println();
//        });
//    }
//
//    public void updateUser() {
//        Scanner scanner = new Scanner(System.in);
//        System.out.println("Please enter user's ID: ");
//        Long userID = Long.parseLong(scanner.nextLine());
//        System.out.print("Please enter new user's first name: ");
//        String firstName = scanner.nextLine();
//        System.out.print("Please enter new user's last name: ");
//        String lastName = scanner.nextLine();
//        try {
//            userService.update(userID, firstName, lastName);
//        } catch (ValidationException | IllegalArgumentException e) {
//            System.out.println(e.getMessage());
//        }
//    }
//
//    public void showCommunities() {
//        List<Set<Long>> communities = communityService.getCommunityGraph();
//        communities.forEach(community -> {community.forEach(
//                                            ID->{User user=userService.findOne(ID);
//                                                System.out.println(user.getID()+" "+user.getFirstName() + " " + user.getLastName());});
//                                         System.out.println();});
//        System.out.println("Total number of communities:" + communities.size());
//
//    }
//
//    public void showBiggestCommunity() {
//        System.out.println("Biggest community:");
//        Set<Long> community = communityService.biggestCommunity();
//        community.forEach(ID->{User user=userService.findOne(ID);
//                               System.out.println(user.getID()+" "+user.getFirstName() + " " + user.getLastName());});
//        System.out.println();
//    }
//
//    public void menu() {
//        System.out.println("1. Add User");
//        System.out.println("2. Add Friendship");
//        System.out.println("3. Remove User");
//        System.out.println("4. Remove Friendship");
//        System.out.println("5. Update User");
//        System.out.println("6. Show Users");
//        System.out.println("7. Show Friendships");
//        System.out.println("8. Show communities");
//        System.out.println("9. Show biggest community");
//        System.out.println("10. Exit");
//        ;
//    }
//}