import java.io.*;
import java.util.Scanner;

public class Main {
    private static int N, M, n, m, p, borderLine, borderColumn;
    // borderLine, borderColumn -> the number of elements that will be present on the border (out of bounds)
    // of the matrix for each line or column

    private static int[][] mat, kernel, result;

    private static final String inputFilePath = "D:\\_Facultate\\D7_Programare paralela si distribuita\\lab-01_java\\input4.txt";
    private static final String outputFilePath = "D:\\_Facultate\\D7_Programare paralela si distribuita\\lab-01_java\\output.txt";
    private static final String expectedFilePath = "D:\\_Facultate\\D7_Programare paralela si distribuita\\lab-01_java\\expected4.txt";

    public static void main(String[] args) {
        //Utils.generate("input4.txt", 10000, 10, 5, 5);

        readFromFile(inputFilePath);
        p = Integer.parseInt(args[0]);

        if (p == 1) {
            sequential();
        } else {
            parallelIntervals();
        }

        if (checkCorrectness()) {
            writeToFile(outputFilePath);
        } else {
            System.out.println("INCORRECT RESULT!");
        }

        //printResultMatrix();
    }

    private static int calculateValue(int line, int column) {
        int value = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int x = line + i - borderLine;
                int y = column + j - borderColumn;

                if (x < 0) {
                    x = 0;
                } else if (x >= N) {
                    x = N - 1;
                }

                if (y < 0) {
                    y = 0;
                } else if (y >= M) {
                    y = M - 1;
                }

                value += kernel[i][j] * mat[x][y];
            }
        }

        return value;
    }

    private static void sequential() {
        long startTime = System.nanoTime();

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                result[i][j] = calculateValue(i, j);
            }
        }

        long endTime = System.nanoTime();
        System.out.print((double)(endTime - startTime) / 1E6);
    }

    private static void parallelIntervals() {
        Thread[] threads = new Thread[p];

        int size, rest;
        if (N > M) {
            size = N / p;
            rest = N % p;
        } else {
            size = M / p;
            rest = M % p;
        }

        int start;
        int end = 0;

        long startTime = System.nanoTime();

        for (int i = 0; i < p; i++) {
            start = end;
            end = start + size;

            if (rest > 0) {
                end++;
                rest--;
            }

            threads[i] = new MyThread(start, end);
            threads[i].start();
        }

        try {
            for (Thread t : threads) {
                t.join();
            }
        } catch (InterruptedException ex) {
            System.out.println("Execution error!");
            ex.printStackTrace();
        }

        long endTime = System.nanoTime();
        System.out.println((double)(endTime - startTime) / 1E6);
    }

    private static boolean checkCorrectness() {
        try {
            File file = new File(expectedFilePath);
            Scanner scanner = new Scanner(file);

            int[][] expected = new int[N][M];
            if (scanner.hasNextLine()) {
                for (int i = 0; i < N; i++) {
                    String line = scanner.nextLine();
                    String[] numbers = line.split(" ");
                    for (int j = 0; j < M; j++) {
                        int num = Integer.parseInt(numbers[j]);
                        expected[i][j] = num;
                    }
                }
            }

            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    if (expected[i][j] != result[i][j]) {
                        return false;
                    }
                }
            }

            return true;
        } catch (FileNotFoundException ex) {
            ex.printStackTrace();
            return false;
        }
    }

    private static void printResultMatrix() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                System.out.print(result[i][j] + " ");
            }
            System.out.println();
        }
    }

    private static void readFromFile(String filePath) {
        try {
            File file = new File(filePath);
            Scanner scanner = new Scanner(file);

            if (scanner.hasNextLine()) {
                N = Integer.parseInt(scanner.nextLine());
            }

            if (scanner.hasNextLine()){
                M = Integer.parseInt(scanner.nextLine());
            }

            mat = new int[N][M];
            if (scanner.hasNextLine()) {
                for (int i = 0; i < N; i++) {
                    String line = scanner.nextLine();
                    String[] numbers = line.split(" ");
                    for (int j = 0; j < M; j++) {
                        int num = Integer.parseInt(numbers[j]);
                        mat[i][j] = num;
                    }
                }
            }

            if (scanner.hasNextLine()) {
                n = Integer.parseInt(scanner.nextLine());
            }

            if (scanner.hasNextLine()){
                m = Integer.parseInt(scanner.nextLine());
            }

            kernel = new int[n][m];
            if (scanner.hasNextLine()) {
                for (int i = 0; i < n; i++) {
                    String line = scanner.nextLine();
                    String[] numbers = line.split(" ");
                    for (int j = 0; j < m; j++) {
                        int num = Integer.parseInt(numbers[j]);
                        kernel[i][j] = num;
                    }
                }
            }

            result = new int[N][M];
            borderLine = (n - 1) / 2;
            borderColumn = (m - 1) / 2;

        } catch (FileNotFoundException ex) {
            ex.printStackTrace();
        }
    }

    private static void writeToFile(String filePath) {
        try {
            FileWriter fileWriter = new FileWriter(filePath);
            BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);

            for (int[] line : result) {
                for (int elem : line) {
                    bufferedWriter.write(elem + " ");
                }
                bufferedWriter.newLine();
            }

            bufferedWriter.flush();
            bufferedWriter.close();

        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private static class MyThread extends Thread {

        int start, end;

        public MyThread(int start, int end) {
            this.start = start;
            this.end = end;
        }

        public void run() {
            if (N > M) {
                for (int i = start; i < end; i++) {
                    for (int j = 0; j < M; j++) {
                        result[i][j] = calculateValue(i, j);
                    }
                }
            } else {
                for (int i = 0; i < N; i++) {
                    for (int j = start; j < end; j++) {
                        result[i][j] = calculateValue(i, j);
                    }
                }
            }
        }
    }
}
