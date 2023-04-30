#pragma once
#include <vector>
using namespace std;

template <class T> class Repo
{
private:
	vector<T> storage;
public:
	Repo();
	Repo(const Repo<T>& other);
	~Repo();

	int getDim();
	void setStorage(vector<T> storageGiven);

	Repo<T>& operator=(const Repo<T>& other);
	void addElem(T elem);
	void deleteElem(int cod);
	void updateElem(int cod, T newElem);
	vector<T> getAll();
	T findByID(int cod);
};

/// <summary>
/// Constructor pentru repository pe obiecte T
/// </summary>
/// <typeparam name="T">tipul elementelor memorate in repository</typeparam>
template<class T>
inline Repo<T>::Repo()
{
}

/// <summary>
/// Constructor de copiere pentru repository pe obiecte T
/// </summary>
/// <typeparam name="T">tipul elementelor memorate in repository</typeparam>
/// <param name="other">repository-ul dupa care se copiaza</param>
template<class T>
inline Repo<T>::Repo(const Repo<T>& other)
{
	this->storage = other.storage;
}

/// <summary>
/// Destructor pentru repository pe obiecte T
/// </summary>
/// <typeparam name="T">tipul elementelor memorate in repository</typeparam>
template<class T>
inline Repo<T>::~Repo()
{
}

/// <summary>
/// Returneaza tabloul de obiecte T memorate in repository-ul curent
/// </summary>
/// <typeparam name="T">tipul elementelor memorate in repository</typeparam>
/// <returns>tabloul de obiecte memorate</returns>
template<class T>
inline vector<T> Repo<T>::getAll()
{
	return this->storage;
}

template<class T>
inline T Repo<T>::findByID(int cod)
{
	for (int i = 0; i < this->getDim(); i++)
		if (this->storage[i].getCod() == cod)
			return this->storage[i];
	return T();
}

/// <summary>
/// Returneaza dimensiunea repository-ului
/// </summary>
/// <typeparam name="T">tipul elementelor memorate in repository</typeparam>
/// <returns>dimensiunea repository-ului</returns>
template<class T>
inline int Repo<T>::getDim()
{
	return this->storage.size();
}

template<class T>
inline void Repo<T>::setStorage(vector<T> storageGiven)
{
	this->storage = storageGiven;
}

/// <summary>
/// Operator de atribuire: atribuie o noua valoare repository-ului pe obiecte T
/// </summary>
/// <typeparam name="T">tipul elementelor memorate in repository</typeparam>
/// <param name="other">repository-ul dupa care se atribuie</param>
/// <returns>referinta catre repository-ul curent dupa actualizare</returns>
template<class T>
inline Repo<T>& Repo<T>::operator=(const Repo<T>& other)
{
	this->storage = other.storage;
	return *this;
}

/// <summary>
/// Adauga un obiect T in repository
/// </summary>
/// <typeparam name="T">tipul elementelor memorate in repository</typeparam>
/// <param name="elem">obiectul de adaugat</param>
template<class T>
inline void Repo<T>::addElem(T elem)
{
	this->storage.push_back(elem);
}

template<class T>
inline void Repo<T>::deleteElem(int cod)
{
	for (int i = 0; i < this->storage.size(); i++)
		if (this->storage[i].getCod() == cod)
			this->storage.erase(this->storage.begin() + i);
}

template<class T>
inline void Repo<T>::updateElem(int cod, T newElem)
{
	for (int i = 0; i < this->storage.size(); i++)
		if (this->storage[i].getCod() == cod)
			this->storage[i] = newElem;
}
