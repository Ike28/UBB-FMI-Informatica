#pragma once
using namespace std;
#include <iostream>
#include <string>
#include <typeinfo>
#include <ostream>
#include <string>

class Component
{
	private:
		string code;
		string name;
		int price;
		int stock;
	public:
		Component();
		Component(string codeGiven, string nameGiven, int priceGiven, int stockGiven);
		Component(const Component& other);
		~Component();
		
		string getCode() { return code; }
		string getName() { return name; }
		int getPrice() { return price; }
		int getStock() { return stock; }

		void setPrice(int priceGiven) { price = priceGiven; }
		void setStock(int stockGiven) { stock = stockGiven; }
		void setName(string nameGiven) { name = nameGiven; }

};
