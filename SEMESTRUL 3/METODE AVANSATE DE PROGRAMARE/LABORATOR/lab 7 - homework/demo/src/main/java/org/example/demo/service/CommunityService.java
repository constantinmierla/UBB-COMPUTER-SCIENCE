package org.example.demo.service;

import org.example.demo.repository.FriendshipDBRepository;
import org.example.demo.repository.UserDBRepository;
import org.jgrapht.Graph;
import org.jgrapht.alg.connectivity.ConnectivityInspector;
import org.jgrapht.graph.DefaultEdge;
import org.jgrapht.graph.SimpleGraph;

import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Set;

/**
 * Provides services for analyzing user communities based on friendships, including generating community graphs
 * and identifying the largest community.
 */
public class CommunityService {
    private final UserDBRepository userRepository;
    private final FriendshipDBRepository friendshipRepository;

    /**
     * Constructs a CommunityService with specified user and friendship repositories.
     *
     * @param userRepo repository for user data
     * @param friendshipRepo repository for friendship data
     */
    public CommunityService(UserDBRepository userRepo, FriendshipDBRepository friendshipRepo) {
        this.userRepository = userRepo;
        this.friendshipRepository = friendshipRepo;
    }

    /**
     * Builds a graph of communities, where each community is represented as a set of user IDs.
     *
     * @return a list of sets, each representing a connected community of users
     */
    public List<Set<Long>> getCommunityGraph() {
        Graph<Long, DefaultEdge> graph = new SimpleGraph<>(DefaultEdge.class);

        var users = userRepository.findAll();
        users.forEach(u -> graph.addVertex(u.getId()));

        var friendships = friendshipRepository.findAll();
        friendships.forEach(f -> graph.addEdge(f.getFirstUser().getId(), f.getSecondUser().getId()));

        return new ConnectivityInspector<>(graph).connectedSets();
    }

    /**
     * Finds the largest community by the number of users.
     *
     * @return a set of user IDs representing the largest community
     */
    public Set<Long> biggestCommunity() {
        return getCommunityGraph().stream()
                .max(Comparator.comparingInt(Set::size))
                .orElse(Collections.emptySet());
    }
}
