#include "Component.h"

Component::Component()
{
	this->price = 0;
	this->stock = 0;
}

Component::Component(string codeGiven, string nameGiven, int priceGiven, int stockGiven)
{
	this->code = codeGiven;
	this->name = nameGiven;
	this->price = priceGiven;
	this->stock = stockGiven;
}

Component::Component(const Component& other)
{
	this->code = other.code;
	this->name = other.name;
	this->price = other.price;
	this->stock = other.stock;
}

Component::~Component()
{
}
