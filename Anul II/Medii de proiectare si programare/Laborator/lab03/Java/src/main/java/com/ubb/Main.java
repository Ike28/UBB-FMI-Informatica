package com.ubb;

import com.ubb.model.Participant;
import com.ubb.repository.ParticipantDBRepository;

import java.io.FileReader;
import java.io.IOException;
import java.util.Collection;
import java.util.Properties;

public class Main {
    public static void main(String[] args) {
        final Properties properties = new Properties();
        try {
            properties.load(new FileReader("bd.properties"));
            ParticipantDBRepository participantDBRepository = new ParticipantDBRepository(properties);
            participantDBRepository.save(new Participant("Emil", "Zola", 600));
            Collection<Participant> participants = participantDBRepository.findAll();
            for (Participant p : participants) {
                System.out.println(p);
            }
        } catch (IOException ioException) {
            System.out.println("Cannot find bd.properties " + ioException.getMessage());
        }
    }
}
