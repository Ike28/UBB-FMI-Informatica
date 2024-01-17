package org.example;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;
import java.util.LinkedList;
import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicInteger;

public class Main {
    public static Semaphore queueSemaphore = new Semaphore(1);
    public static Semaphore listSemaphore = new Semaphore(1);
    private static volatile AtomicInteger nr_jobs = new AtomicInteger(2);
    static class Entry {
        int ID;
        int punctaj;

        Entry(int ID_n, int punctaj_n) {
            this.ID = ID_n;
            this.punctaj = punctaj_n;
        }

        @Override
        public String toString() {
            return "Entry{" +
                    "ID=" + ID +
                    ", punctaj=" + punctaj +
                    '}';
        }
    }

    public static void sequential(MyLinkedList linkedList, Queue<Entry> queue){
        for(int i = 1; i <= 5; ++i){
            for(int j = 1; j <= 10; ++j){
                String fileName = "D:\\_Facultate\\D7_Programare paralela si distribuita\\tema04\\Concurs\\RezultateC"
                        + i + "_P" + j + ".txt";
                try {
                    File myObj = new File(fileName);
                    Scanner myReader = new Scanner(myObj);
                    while (myReader.hasNextLine()) {
                        String data = myReader.nextLine();
                        String[] pair = data.split(",");
                        Main.Entry entry = new Main.Entry(Integer.parseInt(pair[0]), Integer.parseInt(pair[1]));
                        queue.add(entry);
                    }
                    myReader.close();
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                }
            }
        }

        while(!queue.isEmpty()){
            Entry entry = queue.remove();
            if(entry.punctaj == -1){
                linkedList.remove(entry.ID);
            }
            else {
                linkedList.insert(entry.ID, entry.punctaj);
            }
        }
        linkedList.print();
    }

    public static void parallel(MyLinkedList linkedList, Queue<Entry> queue, int p, AtomicInteger nr_jobs) throws InterruptedException {
        Thread[] workerThreads = new Thread[p];
        Thread readerThread = new Thread (new ReaderThread(0, 50, queue, queueSemaphore, nr_jobs));
        readerThread.start();

        for (int i = 0; i < p; ++i) {
            Thread workerThread = new Thread(new WorkerThread(queue, linkedList, queueSemaphore, listSemaphore, nr_jobs));
            workerThreads[i] = workerThread;
            workerThread.start();
        }

        readerThread.join();
        for (int i = 0; i < p; ++i){
            workerThreads[i].join();
        }
        linkedList.print();
    }

    public static void parallel2(MyLinkedList linkedList, Queue<Entry> queue, int p, AtomicInteger nr_jobs) throws InterruptedException {
        Thread readerThread1 = new Thread (new ReaderThread(0, 25, queue, queueSemaphore, nr_jobs));
        Thread readerThread2 = new Thread (new ReaderThread(25, 50, queue, queueSemaphore, nr_jobs));
        readerThread1.start();
        readerThread2.start();

        Thread[] workerThreads = new Thread[p];
        for (int i = 0; i < p; ++i) {
            Thread workerThread = new Thread(new WorkerThread(queue, linkedList, queueSemaphore, listSemaphore, nr_jobs));
            workerThreads[i] = workerThread;
            workerThread.start();
        }

        readerThread1.join();
        readerThread2.join();
        for (int i = 0; i < p; ++i){
            workerThreads[i].join();
        }
        linkedList.print();
    }

    public static void main(String[] args) throws InterruptedException {
        Queue<Entry> queue = new LinkedList<>();
        MyLinkedList linkedList = new MyLinkedList();
        int p = 2;
        p = Integer.parseInt(args[0]);

        if (p == 1) {
            long startTime = System.nanoTime();
            sequential(linkedList, queue);
            System.out.println((double) (System.nanoTime() - startTime) / 1E6);
        }else {
            long startTime = System.nanoTime();
            parallel2(linkedList, queue, p, nr_jobs);
            System.out.println((double) (System.nanoTime() - startTime) / 1E6);
        }
    }
}