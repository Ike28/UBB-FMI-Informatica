#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <iostream>
#include <fstream>
#include <chrono>

#define N 1000
#define M 1000
#define n 3
#define m 3
#define lineOffset 1
#define columnOffset 1

using namespace std;
int kernel[3][3], initialMatrix[N][M], finalMatrix[N][M];

int check_matrices(string pathRight, string pathActual) {
    ifstream finRight(pathRight);
    ifstream finActual(pathActual);
    int x, y;
    while (finRight >> x && finActual >> y) {
        if (x != y) {
            return 0;
        }
    }

    if (finRight >> x || finActual >> x) {
        return 0;
    }
    return 1;
}
int convolution(int x, int y) {
    int sus, jos, stanga, dreapta;

    if (x == 0)sus = 0;
    else sus = x - 1;

    if (x == N - 1)jos = N - 1;
    else jos = x + 1;

    if (y == 0) stanga = 0;
    else stanga = y - 1;

    if (y == M - 1) dreapta = M - 1;
    else dreapta = y + 1;

    return kernel[0][0] * initialMatrix[sus][stanga] + kernel[0][1] * initialMatrix[sus][y] + kernel[0][2] * initialMatrix[sus][dreapta] +
        kernel[1][0] * initialMatrix[x][stanga] + kernel[1][1] * initialMatrix[x][y] + kernel[1][2] * initialMatrix[x][dreapta] +
        kernel[2][0] * initialMatrix[jos][stanga] + kernel[2][1] * initialMatrix[jos][y] + kernel[2][2] * initialMatrix[jos][dreapta];
}

int main()
{
    MPI_Status status;

    MPI_Init(NULL, NULL);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int intreg = N / (world_size - 1);
    int rest = N % (world_size - 1);
    int start = 0, end;

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    //MASTER

    if (world_rank == 0) {

        auto t1_start = chrono::high_resolution_clock::now();

        string fileIN = "D:\\_Facultate\\D7_Programare paralela si distribuita\\lab_03\\in.txt";
        string kernelFile = "D:\\_Facultate\\D7_Programare paralela si distribuita\\lab_03\\kernel.txt";
        ifstream file(fileIN);
        ifstream kernelF(kernelFile);

        if (kernelF.is_open()) {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    kernelF >> kernel[i][j];

            MPI_Bcast(&kernel, 9, MPI_INT, 0, MPI_COMM_WORLD);

            auto t2_start = chrono::high_resolution_clock::now();
            for (int i = 1; i < world_size; i++) {
                end = start + intreg;
                if (rest > 0) {
                    rest--;
                    end++;
                }

                // Se trimite intervalul de linii catre fiecare proces
                MPI_Send(&start, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
                MPI_Send(&end, 1, MPI_INT, i, 0, MPI_COMM_WORLD);

                // se citeste initialMatrix & se trimit bucatile de matrice la fiecare proces
                for (int x = start; x < end; x++)
                {
                    for (int y = 0; y < M; y++)
                        file >> initialMatrix[x][y];
                    MPI_Send(&initialMatrix[x], M, MPI_INT, i, 0, MPI_COMM_WORLD);
                }
                start = end;
            }

            file.close();

            auto t2_end = chrono::high_resolution_clock::now();
            double elapsed_time_ms_2 = chrono::duration<double, std::nano>(t2_end - t2_start).count();
            cout << "T2 (calcul) = " << elapsed_time_ms_2 << endl;
        }
        else cerr << "Reading ERROR!" + fileIN + "\n";

        ofstream outputFile("D:\\_Facultate\\D7_Programare paralela si distribuita\\lab_03\\output.txt");
        if (outputFile.is_open()) {

            for (int i = 1; i < world_size; i++) {
                MPI_Recv(&start, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
                MPI_Recv(&end, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
                for (int a = start; a < end; a++) {
                    MPI_Recv(&finalMatrix[a], M, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
                    for (int b = 0; b < M; b++) {
                        outputFile << finalMatrix[a][b] << " ";
                    }
                    outputFile << endl;
                }
            }
            outputFile.close();
        }

        auto t1_end = chrono::high_resolution_clock::now();
        double elapsed_time_ms_1 = chrono::duration<double, std::nano>(t1_end - t1_start).count();
        std::cout << "T1 (citire + scriere) = " << elapsed_time_ms_1 << endl;

        //verific corectitudinea cu laboratorul trecut
        string pathRight = "D:\\_Facultate\\D7_Programare paralela si distribuita\\lab_03\\outputCorect.txt";
        string pathActual = "D:\\_Facultate\\D7_Programare paralela si distribuita\\lab_03\\output.txt";
        int ok = check_matrices(pathRight, pathActual);
        if (ok == 0) std::cout << "Rezultatele nu corespund!" << endl;
        else std::cout << "Rezultatele corespund!" << endl;

    }

    //WORKER

    else {

        MPI_Bcast(&kernel, 9, MPI_INT, 0, MPI_COMM_WORLD);

        // se primeste intervalul de linii de procesat de la procesul MASTER
        MPI_Recv(&start, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&end, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        for (int a = start; a < end; a++)
            MPI_Recv(&initialMatrix[a], M, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        if (world_rank > 1)
            MPI_Send(&initialMatrix[start], M, MPI_INT, world_rank - 1, 0, MPI_COMM_WORLD);
        if (world_rank < world_size - 1)
            MPI_Send(&initialMatrix[end - 1], M, MPI_INT, world_rank + 1, 0, MPI_COMM_WORLD);

        if (world_rank > 1)
            MPI_Recv(&initialMatrix[start - 1], M, MPI_INT, world_rank - 1, 0, MPI_COMM_WORLD, &status);
        if (world_rank < world_size - 1)
            MPI_Recv(&initialMatrix[end], M, MPI_INT, world_rank + 1, 0, MPI_COMM_WORLD, &status);

        // calculez convolutia pentru liniile transmise
        for (int a = start; a < end; a++)
            for (int b = 0; b < M; b++)
                finalMatrix[a][b] = convolution(a, b);

        MPI_Send(&start, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Send(&end, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

        for (int a = start; a < end; a++)
            MPI_Send(&finalMatrix[a], M, MPI_INT, 0, 0, MPI_COMM_WORLD);

    }
    MPI_Finalize();

}