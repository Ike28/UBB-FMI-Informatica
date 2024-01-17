#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <cstring>

using namespace std;


int N, M, n, m, p, borderLine, borderColumn;
int mat[10005][10005], kernel[10005][10005], result[10005][10005], expected[10005][10005];

int calculateValue(int line, int column) {
	int value = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int x = line + i - borderLine;
			int y = column + j - borderColumn;

			if (x < 0) {
				x = 0;
			}
			else if (x >= N) {
				x = N - 1;
			}

			if (y < 0) {
				y = 0;
			}
			else if (y >= M) {
				y = M - 1;
			}

			value += kernel[i][j] * mat[x][y];
		}
	}

	return value;
}

void sequential() {
	auto startTime = chrono::high_resolution_clock::now();

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			result[i][j] = calculateValue(i, j);
		}
	}

	auto endTime = chrono::high_resolution_clock::now();
	cout << chrono::duration<double, milli>(endTime - startTime).count();
}

void addThread(int start, int end) {
	if (N > M) {
		for (int i = start; i < end; i++) {
			for (int j = 0; j < M; j++) {
				result[i][j] = calculateValue(i, j);
			}
		}
	}
	else {
		for (int i = 0; i < N; i++) {
			for (int j = start; j < end; j++) {
				result[i][j] = calculateValue(i, j);
			}
		}
	}
}

void parallelIntervals() {
	thread threads[17];

	int size, rest;
	if (N > M) {
		size = N / p;
		rest = N % p;
	}
	else {
		size = M / p;
		rest = M % p;
	}

	int start;
	int end = 0;

	auto startTime = chrono::high_resolution_clock::now();

	for (int i = 0; i < p; i++) {
		start = end;
		end = start + size;

		if (rest > 0) {
			end++;
			rest--;
		}

		threads[i] = thread(addThread, start, end);
	}

	for (int i = 0; i < p; i++) {
		threads[i].join();
	}

	auto endTime = chrono::high_resolution_clock::now();
	cout << chrono::duration<double, milli>(endTime - startTime).count();
}

void readFromFile() {
	string inputFilePath = "E:\\__Teme\\Programare Paralela si Distribuita (PPD)\\Lab1\\input4.txt";
	ifstream in(inputFilePath);

	in >> N;
	in >> M;
	//mat.resize(N, vector<int>(M));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			in >> mat[i][j];
		}
	}

	in >> n;
	in >> m;
	//kernel.resize(n, vector<int>(m));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			in >> kernel[i][j];
		}
	}

	in.close();

	//result.resize(N, vector<int>(M));
	borderLine = (n - 1) / 2;
	borderColumn = (m - 1) / 2;
}

void writeToFile() {
	string outputFilePath = "E:\\__Teme\\Programare Paralela si Distribuita (PPD)\\Lab1\\output.txt";
	ofstream out(outputFilePath);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			out << result[i][j] << " ";
		}
		out << "\n";
	}

	out.close();
}

bool checkCorrectness() {
	string expectedFilePath = "E:\\__Teme\\Programare Paralela si Distribuita (PPD)\\Lab1\\expected4.txt";
	ifstream in(expectedFilePath);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			in >> expected[i][j];
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
}


int main(int argc, char** argv) {
	srand(time(NULL));

	p = atoi(argv[1]);
	readFromFile();

	if (p == 1) {
		sequential();
	}
	else {
		parallelIntervals();
	}

	if (checkCorrectness()) {
		writeToFile();
	}
	else {
		cout << "INCORRECT RESULT!";
	}

	return 0;
}