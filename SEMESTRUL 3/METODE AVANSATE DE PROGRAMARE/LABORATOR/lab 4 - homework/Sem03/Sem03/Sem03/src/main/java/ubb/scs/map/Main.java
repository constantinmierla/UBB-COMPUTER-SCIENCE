package ubb.scs.map;

import ubb.scs.map.domain.validators.FriendshipValidator;
import ubb.scs.map.domain.validators.UtilizatorValidator;
import ubb.scs.map.repository.FriendshipRepository;
import ubb.scs.map.repository.UtilizatorRepository;
import ubb.scs.map.service.CommunityService;
import ubb.scs.map.service.FriendshipService;
import ubb.scs.map.service.UserService;
import ubb.scs.map.ui.UIfunctionalities;

public class Main {
    public static void main(String[] args) {
        UIfunctionalities ui = new UIfunctionalities();
        UtilizatorRepository repoFileUsers = new UtilizatorRepository(new UtilizatorValidator(), "Sem03/data/utilizatori.txt");
        FriendshipRepository repoFileFriendships = new FriendshipRepository(new FriendshipValidator(), "Sem03/data/friendships.txt");

        UserService userService = new UserService(repoFileUsers, repoFileFriendships);
        FriendshipService friendshipService = new FriendshipService(repoFileUsers, repoFileFriendships);
        CommunityService communityService = new CommunityService(repoFileUsers, repoFileFriendships);

        while(true) {
            ui.showMenu();
            var opt = ui.getOption(0, 6);

            switch(opt) {
                case 1: {
                    // add user
                    var firstName = ui.getName("Introdu prenumele noului utilizator: ");
                    var lastName = ui.getName("Introdu numele noului friendship: ");

                    var message = userService.addUser(firstName, lastName);
                    ui.showMessage(message);

                    break;
                }
                case 2: {
                    // remove user
                    var allUsers = userService.getAll();
                    ui.showAllUsers(allUsers);

                    long id = ui.getUserID("Introdu id-ul userului pe care vrei sa il stergi: ");
                    var message = userService.deleteUser(id);
                    ui.showMessage(message);

                    break;
                }
                case 3: {
                    // add prieten
                    ui.showAllUsers(userService.getAll());

                    long id1 = ui.getUserID("Introdu id-ul userului pentru care vrei sa adaugi prieten: ");
                    long id2 = ui.getUserID("Introdu id-ul userului pt a face prietenia: ");

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

                    long id1 = ui.getUserID("Introdu id-ul userului pentru care vrei sa stergi un prieten: ") ;
                    ui.showAllUsers(friendshipService.getAllFriends(id1));

                    long id2 = ui.getUserID("Introdu id-ul userului pt care vrei sa stergi prietenia: ");
                    String message = friendshipService.deleteFriendship(id1, id2);
                    ui.showMessage(message);

                    break;
                }
                case 5: {
                    // afisare numar comunitati (nr componente conexe)
                    var communities = communityService.getCommunityGraph();

                    try {
                        ui.showCommunities(repoFileUsers, communities);
                    }
                    catch (Exception e) {
                        ui.showMessage(e.getMessage());
                    }

                    break;
                }
                case 6: {
                    // cea mai sociabila comunitate (comp conexa cu cel mai lung drum)
                    var mostSociableCommunity = communityService.biggestCommunity();

                    if(mostSociableCommunity.isEmpty())
                        ui.showMessage("Nu exista cea mai sociabila comunitate");
                    else {
                        try {
                            ui.showBiggestCommunity(repoFileUsers, mostSociableCommunity);
                        } catch (Exception e) {
                            ui.showMessage(e.getMessage());
                        }
                    }

                    break;
                }
                case 0: {
                    return;
                }
                default: {
                    throw new RuntimeException();
                }
            }
        }

    }
}