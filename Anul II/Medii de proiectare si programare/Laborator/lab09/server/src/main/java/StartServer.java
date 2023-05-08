import com.ubb.IContestServices;
import com.ubb.ContestServices;
import com.ubb.exceptions.ServerException;
import com.ubb.repository.*;
import com.ubb.repository.hibernate.ParticipantORMRepository;
import com.ubb.repository.jdbc.*;
import com.ubb.server.ContestConcurrentServer;
import com.ubb.server.Server;
import com.ubb.service.*;
import org.hibernate.SessionFactory;
import org.hibernate.boot.MetadataSources;
import org.hibernate.boot.registry.StandardServiceRegistry;
import org.hibernate.boot.registry.StandardServiceRegistryBuilder;

import java.io.IOException;
import java.util.Properties;

public class StartServer {
    private static final int DEFAULT_PORT = 25564;

    public static void main(String[] args) {
        Properties serverProperties = new Properties();
        try {
            serverProperties.load(StartServer.class.getResourceAsStream("/server.properties"));
            System.out.println("Server properties set.");
            serverProperties.list(System.out);
        } catch (IOException ioException) {
            System.out.println("Cannot find server.properties.");
            return;
        }

        IContestServices raceServices = initializeServices(serverProperties);
        int serverPort = DEFAULT_PORT;

        try {
            serverPort = Integer.parseInt(serverProperties.getProperty("server.port"));
        } catch (NumberFormatException numberFormatException) {
            System.out.println("Wrong port number: " + numberFormatException.getMessage());
            System.out.println("Using default port " + DEFAULT_PORT);
        }
        System.out.println("Starting server on port:" + serverPort);

        Server server = new ContestConcurrentServer(serverPort, raceServices);
        try {
            server.start();
        } catch (ServerException serverException) {
            System.out.println("Error starting the server: " + serverException.getMessage());
        }
    }

    private static IContestServices initializeServices(Properties serverProperties) {
        final StandardServiceRegistry registry = new StandardServiceRegistryBuilder()
                .configure()
                .build();
        final SessionFactory sessionFactory = new MetadataSources(registry)
                .buildMetadata()
                .buildSessionFactory();
        IParticipantRepository participantRepository = new ParticipantORMRepository(sessionFactory);
        IRaceRepository raceRepository = new RaceDBRepository(serverProperties);
        IRaceEntryRepository raceEntryRepository = new RaceEntryDBRepository(serverProperties, raceRepository, participantRepository);
        IUserRepository userRepository = new UserDBRepository(serverProperties);
        ITeamRepository teamRepository = new TeamDBRepository(serverProperties);

        IUserService userService = new UserService(userRepository);
        IParticipantService participantService = new ParticipantService(participantRepository);
        IRaceService raceService = new RaceService(raceRepository, raceEntryRepository);
        ITeamService teamService = new TeamService(teamRepository);

        return new ContestServices(userService, participantService, raceService, teamService);
    }
}
