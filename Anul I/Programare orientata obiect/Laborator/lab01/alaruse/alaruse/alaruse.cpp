#include <iostream>
#include "subalg.h"
#include "tests.h"
#include <Windows.h>
#include <thread>
#include <future>

int main()
{

    int x, y;
    citireNumar(x, "Dati numar de inmultit: ");
    citireNumar(y, "Dati numarul cu care se inmulteste: ");
    afisareNumar(aLaRusse(x, y), "Rezultatul inmultirii este: ");
    return 0;
}

void load() {
	float progress = 0.0;

	while (progress < 1.0) {

		int barWidth = 70;
		int pos = barWidth * progress;

		Sleep(10);

		cout << "[";
		for (int i = 0; i < barWidth; i++) {
			if (i < pos) cout << char(219);
			else if (i == pos) cout << char(219);
			else cout << " ";
		}
		cout << "]" << int(progress * 100.0) << " %\r";
		cout.flush();

		progress += 0.01;
	}
	std::cout << std::endl;
}
