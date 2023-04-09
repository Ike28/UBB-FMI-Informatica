package com.ubb.service;

import com.ubb.IMainObserver;
import com.ubb.exceptions.RacesException;
import com.ubb.model.User;

import java.util.Optional;

public interface IUserService extends IService<Long, User> {
    Optional<User> getLogin(String username, String password);
}
