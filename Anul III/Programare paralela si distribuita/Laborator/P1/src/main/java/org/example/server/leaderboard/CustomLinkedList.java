package org.example.server.leaderboard;

import lombok.val;
import org.example.server.model.Player;

import java.util.*;
import java.util.concurrent.locks.ReentrantLock;
import java.util.function.Consumer;

public class CustomLinkedList implements Iterable<Player> {
    private final Node head;
    private final Node tail;

    private class PlayerIterator implements Iterator<Player> {
        private Node current = head.next;
        private Node lastAccessed = null;

        @Override
        public boolean hasNext() {
            synchronized (this) {
                return current.next != tail;
            }
        }

        @Override
        public Player next() {
            synchronized (this) {
                if (!hasNext()) {
                    throw new NoSuchElementException();
                }
                if (lastAccessed != null) {
                    lastAccessed.unlock(); // Unlock the last accessed node
                }
                current = current.next; // Move to the next node
                lastAccessed = current;  // Update the last accessed node
                current.lock();         // Lock the current node
                return current.player;
            }
        }
    }

    public CustomLinkedList() {
        head = new Node(null);
        tail = new Node(null);
        head.next = tail;
    }

    @Override
    public Iterator<Player> iterator() {
        return new PlayerIterator();
    }

    @Override
    public void forEach(Consumer<? super Player> action) {
        Iterable.super.forEach(action);
    }

    @Override
    public Spliterator<Player> spliterator() {
        return Iterable.super.spliterator();
    }

    private static class Node {
        Player player;
        Node next;
        ReentrantLock lock = new ReentrantLock();

        public Node(Player player) {
            this.player = player;
            this.next = null;
        }

        public void lock() {
            lock.lock();
        }

        public void unlock() {
            lock.unlock();
        }
    }

    public void insert(Player player) {
        var prev = head;
        prev.lock();

        try {
            var current = prev.next;
            current.lock();

            try {
                while (current != tail && !current.player.getId().equals(player.getId())) {
                    prev.unlock();
                    prev = current;
                    current = current.next;
                    current.lock();
                }

                if (current != tail) {
                    current.player.addScore(player.getScore());
                } else {
                    val newNode = new Node(player);
                    newNode.next = tail;
                    prev.next = newNode;
                }
            } finally {
                current.unlock();
            }
        } finally {
            prev.unlock();
        }
    }

    public Player remove(String playerName) {
        var prev = head;
        prev.lock();
        try {
            var current = prev.next;
            current.lock();
            try {
                while (current != tail && !current.player.getId().equals(playerName)) {
                    prev.unlock();
                    prev = current;
                    current = current.next;
                    current.lock();
                }
                if (current == tail) {
                    return null;
                }

                val removedPlayer = current.player;
                prev.next = current.next;
                return removedPlayer;
            } finally {
                current.unlock();
            }
        } finally {
            prev.unlock();
        }
    }

    public List<Player> copyToList() {
        val playersCopy = new ArrayList<Player>();
        var current = head;

        // Lock the head to ensure consistency during the copy
        current.lock();
        try {
            while (current.next != tail) {
                current = current.next;
                current.lock(); // Lock each node during the iteration
                try {
                    playersCopy.add(current.player);
                } finally {
                    current.unlock(); // Unlock each node after processing
                }
            }
        } finally {
            head.unlock(); // Unlock the head after the copy is complete
        }
        return playersCopy;
    }
}
