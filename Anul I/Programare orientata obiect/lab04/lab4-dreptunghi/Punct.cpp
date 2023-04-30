#include "Punct.h"

Punct::Punct()
{
	this->x = 0;
	this->y = 0;
}

Punct::Punct(int a, int b)
{
	this->x = a;
	this->y = b;
}

Punct::Punct(const Punct& other)
{
	this->x = other.x;
	this->y = other.y;
}

Punct::~Punct()
{
}

int Punct::getX()
{
	return this->x;
}

void Punct::setX(int val)
{
	this->x = val;
}

int Punct::getY()
{
	return this->y;
}

void Punct::setY(int val)
{
	this->y = val;
}

int Punct::getCadran()
{
	switch (this->x * this->y)
	{
	case 0:
		return 0;
	default:
		switch (x > 0)
		{
		case true:
			switch (y > 0)
			{
			case true:
				return 1;
			case false:
				return 4;
			}
		case false:
			switch (y > 0)
			{
			case true:
				return 2;
			case false:
				return 3;
			}
		}
	}
}

Punct& Punct::operator=(const Punct& other)
{
	this->x = other.x;
	this->y = other.y;
	return (*this);
}

ostream& operator<<(ostream& os, const Punct& other)
{
	os << " ( " << other.x << " , " << other.y << " )";
	return os;
}
