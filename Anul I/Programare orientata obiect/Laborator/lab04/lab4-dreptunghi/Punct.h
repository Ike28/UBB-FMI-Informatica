#pragma once
#include <ostream>
using namespace std;

class Punct {
private:
	int x, y;
public:
	Punct();
	Punct(int a, int b);
	Punct(const Punct& other);
	~Punct();

	int getX();
	void setX(int val);
	int getY();
	void setY(int val);
	int getCadran();

	friend ostream& operator<<(ostream& os, const Punct& other);
	Punct& operator=(const Punct& other);
};
