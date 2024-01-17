package org.example;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;

public class Main {
    private static int N, M, n, m, p=2;
    private static int[][] initialMatrix;
    private static int[][] kernel;
    private static Utils utils = new Utils();
    private static CyclicBarrier barrier = new CyclicBarrier(p);

    /*
     * Cream un tip nou de threaduri care preiau pozitii din matrice
     * in functie de distributia ciclica
     * start - pozitia de inceput (din intervalul [0,p-1] = id thread)
     * step - un pas egal cu nr de threaduri
     */
    //p = 0 -> 0, 4, și 8 de ex
    //p = 1 ->  1 și 5
    //p = 2 -> 2 și 6
    //p = 3 -> 3, 7, și 9.
    public static class MyThread extends Thread{
        int step, start;

        public MyThread(int step, int start) {
            this.step = step;
            this.start = start;
        }

        /*
         * Functia run descrie comportamentul tipului nou de threaduri
         * Fiecare thread preia un numar de elemente din matrice pentru prelucrare
         * Preluarea se face prin distributie ciclica
         */
        public void run(){
            List<Integer> aux = new ArrayList<>();
            for(int pos = this.start; pos < N*M; pos = pos + this.step){
                int i = pos/M, j = pos%M;
                aux.add(convolutie(i+2,j+2));
            }

            try{
                barrier.await();
            } catch(InterruptedException | BrokenBarrierException e){
                e.printStackTrace();
            }

            int k = 0;
            for(int pos = this.start; pos < N*M; pos = pos + this.step){
                int i = pos/M, j = pos%M;
                initialMatrix[i+2][j+2] = aux.get(k);
                k++;
            }

        }

    }

    private static void paralel() throws InterruptedException, IOException {
        // cream un array de p threaduri si il initializam
        Thread[] threads = new MyThread[p];
        for(int i=0; i<p; i++){
            threads[i] = new MyThread(p,i);
        }

        // start threads
        for(int i=0; i<p ;i++) {
            threads[i].start();
        }

        // join threads
        for(int i=0; i<p; i++) {
            threads[i].join();
        }

        // afisare rezultat
        FileWriter writer = new FileWriter("D:\\_Facultate\\D7_Programare paralela si distribuita\\lab2-tema\\lab2Java\\lab2Java\\src\\main\\java\\org\\example\\outParalel.txt");
        for(int i = 0; i < N; i ++){
            for(int j = 0; j < M; j ++){
                writer.write(initialMatrix[i][j] + " ");
            }
            writer.write('\n');
        }
        writer.close();

    }


    /*
     * Calculul elementelor din imaginea rezultat prin operatia de convolutie
     */
    private static int convolutie(int i, int j){
        int result = 0;
        for (int l = 0; l < n; l++) {
            for (int k = 0; k < m; k++) {
                result = result + kernel[l][k] * initialMatrix[i+(l-1)][j+(k-1)];
            }
        }
        return result;
    }




    private static void secvential() throws IOException {
        FileWriter writer = new FileWriter("D:\\_Facultate\\D7_Programare paralela si distribuita\\lab2-tema\\lab2Java\\lab2Java\\src\\main\\java\\org\\example\\outSecvential.txt");
        List<Integer> aux = new ArrayList<>();
        for(int i = 2; i < N + 2; i ++) {
            for (int j = 2; j < M + 2; j++) {
                aux.add(convolutie(i, j));
            }
        }

        int k = 0;
        for(int i=2;i<N+2;i++){
            for(int j=2;j<M+2;j++){
                initialMatrix[i][j] = aux.get(k);
                k++;
            }
        }

        for(int i = 0; i < N; i ++){
            for(int j = 0; j < M; j ++){
                writer.write(initialMatrix[i][j] + " ");
            }
            writer.write('\n');
        }
        writer.close();
    }


    public static void main(String[] args) throws IOException, InterruptedException {
        N = 10; M = 10; n = 3; m = 3; p = 2;

        // initializare matrici
        initialMatrix = new int[N+5][M+5];
        kernel = new int[n][m];

        // Citire date din fisiere
        // citire imagine initiala
        File fisierImagineInitiala = new File("D:\\_Facultate\\D7_Programare paralela si distribuita\\lab2-tema\\lab2Java\\lab2Java\\src\\main\\java\\org\\example\\in.txt");
        Scanner fii  = new Scanner(fisierImagineInitiala);
        for (int i = 2; i < N+2; i++) {
            for(int j = 2; j < M+2; j++) {
                initialMatrix[i][j] = fii.nextInt();
            }
        }
        fii.close();
        //citire fereastra
        File fisierFereastra = new File("D:\\_Facultate\\D7_Programare paralela si distribuita\\lab2-tema\\lab2Java\\lab2Java\\src\\main\\java\\org\\example\\kernel.txt");
        Scanner ff = new Scanner(fisierFereastra);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                kernel[i][j] = ff.nextInt();
            }
        }
        ff.close();

        // Bordare matrice initiala
        // bordare colturi
        initialMatrix[0][0] = initialMatrix[0][1] = initialMatrix[1][0] = initialMatrix[1][1] = initialMatrix[2][2];
        initialMatrix[N+3][1] = initialMatrix[N+2][1] = initialMatrix[N+3][0] = initialMatrix[N+2][0] = initialMatrix[N+1][2];
        initialMatrix[0][M+3] = initialMatrix[0][M+2] = initialMatrix[1][M+3] = initialMatrix[1][M+2] = initialMatrix[2][M+1];
        initialMatrix[N+3][M+3] = initialMatrix[N+3][M+2] = initialMatrix[N+2][M+3] = initialMatrix[N+2][M+2] = initialMatrix[N+1][M+1];
        // bordare coloane
        for(int i = 2; i < N+2; i ++) {
            initialMatrix[i][0] = initialMatrix[i][1] = initialMatrix[i][2];
            initialMatrix[i][M+2] = initialMatrix[i][M+3] = initialMatrix[i][M+1];
        }
        // bordare linii
        for(int j = 2; j < M+2; j ++) {
            initialMatrix[0][j] = initialMatrix[1][j] = initialMatrix[2][j];
            initialMatrix[N+2][j] = initialMatrix[N+3][j] = initialMatrix[N+1][j];
        }

        // masurare timp
        long startTime = System.nanoTime();
        //secvential();
        paralel();
        long stopTime = System.nanoTime();
        //System.out.println("Timp:" + (double)(stopTime-startTime)); //nano
        System.out.println("Timp:" + (double)(stopTime-startTime)/1E6); //milli

        // afisare
//        for (int i = 0; i < N+4; i++) {
//            for (int j = 0; j < M+4; j++) {
//                System.out.print(initialImage[i][j] + " ");
//            }
//            System.out.print("\n");
//        }
//        for (int i = 0; i < n; i++) {
//            for (int j = 0; j < m; j++) {
//                System.out.print(window[i][j] + " ");
//            }
//            System.out.print("\n");
//        }

        if(utils.equalResults("D:\\_Facultate\\D7_Programare paralela si distribuita\\lab2-tema\\lab2Java\\lab2Java\\src\\main\\java\\org\\example\\outParalel.txt", "D:\\_Facultate\\D7_Programare paralela si distribuita\\lab2-tema\\lab2Java\\lab2Java\\src\\main\\java\\org\\example\\outSecvential.txt")){
            System.out.println("Rezultatele corespund");
        } else{
            System.out.println("Rezultatele NU corespund si nu e OK");
        }
    }
}
