#include "Dreptunghi.h"
#include <math.h>
#include "utils.h"
#include <iostream>
#include <cstring>

map <char, int> Dreptunghi::pointKeys = {
    { 'A' , 0 },
    { 'B' , 2 },
    { 'C' , 1 },
    { 'D' , 3 }
};

void Dreptunghi::setLaturi()
{
    if (this->figura == NULL)
    {
        this->lungime = 0;
        this->latime = 0;
    }
    else
    {
        this->lungime = max(abs(this->figura[0].getX() - this->figura[1].getX()), abs(this->figura[0].getY() - this->figura[1].getY()));
        this->latime = min(abs(this->figura[0].getX() - this->figura[1].getX()), abs(this->figura[0].getY() - this->figura[1].getY()));
    }
}

Dreptunghi::Dreptunghi()
{
    this->figura = NULL;
    this->setLaturi();
}

Dreptunghi::Dreptunghi(int x1, int y1, int x2, int y2)
{
    this->figura = new Punct[4];
    figura[0] = Punct(x1, y1);
    figura[1] = Punct(x2, y2);


    if ((x1 < x2) == (y1 < y2))
    {
        figura[2] = Punct(x1, y2);
        figura[3] = Punct(x2, y1);
    }
    else
    {
        figura[2] = Punct(x2, y1);
        figura[3] = Punct(x1, y2);
    }
    this->setLaturi();
}

Dreptunghi::Dreptunghi(const Dreptunghi& other)
{
    this->lungime = other.lungime;
    this->latime = other.latime;
    if (other.figura == NULL)
        this->figura = NULL;
    else
    {
        this->figura = new Punct[4];
        for (int i = 0; i < 4; i++)
            this->figura[i] = other.figura[i];
    }
}

Dreptunghi::~Dreptunghi()
{
    if (this->figura != NULL)
    {
        delete[] this->figura;
        this->figura = NULL;
    }
}

Punct Dreptunghi::getPunctA()
{
    if (this->figura != NULL)
    {
        return this->figura[0];
    }
    else return Punct(0, 0);
}

Punct Dreptunghi::getPunctC()
{
    if (this->figura != NULL)
    {
        return this->figura[1];
    }
    else return Punct(0, 0);
}

Punct Dreptunghi::getPunctB()
{
    if (this->figura != NULL)
    {
        return this->figura[2];
    }
    else return Punct(0, 0);
}

Punct Dreptunghi::getPunctD()
{
    if (this->figura != NULL)
    {
        return this->figura[3];
    }
    else return Punct(0, 0);
}

Punct* Dreptunghi::getFigura()
{
    return this->figura;
}

int Dreptunghi::getLungime()
{
    return this->lungime;
}

int Dreptunghi::getLatime()
{
    return this->latime;
}

void Dreptunghi::setPunctA(int x, int y)
{
    if (this->figura != NULL)
    {
        this->figura[0] = Punct(x, y);
        this->figura[2].setX(x);
        this->figura[3].setY(y);
        this->setLaturi();
    }
}

void Dreptunghi::setPunctC(int x, int y)
{
    if (this->figura != NULL)
    {
        this->figura[1] = Punct(x, y);
        this->figura[2].setY(y);
        this->figura[3].setX(x);
        this->setLaturi();
    }
}

void Dreptunghi::setPunctB(int x, int y)
{
    if (this->figura != NULL)
    {
        this->figura[2] = Punct(x, y);
        this->figura[0].setX(x);
        this->figura[1].setY(y);
        this->setLaturi();
    }
}

void Dreptunghi::setPunctD(int x, int y)
{
    if (this->figura != NULL)
    {
        this->figura[3] = Punct(x, y);
        this->figura[2].setX(x);
        this->figura[0].setY(y);
        this->setLaturi();
    }
}

Dreptunghi& Dreptunghi:: operator=(const Dreptunghi& other)
{
    this->lungime = other.lungime;
    this->latime = other.latime;
    if (other.figura == NULL)
        this->figura = NULL;
    else
    {
        this->figura = new Punct[4];
        for (int i = 0; i < 4; i++)
            this->figura[i] = other.figura[i];
    }
    return (*this);
}

bool Dreptunghi::operator>(Dreptunghi& other)
{
    return this->aria() > other.aria();
}

bool Dreptunghi::operator<(Dreptunghi& other)
{
    return this->aria() < other.aria();
}

bool Dreptunghi::operator==(Dreptunghi& other)
{
    return abs(other.figura[0].getX() - other.figura[1].getX())
        == abs(this->figura[0].getX() - this->figura[1].getX())
        &&
        abs(other.figura[0].getY() - other.figura[1].getY())
        == abs(this->figura[0].getY() - this->figura[1].getY());
}

std::ostream& operator<<(std::ostream& os, Dreptunghi& other)
{
    if (other.figura == NULL)
    {
        os << "Dreptunghiul nul";
    }
    else
    {
        os << "Dreptunghiul de puncte\n";
        os << "A" << other.figura[0] << "  ";
        os << "B" << other.figura[2] << '\n';
        os << "D" << other.figura[3] << "  ";
        os << "C" << other.figura[1];
    }
    return os;
}

std::istream& operator>>(std::istream& is, Dreptunghi& other)
{
    if (other.figura)
        delete[] other.figura;
    other.figura = new Punct[4];
    int x1, y1, x2, y2;
    is >> x1;
    is >> y1;

    is >> x2;
    is >> y2;

    if (!(x1 != x2 && y1 != y2))
        x1 = y1 = x2 = y2 = 0;
    other.figura[0] = Punct(x1, y1);
    other.figura[1] = Punct(x2, y2);


    if ((x1 < x2) == (y1 < y2))
    {
        other.figura[2] = Punct(x1, y2);
        other.figura[3] = Punct(x2, y1);
    }
    else
    {
        other.figura[2] = Punct(x2, y1);
        other.figura[3] = Punct(x1, y2);
    }
    other.setLaturi();

    return is;
}

void Dreptunghi::lineEquation(char*& equ, char point1, char point2)
{
    Punct p1 = this->figura[this->pointKeys[point1]];
    Punct p2 = this->figura[this->pointKeys[point2]];

    int coefX = p2.getY() - p1.getY(),
        coefY = p1.getX() - p2.getX(),
        coefFree = p1.getY() * p2.getX() - p2.getY() * p1.getX();
    char cX[12], cY[12], cF[12];
    copyIntToString(cX, coefX); int lx = strlen(cX);
    copyIntToString(cY, coefY); int ly = strlen(cY);
    copyIntToString(cF, coefFree); int lf = strlen(cF);

    equ = new char[lx + ly + lf + 5];

    int i = 0, j = (cX[0] == '+') ? 1 : 0;
    for (; j < lx; j++)
        equ[i++] = cX[j];
    equ[i++] = 'x';

    for (j = 0; j < ly; j++)
        equ[i++] = cY[j];
    equ[i++] = 'y';

    for (j = 0; j < lf; j++)
        equ[i++] = cF[j];
    equ[i++] = '=';
    equ[i++] = '0';
    equ[i] = 0;
}

int Dreptunghi::aria()
{
    return this->lungime * this->latime;
}

int Dreptunghi::perimetrul()
{
    return 2 * (this->lungime + this->latime);
}
