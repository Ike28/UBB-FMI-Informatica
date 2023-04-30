#include "Payment.h"
#include <string.h>

unsigned int Payment::nextID = 1;
vector<const char*> types{ "menaj", "mancare", "transport", "haine", "internet", "altele" };

/// <summary>
/// Constructor implicit de cheltuiala
/// </summary>
Payment::Payment()
{
	this->tip = nullptr;
	this->ID = nextID++;
	this->day = 0;
	this->sum = 0;
}

/// <summary>
/// Constructor de cheltuiala cu parametri
/// </summary>
/// <param name="tipDat">tipul cheltuielii</param>
/// <param name="dayGiven">ziua platii</param>
/// <param name="sumGiven">suma cheltuita</param>
Payment::Payment(char* tipDat, int dayGiven, int sumGiven)
{
	if (tipDat != nullptr)
	{
		this->tip = new char[strlen(tipDat) + 1];
		strcpy_s(this->tip, strlen(tipDat) + 1, tipDat);
	}
	else this->tip = nullptr;
	this->ID = nextID++;
	this->day = dayGiven;
	this->sum = sumGiven;
}

/// <summary>
/// Constructor de copiere pentru cheltuieli
/// </summary>
/// <param name="other">Cheltuiala dupa care se copiaza</param>
Payment::Payment(const Payment& other)
{
	if (other.tip != nullptr)
	{
		this->tip = new char[strlen(other.tip) + 1];
		strcpy_s(this->tip, strlen(other.tip) + 1, other.tip);
	}
	else this->tip = nullptr;
	this->ID = other.ID;
	this->day = other.day;
	this->sum = other.sum;
}

/// <summary>
/// Destructor pentru cheltuieli
/// </summary>
Payment::~Payment()
{
	delete[] this->tip;
	this->tip = nullptr;
}

/// <summary>
/// Returneaza tipul cheltuielii curente
/// </summary>
/// <returns>tipul cheltuielii</returns>
char* Payment::getTip()
{
	return this->tip;
}

/// <summary>
/// Seteaza tipul cheltuielii curente
/// </summary>
/// <param name="tipDat">tipul nou</param>
void Payment::setTip(char* tipDat)
{
	if (tipDat != nullptr)
	{
		this->tip = new char[strlen(tipDat) + 1];
		strcpy_s(this->tip, strlen(tipDat) + 1, tipDat);
	}
	else this->tip = nullptr;
}

/// <summary>
/// Returneaza ID-ul intern al cheltuielii curente
/// </summary>
/// <returns>ID-ul cheltuielii</returns>
unsigned int Payment::getID()
{
	return this->ID;
}

/// <summary>
/// Seteaza ID-ul cheltuielii curente (NERECOMANDAT)
/// </summary>
/// <param name="newID">ID-ul nou</param>
void Payment::setID(int newID)
{
	this->ID = newID;
}

/// <summary>
/// Operator de atribuire: atribuie o noua valoare cheltuielii curente
/// </summary>
/// <param name="other">cheltuiala dupa care se atribuie</param>
/// <returns>referinta catre cheltuiala curenta dupa actualizare</returns>
Payment& Payment::operator=(const Payment& other)
{
	if (other.tip != nullptr)
	{
		this->tip = new char[strlen(other.tip) + 1];
		strcpy_s(this->tip, strlen(other.tip) + 1, other.tip);
	}
	else this->tip = nullptr;
	this->ID = other.ID;
	this->day = other.day;
	this->sum = other.sum;
	return *this;
}

/// <summary>
/// Operator de egalitate: verifica daca doua cheltuieli sunt egale (nu se ia in calcul ID-ul)
/// </summary>
/// <param name="other">cheltuiala dupa care se compara cea curenta</param>
/// <returns>cheltuiala curenta dupa actualizare</returns>
bool Payment::operator==(const Payment& other)
{
	return (strcmp(this->tip, other.tip) == 0
		&& this->day == other.day
		&& this->sum == other.sum);
}

bool Payment::operator<(const Payment& other)
{
	return this->sum < other.sum;
}

/// <summary>
/// Returneaza atributul zilei cheltuielii
/// </summary>
/// <returns>ziua cheltuielii</returns>
int Payment::getDay()
{
	return this->day;
}

/// <summary>
/// Seteaza atributul zilei cheltuielii
/// </summary>
/// <param name="dayGiven">valoare noua a zilei</param>
void Payment::setDay(int dayGiven)
{
	this->day = dayGiven;
}

/// <summary>
/// Returneaza atributul sumei cheltuite
/// </summary>
/// <returns>suma cheltuielii</returns>
int Payment::getSum()
{
	return this->sum;
}

/// <summary>
/// Seteaza atributul sumei cheltuielii
/// </summary>
/// <param name="sumGiven">valoarea noua a sumei cheltuite</param>
void Payment::setSum(int sumGiven)
{
	this->sum = sumGiven;
}

//vector<const char*>& Payment::getTypes()
//{
	//return Payment::types;
//}

/// <summary>
/// Operator de transmitere in stream de date generic a cheltuielii
/// </summary>
/// <param name="os">stream-ul de date</param>
/// <param name="other">cheltuiala pentru transmitere</param>
/// <returns>referinta catre stream-ul de date</returns>
ostream& operator<<(ostream& os, Payment& other)
{
	if (other.getTip() == nullptr)
		os << "Cheltuiala nula";
	else
	{
		os << "ID: " << other.getID() << " | Cheltuiala: "
					 << other.getTip() 
					 << " in ziua " << other.getDay() 
					 << " , " << other.getSum() << " lei";
	}
	return os;
}
