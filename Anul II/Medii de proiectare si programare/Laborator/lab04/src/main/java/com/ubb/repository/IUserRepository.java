package com.ubb.repository;

import com.ubb.model.User;

import java.util.Optional;

public interface IUserRepository extends IRepository<Long, User> {
    Optional<User> getByUsernameAndPassword(String username, String password);
}
