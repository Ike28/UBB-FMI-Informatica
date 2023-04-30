#include "utils.h"
#include "Component.h"
#include <vector>
#include <ctime>
#include <chrono>
#include <ratio>
using namespace std;

string generateCode()
{

	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, sizeof(buffer), "%d%H%M%S", timeinfo);
	string str(buffer);
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	chrono::duration<double, std::milli> time_span = t2 - t1;
	int tcount = (int)time_span.count();
	str += to_string(tcount);

	return str;
}


void load() {
	float progress = 0.0;

	while (progress < 1.01) {

		int barWidth = 70;
		int pos = barWidth * progress;

		Sleep(10);

		std::cout << "[";
		for (int i = 0; i < barWidth; i++) {
			if (i < pos) std::cout << "=";
			else if (i == pos) std::cout << ">";
			else std::cout << " ";
		}
		std::cout << "]" << int(progress * 100.0) << " %\r";
		std::cout.flush();

		progress += 0.01;
	}
	std::cout << std::endl;
}
