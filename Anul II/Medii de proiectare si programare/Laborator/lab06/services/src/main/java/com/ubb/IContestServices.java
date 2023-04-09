package com.ubb;

import com.ubb.exceptions.RacesException;
import com.ubb.model.User;

public interface IContestServices {
    void login(String username, String passwordToken, IMainObserver client) throws RacesException;
    void logout(User user, IMainObserver client) throws RacesException;
}
