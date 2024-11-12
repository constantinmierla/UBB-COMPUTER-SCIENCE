package org.example.ui;

import org.example.domain.User;
import org.example.repository.UserDBRepository;

import java.util.*;

/**
 * Provides user interface functionalities for managing and displaying user and friendship data.
 */
public class UIfunctionalities {

    /**
     * Displays the main menu options for the user.
     */
    public void showMenu(){
        System.out.println("Menu");
        System.out.println("1. Add user");
        System.out.println("2. Remove user");
        System.out.println("3. Add friend");
        System.out.println("4. Remove friend");
        System.out.println("5. Show the number of communities");
        System.out.println("6. The most sociable community");
        System.out.println("0. Exit");
    }

    /**
     * Prompts the user to select an option and validates the input.
     *
     * @param n1 the minimum valid option number
     * @param n2 the maximum valid option number
     * @return the validated option number
     */
    public int getOption(int n1, int n2){
        Scanner scanner = new Scanner(System.in);
        int number;
        do{
            System.out.print("Your option: ");
            String input = scanner.next();
            try{
                number = Integer.parseInt(input);
                if(number < n1 || number > n2){
                    System.out.println("The option's number must be between "+ n1 + " and " + n2 + "!");
                }
            } catch(NumberFormatException e){
                System.out.println("Invalid number!");
                number = -1;
            }
        } while(number < n1 || number > n2);

        return number;
    }

    /**
     * Displays a message to the user.
     *
     * @param message the message to display
     */
    public void showMessage(String message) {
        System.out.println(message);
    }

    /**
     * Displays all users in the provided collection.
     *
     * @param users an iterable collection of {@link User} entities
     */
    public void showAllUsers(Collection<User> users) {
        users.stream()
                .sorted(Comparator.comparing(User::getId))
                .forEach(System.out::println);
    }

    /**
     * Prompts the user for a name input and returns it.
     *
     * @param message the prompt message to display
     * @return the entered name
     */
    public String getName(String message) {
        Scanner scanner = new Scanner(System.in);

        System.out.println(message);

        return scanner.next();
    }

    /**
     * Prompts the user for a user ID and validates the input.
     *
     * @param message the prompt message to display
     * @return the validated user ID
     */
    public long getUserID(String message) {
        Scanner scanner = new Scanner(System.in);
        long id;
        do {
            System.out.println(message);
            String input = scanner.next();

            try {
                id = Long.parseLong(input);
                return id;
            }
            catch (NumberFormatException e) {
                System.out.println("You have entered a wrong id!");
            }
        }while(true);
    }

    /**
     * Displays all communities and their members.
     *
     * @param users      the repository of users
     * @param communities a list of sets representing the communities
     */
    public void showCommunities(UserDBRepository users, List<Set<Long>> communities) {
        System.out.println("The communities are: ");
        final int[] i = {1};
        communities.stream().filter(community -> community.size() > 1)
                .forEach(community -> {
                    System.out.println("The community " + i[0] + ": ");
                    i[0]++;

                    community.forEach(id -> {
                        var user = users.findOne(id).orElseThrow(() -> new IllegalArgumentException("No user with id was found " + id));
                        System.out.println(user.getFirstname() + " " + user.getLastname());
                    });
                });
        i[0]--;
        System.out.println("Total number of communities: " + i[0]);
        System.out.println("The other users are not in a community: ");
    }

    /**
     * Displays the members of the largest community.
     *
     * @param users    the repository of users
     * @param community a set representing the largest community
     */
    public void showBiggestCommunity(UserDBRepository users, Set<Long> community) {
        System.out.println("Largest community: ");
        community.forEach(id -> {
            var user = users.findOne(id).orElseThrow(() -> new IllegalArgumentException("No user with id was found" + id));
            System.out.println(user.getFirstname() + " " + user.getLastname());
        });
        System.out.println("Number of people in the community: " + community.size());
    }
}
