#pragma once
#include "Repo.h"
#include "Undo.h"
#include "utils.h"
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

template <class T> class Service
{
	private:
		Repo<T> repo;
		Undo<T> timeline;
	public:
		Service();
		Service(Repo<T>& repoDat);
		~Service();

		Repo<T>& getRepo();
		void setRepo(Repo<T> repoDat);
		int size();

		void addElem(T elem);
		void deleteByID(int idDat);
		void updateByID(int idDat, T elem);
		T* read();

		void deleteByDay(int dayGiven);
		void deleteByInterval(int dayStart, int dayFinal);
		void deleteByType(char* typeGiven);

		vector<T> listByType(char* typeGiven, char disc, int val);

		pair<int, int> maxDayBySums();
		int sumByType(char* typeGiven);
		vector<pair<int,int>> sortSumsByType(char* typeGiven);

		void filterByType(char* typeGiven, char disc, int val);

		void undo();
		bool isUndo();

		Service<T>& operator=(const Service<T>& other);
};

/// <summary>
/// Constructor implicit pentru serviciu pe obiecte T
/// </summary>
/// <typeparam name="T">tipul elementelor asupra carora actioneaza serviciul</typeparam>
template<class T>
inline Service<T>::Service()
{
}

/// <summary>
/// Constructor cu parametri pentru serviciu pe obiecte T
/// </summary>
/// <typeparam name="T">tipul elementelor asupra carora actioneaza serviciul</typeparam>
/// <param name="repoDat">repository pe obiecte T asupra caruia va actiona serviciul</param>
template<class T>
inline Service<T>::Service(Repo<T>& repoDat)
{
	this->repo = repoDat;
}

/// <summary>
/// Destructor pentru serviciu pe obiecte T
/// </summary>
/// <typeparam name="T">tipul elementelor asupra carora actioneaza serviciul</typeparam>
template<class T>
inline Service<T>::~Service()
{
}

/// <summary>
/// Returneaza repository-ul pe obiecte T prelucrat de catre serviciul curent
/// </summary>
/// <typeparam name="T">tipul elementelor asupra carora actioneaza serviciul</typeparam>
/// <returns>repository-ul</returns>
template<class T>
inline Repo<T>& Service<T>::getRepo()
{
	return this->repo;
}

/// <summary>
/// Seteaza repository-ul pe obiecte T prelucrat de catre serviciul curent
/// </summary>
/// <typeparam name="T">tipul elementelor asupra carora actioneaza serviciul</typeparam>
/// <param name="repoDat">repository-ul dat</param>
template<class T>
inline void Service<T>::setRepo(Repo<T> repoDat)
{
	this->repo = repoDat;
}

/// <summary>
/// Returneaza dimensiunea repository-ului pe obiecte T prelucrat de catre serviciul curent
/// </summary>
/// <typeparam name="T">tipul elementelor asupra carora actioneaza serviciul</typeparam>
/// <returns>dimensiunea repository-ului</returns>
template<class T>
inline int Service<T>::size()
{
	return this->repo.getDim();
}

/// <summary>
/// Adauga un obiect T in repository
/// </summary>
/// <typeparam name="T">tipul elementelor asupra carora actioneaza serviciul</typeparam>
/// <param name="elem">elementul de adaugat</param>
template<class T>
inline void Service<T>::addElem(T elem)
{
	this->timeline.registerUndo(this->repo);
	this->repo.addElem(elem);
}

/// <summary>
/// Sterge pe baza de ID un obiect din repository-ul pe obiecte T ; apelul nu are niciun efect in caz de inexistenta a ID-ului
/// </summary>
/// <typeparam name="T">tipul elementelor asupra carora actioneaza serviciul</typeparam>
/// <param name="idDat">ID-ul dupa care se cauta</param>
template<class T>
inline void Service<T>::deleteByID(int idDat)
{
	this->timeline.registerUndo(this->repo);
	this->repo.deleteByID(idDat);
}

/// <summary>
/// Actualizeaza dupa ID un obiect din repository-ul pe obiecte T ; apelul nu are niciun efect in caz de inexistenta a ID-ului
/// </summary>
/// <typeparam name="T">tipul elementelor asupra carora actioneaza serviciul</typeparam>
/// <param name="idDat">ID-ul dupa care se cauta</param>
/// <param name="elem">elementul nou ce il va inlocui pe cel gasit, in caz de existenta</param>
template<class T>
inline void Service<T>::updateByID(int idDat, T elem)
{
	this->timeline.registerUndo(this->repo);
	this->repo.updateByID(idDat, elem);
}

/// <summary>
/// Returneaza tabloul de obiecte T memorate in repository
/// </summary>
/// <typeparam name="T">tipul elementelor asupra carora actioneaza serviciul</typeparam>
/// <returns>tabloul repository-ului</returns>
template<class T>
inline T* Service<T>::read()
{
	return this->repo.getAll();
}

template<class T>
inline void Service<T>::deleteByDay(int dayGiven)
{
	this->timeline.registerUndo(this->repo);
	vector<int> validIDs;
	for (int i = 0; i < this->repo.getDim(); i++)
		if (this->repo.getAll()[i].getDay() == dayGiven)
			validIDs.push_back(this->repo.getAll()[i].getID());
	for (vector<int>::iterator i = validIDs.begin(); i != validIDs.end(); i++)
		this->repo.deleteByID(*i);
}

template<class T>
inline void Service<T>::deleteByInterval(int dayStart, int dayFinal)
{
	this->timeline.registerUndo(this->repo);
	vector<int> validIDs; int dayCurrent;
	for (int i = 0; i < this->repo.getDim(); i++)
	{
		dayCurrent = this->repo.getAll()[i].getDay();
		if (dayCurrent >= dayStart && dayCurrent <= dayFinal)
			validIDs.push_back(this->repo.getAll()[i].getID());
	}
	for (vector<int>::iterator i = validIDs.begin(); i != validIDs.end(); i++)
		this->repo.deleteByID(*i);
}

template<class T>
inline void Service<T>::deleteByType(char* typeGiven)
{
	this->timeline.registerUndo(this->repo);
	vector<int> validIDs;
	for (int i = 0; i < this->repo.getDim(); i++)
		if (strcmp(this->repo.getAll()[i].getTip() , typeGiven) == 0)
			validIDs.push_back(this->repo.getAll()[i].getID());
	for (vector<int>::iterator i = validIDs.begin(); i != validIDs.end(); i++)
		this->repo.deleteByID(*i);
}

template<class T>
inline vector<T> Service<T>::listByType(char* typeGiven, char disc, int val)
{
	vector<T> found; T current;
	for (int i = 0; i < this->repo.getDim(); i++)
	{
		T current = this->repo.getAll()[i];
		if (strcmp(current.getTip(), typeGiven) == 0)
			if (disc == '-'
				|| (disc == '=' && current.getSum() == val)
				|| (disc == '>' && current.getSum() > val)
				|| (disc == '<' && current.getSum() < val))
				found.push_back(current);
	}
	return found;
}

template<class T>
inline pair<int, int> Service<T>::maxDayBySums()
{
	vector<int> days; int currentDay;
	for (int i = 0; i < this->repo.getDim(); i++)
	{
		currentDay = this->repo.getAll()[i].getDay();
		if (find(days.begin(), days.end(), currentDay) == days.end())
			days.push_back(currentDay);
	}
	pair<int, int> result; result.first = result.second = 0;
	int currentSum;
	for (int i = 0; i < days.size(); i++)
	{
		currentSum = 0;
		for (int j = 0; j < this->repo.getDim(); j++)
			if (this->repo.getAll()[j].getDay() == days[i])
				currentSum += this->repo.getAll()[j].getSum();
		if (currentSum > result.second)
			result.first = days[i], result.second = currentSum;
	}
	return result;
}

template<class T>
inline int Service<T>::sumByType(char* typeGiven)
{
	vector<T> found; T current;
	for (int i = 0; i < this->repo.getDim(); i++)
	{
		current = this->repo.getAll()[i];
		if (strcmp(current.getTip(), typeGiven) == 0)
			found.push_back(current);
	}
	int sum = 0;
	typename vector<T>::iterator i = found.begin();
	while (i != found.end())
	{
		sum += (*i).getSum();
		i++;
	}
	return sum;
}

template<class T>
inline vector<pair<int,int>> Service<T>::sortSumsByType(char* typeGiven)
{
	vector<pair<int, int>> found; T current; int n = 0;
	if (strcmp("null", typeGiven) != 0)
	{
		
		for (int i = 0; i < this->repo.getDim(); i++)
		{
			current = this->repo.getAll()[i];
			if (strcmp(current.getTip(), typeGiven) == 0)
			{
				n++;
				bool ok = false;
				for (vector<pair<int, int>>::iterator i = found.begin(); i != found.end() && ok == false; i++)
					if ((*i).first == current.getDay())
						(*i).second += current.getSum(), ok = true;
				if (!ok)
					found.push_back(make_pair(current.getDay(), current.getSum()));
			}
		}
	}
	else
	{
		for (int i = 0; i < this->repo.getDim(); i++)
		{
			current = this->repo.getAll()[i];
			bool ok = false;
			for (vector<pair<int, int>>::iterator i = found.begin(); i != found.end() && ok == false; i++)
				if ((*i).first == current.getDay())
					(*i).second += current.getSum(), ok = true;
			if (!ok)
				found.push_back(make_pair(current.getDay(), current.getSum()));
		}
	}
	radixSort(found);
	return found;
}

template<class T>
inline void Service<T>::filterByType(char* typeGiven, char disc, int val)
{
	this->timeline.registerUndo(this->repo);
	vector<int> foundIDs;
	for (int i = 0; i < this->repo.getDim(); i++)
	{
		T current = this->repo.getAll()[i];
		if (strcmp(current.getTip(), typeGiven) == 0)
		{
			if (
				(disc == '=' && current.getSum() != val)
				|| (disc == '>' && current.getSum() <= val)
				|| (disc == '<' && current.getSum() >= val))
				foundIDs.push_back(current.getID());
		}
		else foundIDs.push_back(current.getID());
	}
	for (int i = 0; i < foundIDs.size(); i++)
		this->repo.deleteByID(foundIDs[i]);
}

template<class T>
inline void Service<T>::undo()
{
	this->repo = this->timeline.doUndo();
}

template<class T>
inline bool Service<T>::isUndo()
{
	return this->timeline.aiUndo();
}

/// <summary>
/// Operator de atribuire: atribuie o noua valoare serviciului de functionalitati
/// </summary>
/// <typeparam name="T">tipul elementelor asupra carora actioneaza serviciul</typeparam>
/// <param name="other">serviciul dupa care se va atribui</param>
/// <returns>referinta catre serviciul curent dupa actualizare</returns>
template<class T>
inline Service<T>& Service<T>::operator=(const Service<T>& other)
{
	this->repo = other.repo;
	return *this;
}
