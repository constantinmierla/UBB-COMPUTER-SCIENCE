//package org.example.org.example.socialnetworkfx.socialnetworkfx.org.example.socialnetworkfx.socialnetworkfx.service;
//
//import org.example.org.example.socialnetworkfx.socialnetworkfx.org.example.socialnetworkfx.socialnetworkfx.repository.FriendshipDbRepository;
//import org.example.org.example.socialnetworkfx.socialnetworkfx.org.example.socialnetworkfx.socialnetworkfx.repository.UserDbRepository;
//import org.jgrapht.Graph;
//import org.jgrapht.alg.connectivity.ConnectivityInspector;
//import org.jgrapht.graph.DefaultEdge;
//import org.jgrapht.graph.SimpleGraph;
//
//import java.util.Comparator;
//import java.util.HashSet;
//import java.util.List;
//import java.util.Set;
//
//public class CommunityService {
//    private UserDbRepository userRepository;
//    private FriendshipDbRepository friendshipRepository;
//
//    public CommunityService(UserDbRepository userRepository, FriendshipDbRepository friendshipRepository) {
//        this.userRepository = userRepository;
//        this.friendshipRepository = friendshipRepository;
//    }
//
//    public List<Set<Long>> getCommunityGraph() {
//        Graph<Long, DefaultEdge> graph = new SimpleGraph<>(DefaultEdge.class);
//        userRepository.findAll().forEach(user -> {graph.addVertex(user.getID());});
//        friendshipRepository.findAll()
//                .forEach(friendship -> graph
//                        .addEdge(friendship.getFirstFriend().getID(),friendship.getSecondFriend().getID()));
//        return new ConnectivityInspector<>(graph).connectedSets();
//    }
//    public Set<Long> biggestCommunity() {
//        List<Set<Long>> communityGraph = getCommunityGraph();
//        return communityGraph.stream()
//                        .max(Comparator.comparingInt(Set::size))
//                        .orElse(new HashSet<>());
//    }
//
//}
