package service;

import domain.Friendship;
import domain.User;

import java.util.*;

/**
 * The SocialCommunities class provides functionality to calculate the number of connected communities
 * (connected components) in a social network and to find the most social community (component with the most connections).
 */
public class SocialCommunities {

    SocialNetwork socialNetwork;        // Reference to the SocialNetwork service
    HashMap<Long, List<Long>> adjList;  // Adjacency list representing users and their friends

    /**
     * Constructor that initializes the SocialCommunities service with a given SocialNetwork instance.
     *
     * @param socialNetwork - the SocialNetwork service used to fetch users and friendships
     */
    public SocialCommunities(SocialNetwork socialNetwork) {
        this.socialNetwork = socialNetwork;
    }

    /**
     * Depth-First Search (DFS) helper method to explore all friends (connections) of a user.
     *
     * @param v - the ID of the user being explored
     * @param visited - a map that keeps track of visited users to avoid cycles
     */
    void DFS(Long v, HashMap<Long, Boolean> visited) {
        visited.put(v, true);  // Mark user as visited
        System.out.println(v + " " + this.socialNetwork.findUser(v).getFirstname() + " " + this.socialNetwork.findUser(v).getLastname());
        // Recursively explore all unvisited friends
        if (adjList.containsKey(v)) {
            for (Long x : adjList.get(v)) {
                if (!visited.containsKey(x))
                    DFS(x, visited);
            }
        }
    }

    /**
     * Computes the number of connected communities (connected components) in the social network.
     * This is done by creating an adjacency list and performing DFS on unvisited nodes (users).
     *
     * @return the number of connected communities
     */
    public int connectedCommunities() {
        // Creates an adjacency list of users and their friends
        adjList = new HashMap<>();
        for (User user : socialNetwork.getUsers()) {
            List<Long> friends = new ArrayList<>();
            for (Friendship friendship : socialNetwork.getFriendships()) {
                if (friendship.getIdUser1().equals(user.getId()))
                    friends.add(friendship.getIdUser2());
                if (friendship.getIdUser2().equals(user.getId()))
                    friends.add(friendship.getIdUser1());
            }
            if (!friends.isEmpty())
                this.adjList.put(user.getId(), friends);  // Add user and their friends to the adjacency list
        }

        // List of all user IDs
        List<Long> ids = new ArrayList<>();
        for (User user : socialNetwork.getUsers())
            ids.add(user.getId());

        int nrOfCommunities = 0;  // Counter for the number of communities
        HashMap<Long, Boolean> visited = new HashMap<>();  // Map to track visited users
        // Perform DFS for each unvisited user
        for (Long v : ids) {
            if (!visited.containsKey(v)) {
                DFS(v, visited);  // Explore the community of user 'v'
                nrOfCommunities++;
                System.out.println();  // Separate communities by a new line
            }
        }
        return nrOfCommunities;  // Return the number of connected communities
    }

    /**
     * Identifies the most social community in the network, defined as the community with the most connections.
     * It iterates through all users and tracks the community with the largest number of members.
     *
     * @return a list of user IDs representing the most social community
     */
    public List<Long> mostSocialCommunity() {
        // Creates an adjacency list of users and their friends
        adjList = new HashMap<>();
        List<Long> max = new ArrayList<>();  // List to store the most social community
        for (User user : socialNetwork.getUsers()) {
            List<Long> friends = new ArrayList<>();
            for (Friendship friendship : socialNetwork.getFriendships()) {
                if (friendship.getIdUser1().equals(user.getId()))
                    friends.add(friendship.getIdUser2());
                if (friendship.getIdUser2().equals(user.getId()))
                    friends.add(friendship.getIdUser1());
            }
            if (!friends.isEmpty()) {
                this.adjList.put(user.getId(), friends);  // Add user and their friends to the adjacency list
                // Update the largest community if the current user's friends list is larger
                if (max.size() < friends.size() + 1) {
                    max = friends;
                    max.add(user.getId());  // Include the user in the community
                }
            }
        }
        return max;  // Return the most social community
    }
}
