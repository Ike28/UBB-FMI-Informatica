package com.ubb.client;

import com.ubb.model.Race;
import org.springframework.web.client.RestTemplate;

import java.util.concurrent.Callable;

public class RestClient {
    public static final String URL = "http://localhost:8080/contest/races";
    private final RestTemplate restTemplate = new RestTemplate();

    private <T> T execute(Callable<T> callable) throws Exception {
        try {
            return callable.call();
        } catch (Exception e) {
            throw new Exception(e);
        }
    }

    public Race[] getAll() throws Exception {
        return execute(() -> restTemplate.getForObject(URL, Race[].class));
    }

    public Race getById(Long id) throws Exception {
        return execute(() -> restTemplate.getForObject(String.format("%s/%s", URL, id), Race.class));
    }

    public Race create(Race race) throws Exception {
        return execute(() -> restTemplate.postForObject(URL, race, Race.class));
    }

    public void update(Race race) throws Exception {
        execute(() -> {
            restTemplate.put(String.format("%s/%s", URL, race.getId()), race);
            return null;
        });
    }

    public void delete(Long id) throws Exception {
        execute(() -> {
            restTemplate.delete(String.format("%s/%s", URL, id));
            return null;
        });
    }
}
