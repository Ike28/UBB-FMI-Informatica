#include "Datetime.h"

Datetime::Datetime()
{
	this->dd = this->mm = this->yyyy = this->hh = this->ms = this->ss = 0;
}

Datetime::Datetime(int dd, int mm, int yyyy)
{
	this->dd = dd;
	this->mm = mm;
	this->yyyy = yyyy;

	this->hh = this->ms = this->ss = 0;
}

Datetime::Datetime(int dd, int mm, int yyyy, int hh, int ms, int ss)
{
	this->dd = dd;
	this->mm = mm;
	this->yyyy = yyyy;
	this->hh = hh;
	this->ms = ms;
	this->ss = ss;
}

Datetime::Datetime(const Datetime& other)
{
	this->dd = other.dd;
	this->mm = other.mm;
	this->yyyy = other.yyyy;
	this->hh = other.hh;
	this->ms = other.ms;
	this->ss = other.ss;
}

Datetime::~Datetime()
{
}

int Datetime::year()
{
	return this->yyyy;
}

int Datetime::month()
{
	return this->mm;
}

int Datetime::day()
{
	return this->dd;
}

int Datetime::hour()
{
	return this->hh;
}

int Datetime::minutes()
{
	return this->ms;
}

int Datetime::seconds()
{
	return this->ss;
}
