import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class Utils {

    public static void generate(String outputFileName, int N, int M, int n, int m) {
        try {
            FileWriter fileWriter = new FileWriter(outputFileName);
            BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);

            Random random = new Random();
            int[][] generatedMat = new int[N][M];
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    generatedMat[i][j] = random.nextInt(100);
                }
            }

            int[][] generatedKernel = new int[n][m];
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    generatedKernel[i][j] = random.nextInt(100);
                }
            }

            bufferedWriter.write(String.valueOf(N));
            bufferedWriter.newLine();
            bufferedWriter.write(String.valueOf(M));
            bufferedWriter.newLine();

            for (int[] line : generatedMat) {
                for (int elem : line) {
                    bufferedWriter.write(elem + " ");
                }
                bufferedWriter.newLine();
            }

            bufferedWriter.write(String.valueOf(n));
            bufferedWriter.newLine();
            bufferedWriter.write(String.valueOf(m));
            bufferedWriter.newLine();

            for (int[] line : generatedKernel) {
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
}
