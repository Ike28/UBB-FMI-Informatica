package com.ubb;

import com.ubb.exceptions.RacesException;
import com.ubb.model.User;
import com.ubb.service.IUserService;

import java.util.Map;
import java.util.Optional;
import java.util.concurrent.ConcurrentHashMap;

public class ContestServices implements IContestServices {
    private final IUserService userService;
    private final Map<String, IMainObserver> loggedClients;
    private static final int DEFAULT_THREADS = 5;

    public ContestServices(IUserService userService) {
        this.userService = userService;
        loggedClients = new ConcurrentHashMap<>();
    }

    @Override
    public synchronized void login(String username, String passwordToken, IMainObserver client) throws RacesException {
        Optional<User> foundUser = userService.getLogin(username, passwordToken);
        if (foundUser.isPresent()) {
            if (loggedClients.get(username) != null) {
                throw new RacesException("User already logged in.");
            }
            loggedClients.put(username, client);
        } else {
            throw new RacesException("Authentication failed.");
        }
    }

    @Override
    public synchronized void logout(User user, IMainObserver client) throws RacesException {
        IMainObserver localClient = loggedClients.remove(user.getUsername());
        if (localClient == null) {
            throw new RacesException("User " + user.getUsername() + " is not logged in.");
        }
    }
}
