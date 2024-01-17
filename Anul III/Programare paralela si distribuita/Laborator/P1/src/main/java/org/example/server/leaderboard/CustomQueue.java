package org.example.server.leaderboard;

import lombok.val;

import java.util.Queue;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class CustomQueue {
    private final Queue<String> queue = new java.util.LinkedList<>();
    private final int maxSize;
    private final AtomicInteger writersCounter;
    private final Lock lock = new ReentrantLock();
    private final Condition notFull = lock.newCondition();
    private final Condition notEmpty = lock.newCondition();

    public CustomQueue(int maxSize, int writersCounter) {
        this.maxSize = maxSize;
        this.writersCounter = new AtomicInteger(writersCounter);
    }

    public void produce(String message) throws InterruptedException {
        lock.lock();
        try {
            while(queue.size() >= maxSize) {
                notFull.await(); // Wait for the queue to not be full
            }
            queue.add(message);
            notEmpty.signalAll(); // Signal that the queue is not empty
        } finally {
            lock.unlock();
        }
    }

    public String consume() throws InterruptedException {
        lock.lock();
        try {
            while (queue.isEmpty()) {
                notEmpty.await(); // Signal that the queue is empty
            }

            val item = queue.poll();
            //System.out.println("Consumed: " + item);
            notFull.signalAll(); // Signal that the queue is not full
            return item;
        } finally {
            lock.unlock();
        }
    }

    public synchronized void decrementWriter() {
        writersCounter.decrementAndGet();
        notifyAll(); // Notify waiting producer that writer is decremented
    }
    public synchronized int getWritersCounter()
    {
        return writersCounter.get();
    }

    public synchronized boolean isQueueEmpty()
    {
        return queue.isEmpty();
    }
}
