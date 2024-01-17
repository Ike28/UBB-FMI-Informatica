package org.example;

import java.util.Queue;
import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicInteger;

public class WorkerThread implements Runnable {
    private Queue<Main.Entry> queue;
    private MyLinkedList linkedList;
    private Semaphore queueSemaphore;
    private Semaphore listSemaphore;
    private volatile AtomicInteger nr_jobs;

    public WorkerThread(Queue<Main.Entry> queue, MyLinkedList linkedList, Semaphore queueSemaphore, Semaphore listSemaphore, AtomicInteger nr_jobs) {
        this.queue = queue;
        this.linkedList = linkedList;
        this.queueSemaphore = queueSemaphore;
        this.listSemaphore = listSemaphore;
        this.nr_jobs = nr_jobs;
    }

    @Override
    public void run(){
        while(nr_jobs.get() != 0 || !queue.isEmpty()){
            Main.Entry entry;
            try {
                queueSemaphore.acquire();
                if(!queue.isEmpty())
                    entry = queue.remove();
                else {
                    queueSemaphore.release();
                    continue;
                }
                queueSemaphore.release();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
            if(entry.punctaj == -1){
                try {
                    listSemaphore.acquire();
                    linkedList.remove(entry.ID);
                    listSemaphore.release();
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
            else {
                try {
                    listSemaphore.acquire();
                    linkedList.insert(entry.ID, entry.punctaj);
                    listSemaphore.release();
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
        }
    }

}
