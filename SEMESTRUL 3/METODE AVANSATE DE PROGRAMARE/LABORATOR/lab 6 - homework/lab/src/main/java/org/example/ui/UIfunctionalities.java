package org.example.ui;

import org.example.domain.User;
import org.example.repository.UserDBRepository;

import java.util.*;

public class UIfunctionalities {

    public void showMenu(){
        System.out.println("Menu");
        System.out.println("1. Add user");
        System.out.println("2. Remove user");
        System.out.println("3. Add friend");
        System.out.println("4. Remove friend");
        System.out.println("5. Show the number of communities");
        System.out.println("6. The most social community");
        System.out.println("0. Exit");
    }

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
    public void showMessage(String message) {
        System.out.println(message);
    }
    public void showAllUsers(Collection<User> users) {
        users.stream()
                .sorted(Comparator.comparing(User::getId))
                .forEach(System.out::println);
    }

    public String getName(String message) {
        Scanner scanner = new Scanner(System.in);

        System.out.println(message);

        return scanner.next();
    }

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

    public void showBiggestCommunity(UserDBRepository users, Set<Long> community) {
        System.out.println("Largest community: ");
        community.forEach(id -> {
            var user = users.findOne(id).orElseThrow(() -> new IllegalArgumentException("No user with id was found" + id));
            System.out.println(user.getFirstname() + " " + user.getLastname());
        });
        System.out.println("Number of people in the community: " + community.size());
    }
}
