package com.ubb;

import com.ubb.model.Participant;
import com.ubb.repository.*;

import java.io.FileReader;
import java.io.IOException;
import java.util.Properties;

public class Main {
    public static void main(String[] args) {
        final Properties properties = new Properties();
        try {
            properties.load(new FileReader("bd.properties"));
            IParticipantRepository participantDBRepository = new ParticipantDBRepository(properties);
            participantDBRepository.save(new Participant("Tim", "Gajser", 1200));
            for (Participant p : participantDBRepository.findAll()) {
                System.out.println(p);
            }
        } catch (IOException ioException) {
            System.out.println("Cannot find bd.properties " + ioException.getMessage());
        }
    }
}
