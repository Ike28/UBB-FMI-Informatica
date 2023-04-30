#pragma once

class Datetime
{
	private:
		int dd;
		int mm;
		int yyyy;
		int hh;
		int ms;
		int ss;
	public:
		Datetime();
		Datetime(int dd, int mm, int yyyy);
		Datetime(int dd, int mm, int yyyy, int hh, int ms, int ss);
		Datetime(const Datetime& other);
		~Datetime();

		int year();
		int month();
		int day();
		int hour();
		int minutes();
		int seconds();
};
