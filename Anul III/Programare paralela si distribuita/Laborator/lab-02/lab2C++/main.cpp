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

string pathII = R"(D:\_Facultate\D7_Programare paralela si distribuita\lab2-tema\lab2Java\lab2Java\src\main\java\org\example\imagineInitiala.txt)";
string pathW = R"(D:\_Facultate\D7_Programare paralela si distribuita\lab2-tema\lab2Java\lab2Java\src\main\java\org\example\fereastra.txt)";
string pathIFS = R"(D:\_Facultate\D7_Programare paralela si distribuita\lab2-tema\lab2Java\lab2Java\src\main\java\org\example\imagineFinalaSecvential.txt)";
string pathIFP = R"(D:\_Facultate\D7_Programare paralela si distribuita\lab2-tema\lab2Java\lab2Java\src\main\java\org\example\imagineFinalaParalel.txt)";

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

int convolutie(int i, int j, int** initialImage,  int** window) {
    int result = 0;
    for (int l = 0; l < n; l++) {
        for (int k = 0; k < m; k++) {
            result = result + window[l][k] * initialImage[i + (l - 1)][j + (k - 1)];
        }
    }
    return result;
}

void secvential(int** initialImage, int** window) {
    ofstream fout(pathIFS);
    int aux[N * M], k = 0;
    for (int i = 2; i < N + 2; i++) {
        for (int j = 2; j < M + 2; j++) {
            aux[k++] = convolutie(i, j, initialImage, window);
        }
    }

    k = 0;
    for (int i = 2; i < N + 2; i++) {
        for (int j = 2; j < M + 2; j++) {
            initialImage[i][j] = aux[k++];
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            fout << initialImage[i][j] << ' ';
        }
        fout << '\n';
    }
    fout.close();
}

void run(int step, int start, int** initialImage, int** window) {
    int aux[N * M], k = 0;
    for (int pos = start; pos < N * M; pos = pos + step) {
        int i = pos / M, j = pos % M;
        aux[k++] = convolutie(i + 2, j + 2, initialImage, window);
    }

    bariera.arrive_and_wait();
    k = 0;
    for (int pos = start; pos < N * M; pos = pos + step) {
        int i = pos / M, j = pos % M;
        initialImage[i][j] = aux[k++];
    }
}

void paralel(int** initialImage,  int** window) {
    // declaram un array de threaduri
    vector<thread> threads(p);

    // cream threadurile
    for (int i = 0; i < p; i++) {
        threads[i] = thread(run, p, i, initialImage, window);
    }

    // join threads
    for (int i = 0; i < p; i++) {
        threads[i].join();
    }

    ofstream fout(pathIFP);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            fout << initialImage[i][j] << ' ';
        fout << '\n';
    }
    fout.close();
}

int main() {

    int** initialImage, ** window;
    initialImage = new int* [N + 4];
    for (int i = 0; i < N + 4; i++)
        initialImage[i] = new int[M + 4];

    window = new int* [n];
    for (int i = 0; i < n; i++)
        window[i] = new int[m];


    // citire date din fisiere
    ifstream fii(pathII);
    for (int i = 2; i < N + 2; i++)
        for (int j = 2; j < M + 2; j++)
            fii >> initialImage[i][j];
    fii.close();

    ifstream ff(pathW);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            ff >> window[i][j];
    ff.close();

    // bordare matrice initiala
    // colturi
    initialImage[0][0] = initialImage[0][1] = initialImage[1][0] = initialImage[1][1] = initialImage[2][2];
    initialImage[N + 3][1] = initialImage[N + 2][1] = initialImage[N + 3][0] = initialImage[N + 2][0] = initialImage[N + 1][2];
    initialImage[0][M + 3] = initialImage[0][M + 2] = initialImage[1][M + 3] = initialImage[1][M + 2] = initialImage[2][M + 1];
    initialImage[N + 3][M + 3] = initialImage[N + 3][M + 2] = initialImage[N + 2][M + 3] = initialImage[N + 2][M + 2] = initialImage[N + 1][M + 1];
    // bordare coloane
    for (int i = 2; i < N + 2; i++) {
        initialImage[i][0] = initialImage[i][1] = initialImage[i][2];
        initialImage[i][M + 2] = initialImage[i][M + 3] = initialImage[i][M + 1];
    }
    // bordare linii
    for (int j = 2; j < M + 2; j++) {
        initialImage[0][j] = initialImage[1][j] = initialImage[2][j];
        initialImage[N + 2][j] = initialImage[N + 3][j] = initialImage[N + 1][j];
    }

    // masurare timp
    auto startTime = std::chrono::high_resolution_clock::now();
    //secvential(initialImage, window);
    paralel(initialImage, window);
    auto endTime = std::chrono::high_resolution_clock::now();
    cout << '\n' << std::chrono::duration<double, std::milli>(endTime - startTime).count() << '\n';

    if (equalResults(pathIFS, pathIFP))
        cout << "Rezultatele corespund" << '\n';
    else
        cout << "Rezultatele NU corespund si nu este OK" << '\n';


//    // afisare date
//    for (int i = 0; i < N + 4; i++) {
//        for (int j = 0; j < M + 4; j++)
//            cout << initialImage[i][j] << ' ';
//        cout << '\n';
//    }
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < m; j++)
//            cout << window[i][j] << ' ';
//        cout << '\n';
//    }
}