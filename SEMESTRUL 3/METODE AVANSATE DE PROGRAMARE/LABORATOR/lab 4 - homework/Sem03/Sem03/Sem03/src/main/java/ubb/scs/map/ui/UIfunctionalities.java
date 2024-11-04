package ubb.scs.map.ui;

import ubb.scs.map.domain.Utilizator;
import ubb.scs.map.repository.InMemoryRepository;

import java.util.List;
import java.util.Scanner;
import java.util.Set;

/**
 * Provides user interface functionalities for managing and displaying user and friendship data.
 */
public class UIfunctionalities {
    /**
     * Displays the main menu options for the user.
     */
    public void showMenu() {
        System.out.println("Meniu ");
        System.out.println("1. Add utilizator");
        System.out.println("2. Remove utilizator");
        System.out.println("3. Add prieten");
        System.out.println("4. Remove prieten");
        System.out.println("5. Afiseaza numarul de comunitati");
        System.out.println("6. Afiseaza cea mai sociabila comunitate");
        System.out.println("0. Iesire");
    }

    /**
     * Prompts the user to select an option and validates the input.
     *
     * @param n1 the minimum valid option number
     * @param n2 the maximum valid option number
     * @return the validated option number
     */
    public int getOption(int n1, int n2) {
        Scanner scanner = new Scanner(System.in);
        int number;

        do {
            System.out.print("Introduceți o optiune: ");
            String input = scanner.next();

            // Verificăm dacă inputul conține doar caractere numerice
            try {
                number = Integer.parseInt(input);

                if (number < n1 || number > n2) {
                    System.out.println("Numărul optiunii trebuie să fie între " + n1 + " si " + n2 + "!");
                }
            } catch (NumberFormatException e) {
                // Afișăm mesajul de eroare dacă inputul nu este un număr valid
                System.out.println("Nu ați introdus un număr valid!");
                number = -1;
            }
        } while (number < n1 || number > n2);

        return number;
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
                System.out.println("Ati introdus un id gresit!");
            }
        }while(true);
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
     * @param users an iterable collection of {@link Utilizator} entities
     */
    public void showAllUsers(Iterable<Utilizator> users) {
        users.forEach(System.out::println);
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
     * Displays all communities and their members.
     *
     * @param users      the repository of users
     * @param communities a list of sets representing the communities
     */
    public void showCommunities(InMemoryRepository<Long, Utilizator> users, List<Set<Long>> communities) {
        System.out.println("Comunitatile sunt: ");
        final int[] i = {1};
        communities.stream().filter(community -> community.size() > 1)
                .forEach(community -> {
                    System.out.println("Comunitatea " + i[0] + ": ");
                    i[0]++;

                    community.forEach(id -> {
                        var user = users.findOne(id).orElseThrow(() -> new IllegalArgumentException("Nu a fost gasit user cu id " + id));
                        System.out.println(user.getFirstName() + " " + user.getLastName());
                    });
                });
        i[0]--;
        System.out.println("Numar total de comunitati: " + i[0]);
        System.out.println("Ceilalti utilizatori nu sunt intr-o comunitate (antisociali)");
    }

    /**
     * Displays the members of the largest community.
     *
     * @param users    the repository of users
     * @param community a set representing the largest community
     */
    public void showBiggestCommunity(InMemoryRepository<Long, Utilizator> users, Set<Long> community) {
        System.out.println("Cea mai mare comunitate: ");
        community.forEach(id -> {
            var user = users.findOne(id).orElseThrow(() -> new IllegalArgumentException("Nu a fost gasit user cu id " + id));
            System.out.println(user.getFirstName() + " " + user.getLastName());
        });
        System.out.println("Numarul de persoane din comunitate: " + community.size());
    }
}
