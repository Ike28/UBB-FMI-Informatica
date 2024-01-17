package org.example;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Queue;
import java.util.Scanner;
import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicInteger;

public class ReaderThread implements Runnable {
    private volatile AtomicInteger nr_jobs;
    private int start, end;
    private Queue<Main.Entry> queue;
    private volatile Semaphore semaphore;

    public ReaderThread(int start, int end, Queue<Main.Entry> queue, Semaphore semaphore, AtomicInteger nr_jobs) {
        this.nr_jobs = nr_jobs;
        this.start = start;
        this.end = end - 1;
        this.queue = queue;
        this.semaphore = semaphore;
    }

    public synchronized void decrement() {
        nr_jobs.decrementAndGet();
    }

    @Override
    public void run() {
        int country = start / 10 + 1;
        int problem = start % 10 + 1;
        int countryFinal = end / 10 + 1;
        int problemFinal = end % 10 + 1;
        boolean started = false;

        for (int i = country; i <= countryFinal; ++i) {
            for (int j = 1; j <= 10; ++j) {
                if(!started){
                    started = true;
                    j = problem;
                }
                if (i == countryFinal && j > problemFinal) {
                    decrement();
                    return;
                }
                String fileName = "D:\\_Facultate\\D7_Programare paralela si distribuita\\tema04\\Concurs\\RezultateC"
                        + i + "_P" + j + ".txt";

                try {
                    File myObj = new File(fileName);
                    Scanner myReader = new Scanner(myObj);
                    while (myReader.hasNextLine()) {
                        String data = myReader.nextLine();
                        String[] pair = data.split(",");
                        Main.Entry entry = new Main.Entry(Integer.parseInt(pair[0]), Integer.parseInt(pair[1]));
                        try {
                            semaphore.acquire();
                            queue.add(entry);
                            semaphore.release();
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }
                    myReader.close();
                } catch (FileNotFoundException e) {
                    System.out.println("An FileNotFoundException occurred.");
                    e.printStackTrace();
                }
            }
        }

        decrement();
    }
}
