package org.example.server.consumer;

import lombok.val;
import org.example.server.leaderboard.CustomLinkedList;
import org.example.server.leaderboard.CustomQueue;
import org.example.server.leaderboard.LeaderboardsHelper;
import org.example.server.model.Player;

import java.util.Set;
import java.util.concurrent.atomic.AtomicInteger;

import static java.lang.Integer.parseInt;

public class ConsumerThread extends Thread {
    private final CustomLinkedList players;
    private final Set<String> bannedIds;
    private final CustomQueue playerQueue;
    private final AtomicInteger connections;
    private final LeaderboardsHelper leaderboardsHelper;

    public ConsumerThread(CustomLinkedList players,
                          Set<String> bannedIds,
                          CustomQueue playerQueue,
                          AtomicInteger connections,
                          LeaderboardsHelper leaderboardsHelper) {
        this.players = players;
        this.bannedIds = bannedIds;
        this.playerQueue = playerQueue;
        this.connections = connections;
        this.leaderboardsHelper = leaderboardsHelper;
    }

    @Override
    public void run() {
        try {
            while (connections.get() > 0 || !playerQueue.isQueueEmpty()) {
                try {
                    Thread.sleep(50);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }

                if (!playerQueue.isQueueEmpty()) {
                    val data = playerQueue.consume();
                    val dataList = data.split(" ");
                    val participant = dataList[0];
                    val points = parseInt(dataList[1]);
                    val country = dataList[2];
                    val player = new Player(participant, points, country);

                    synchronized (bannedIds) {
                        if (!bannedIds.contains(player.getId())) {
                            if (player.getScore() == -1) {
                                bannedIds.add(player.getId());
                                players.remove(player.getId());
                            } else {
                                players.insert(player);
                            }
                        }
                    }
                }
            }

            playerQueue.decrementWriter();
            if (playerQueue.getWritersCounter() == 0) {
                leaderboardsHelper.writePlayerLeaderboardToFile();
                leaderboardsHelper.writeCountryLeaderboardToFile();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
