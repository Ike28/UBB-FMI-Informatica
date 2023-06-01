package com.ubb.controller;

import com.ubb.model.Race;
import com.ubb.repository.jdbc.RaceDBRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.Optional;

@RestController
@RequestMapping("/contest/races")
public class RaceController {
    private static final String template = "Hello, %s!";

    @Autowired
    private RaceDBRepository raceRepository;

    @CrossOrigin(origins = "http://localhost:5623")
    @GetMapping("/greeting")
    public String greeting(@RequestParam(value = "name", defaultValue = "World") String name) {
        return String.format(template, name);
    }

    @CrossOrigin(origins = "http://localhost:5623")
    @RequestMapping(method = RequestMethod.GET)
    public List<Race> getAll() {
        return raceRepository.findAll().stream().toList();
    }

    @CrossOrigin(origins = "http://localhost:5623")
    @RequestMapping(value = "/{id}", method = RequestMethod.GET)
    public ResponseEntity<?> getById(@PathVariable String id) {

        System.out.println("Get By ID: " + id);

        Optional<Race> race = raceRepository.findById(Long.parseLong(id));
        if (race.isEmpty())
            return new ResponseEntity<>("Race not found!", HttpStatus.NOT_FOUND);

        else {
            Race result = race.get();
            result.setId(Long.parseLong(id));
            return new ResponseEntity<>(result, HttpStatus.OK);
        }
    }

    @CrossOrigin(origins = "http://localhost:5623")
    @RequestMapping(method = RequestMethod.POST)
    public Race create(@RequestBody Race race) {
        System.out.println("Adding Race: " + race);

        raceRepository.save(race);
        Optional<Race> added = raceRepository.getRaceByName(race.getName());

        if (added.isEmpty())
            return null;
        return added.get();
    }

    @CrossOrigin(origins = "http://localhost:5623")
    @RequestMapping(value = "/{id}", method = RequestMethod.PUT)
    public ResponseEntity<?> update(@PathVariable String id, @RequestBody Race race) {
        System.out.println("Updating race " + id);

        raceRepository.update(race);
        return new ResponseEntity<>(race, HttpStatus.OK);
    }

    @CrossOrigin(origins = "http://localhost:5623")
    @RequestMapping(value = "/{id}", method = RequestMethod.DELETE)
    public ResponseEntity<?> delete(@PathVariable String id) {
        raceRepository.delete(Long.parseLong(id));
        return new ResponseEntity<Race>(HttpStatus.OK);
    }

    @ExceptionHandler(Exception.class)
    @ResponseStatus(HttpStatus.BAD_REQUEST)
    public String raceError(Exception ex) {

        return ex.getMessage();
    }
}
