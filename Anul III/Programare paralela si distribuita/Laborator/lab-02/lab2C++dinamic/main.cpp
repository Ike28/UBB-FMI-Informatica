#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <vector>
#include <barrier>

using std::cout;
using std::string;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::thread;
using std::barrier;

string pathIN = "D:/_Facultate/D7_Programare paralela si distribuita/lab2-tema/lab2Java/lab2Java/src/main/java/org/example/in.txt";
string pathKernel = "D:/_Facultate/D7_Programare paralela si distribuita/lab2-tema/lab2Java/lab2Java/src/main/java/org/example/kernel.txt";
string pathOutSecvential = "D:/_Facultate/D7_Programare paralela si distribuita/lab2-tema/lab2Java/lab2Java/src/main/java/org/example/outSecvential.txt";
string pathOutParalel = "D:/_Facultate/D7_Programare paralela si distribuita/lab2-tema/lab2Java/lab2Java/src/main/java/org/example/outParalel.txt";

const int N = 10, M = 10, n = 3, m = 3, p = 2;
barrier<> bariera = barrier(p);

bool equalResults(string fname1, string fname2) {

    int x, y;
    ifstream fd1(fname1), fd2(fname2);

    while (fd1 >> x && fd2 >> y)
        if (x != y)
            return false;

    fd1.close();
    fd2.close();
    return true;
}

int convolutie(int i, int j, int** initialMatrix,  int** kernel) {
    int result = 0;
    for (int l = 0; l < n; l++) {
        for (int k = 0; k < m; k++) {
            result = result + kernel[l][k] * initialMatrix[i + (l - 1)][j + (k - 1)];
        }
    }
    return result;
}

void secvential(int** initialMatrix, int** kernel) {
    ofstream fout(pathOutSecvential);
    int aux[N * M], k = 0;
    for (int i = 2; i < N + 2; i++) {
        for (int j = 2; j < M + 2; j++) {
            aux[k++] = convolutie(i, j, initialMatrix, kernel);
        }
    }

    k = 0;
    for (int i = 2; i < N + 2; i++) {
        for (int j = 2; j < M + 2; j++) {
            initialMatrix[i][j] = aux[k++];
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            fout << initialMatrix[i][j] << ' ';
        }
        fout << '\n';
    }
    fout.close();
}

void run(int end, int start, int** initialMatrix, int** kernel) {
    int aux[N * M], k = 0;
    for (int pos = start; pos < N * M; pos = pos + end) {
        int i = pos / M, j = pos % M;
        aux[k++] = convolutie(i + 2, j + 2, initialMatrix, kernel);
    }

    bariera.arrive_and_wait();
    k = 0;
    for (int pos = start; pos < N * M; pos = pos + end) {
        int i = pos / M, j = pos % M;
        initialMatrix[i][j] = aux[k++];
    }
}

void paralel(int** initialMatrix,  int** kernel) {
    // declaram un array de threaduri
    vector<thread> threads(p);

    // cream threadurile
    for (int i = 0; i < p; i++) {
        threads[i] = thread(run, p, i, initialMatrix, kernel);
    }

    // join threads
    for (int i = 0; i < p; i++) {
        threads[i].join();
    }

    ofstream fout(pathOutParalel);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            fout << initialMatrix[i][j] << ' ';
        fout << '\n';
    }
    fout.close();
}
int main() {

    int** initialMatrix, ** kernel;
    initialMatrix = new int* [N + 4];
    for (int i = 0; i < N + 4; i++)
        initialMatrix[i] = new int[M + 4];

    kernel = new int* [n];
    for (int i = 0; i < n; i++)
        kernel[i] = new int[m];


    // citire date din fisiere
    ifstream fii(pathIN);
    for (int i = 2; i < N + 2; i++)
        for (int j = 2; j < M + 2; j++)
            fii >> initialMatrix[i][j];
    fii.close();

    ifstream ff(pathKernel);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            ff >> kernel[i][j];
    ff.close();

    // bordare matrice initiala
    // colturi
    initialMatrix[0][0] = initialMatrix[0][1] = initialMatrix[1][0] = initialMatrix[1][1] = initialMatrix[2][2];
    initialMatrix[N + 3][1] = initialMatrix[N + 2][1] = initialMatrix[N + 3][0] = initialMatrix[N + 2][0] = initialMatrix[N + 1][2];
    initialMatrix[0][M + 3] = initialMatrix[0][M + 2] = initialMatrix[1][M + 3] = initialMatrix[1][M + 2] = initialMatrix[2][M + 1];
    initialMatrix[N + 3][M + 3] = initialMatrix[N + 3][M + 2] = initialMatrix[N + 2][M + 3] = initialMatrix[N + 2][M + 2] = initialMatrix[N + 1][M + 1];
    // bordare coloane
    for (int i = 2; i < N + 2; i++) {
        initialMatrix[i][0] = initialMatrix[i][1] = initialMatrix[i][2];
        initialMatrix[i][M + 2] = initialMatrix[i][M + 3] = initialMatrix[i][M + 1];
    }
    // bordare linii
    for (int j = 2; j < M + 2; j++) {
        initialMatrix[0][j] = initialMatrix[1][j] = initialMatrix[2][j];
        initialMatrix[N + 2][j] = initialMatrix[N + 3][j] = initialMatrix[N + 1][j];
    }

    // masurare timp
    auto startTime = std::chrono::high_resolution_clock::now();
    //secvential(initialMatrix, kernel);
    paralel(initialMatrix, kernel);
    auto endTime = std::chrono::high_resolution_clock::now();
    cout << '\n' << std::chrono::duration<double, std::milli>(endTime - startTime).count() << '\n';

    // afisare date
    /*for (int i = 0; i < N + 4; i++) {
        for (int j = 0; j < M + 4; j++)
            cout << initialMatrix[i][j] << ' ';
        cout << '\n';
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << kernel[i][j] << ' ';
        cout << '\n';
    }*/
}