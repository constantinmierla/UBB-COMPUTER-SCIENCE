import domain.Friendship;
import domain.User;
import domain.validators.FriendshipValidator;
import domain.validators.UserValidator;
import domain.validators.ValidationException;
import repository.InMemoryRepository;
import service.SocialNetwork;
import ui.Console;

public class Main {

    public static void main(String[] args) {
        // Initialize repositories for Users and Friendships
        InMemoryRepository<Long, User> repoUser = new InMemoryRepository<>(new UserValidator());
        InMemoryRepository<Long, Friendship> repoFriendship = new InMemoryRepository<>(new FriendshipValidator(repoUser));

        // Create the social network service
        SocialNetwork socialNetwork = new SocialNetwork(repoUser, repoFriendship);
        Console ui = new Console(socialNetwork);

        User u1 = new User("Andrei", "Popescu");
        User u2 = new User("Maria", "Ionescu");
        User u3 = new User("Ion", "Vasilescu");
        User u4 = new User("Elena", "Dumitru");
        User u5 = new User("George", "Petrescu");
        User u6 = new User("Ana", "Stanescu");
        User u7 = new User("Cristian", "Marin");

        // Add users to the social network
        socialNetwork.addUser(u1);
        socialNetwork.addUser(u2);
        socialNetwork.addUser(u3);
        socialNetwork.addUser(u4);
        socialNetwork.addUser(u5);
        socialNetwork.addUser(u6);
        socialNetwork.addUser(u7);

        // Create friendships
        try {
            socialNetwork.addFriendship(new Friendship(u1.getId(), u2.getId())); // Andrei <-> Maria
            socialNetwork.addFriendship(new Friendship(u2.getId(), u3.getId())); // Maria <-> Ion
            socialNetwork.addFriendship(new Friendship(u3.getId(), u4.getId())); // Ion <-> Elena
            socialNetwork.addFriendship(new Friendship(u5.getId(), u6.getId())); // George <-> Ana
            socialNetwork.addFriendship(new Friendship(u6.getId(), u7.getId())); // Ana <-> Cristian
            socialNetwork.addFriendship(new Friendship(u5.getId(), u7.getId())); // George <-> Cristian
        } catch (ValidationException e) {
            System.err.println("Error adding friendship: " + e.getMessage());
        }

        // Run the user interface
        ui.run();
    }
}
