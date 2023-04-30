#pragma once
#include "Repo.h"
#include "RepoFile.h"
#include <vector>
using namespace std;

template <class T> class Service
{
private:
	Repo<T> repo;
public:
	Service();
	Service(Repo<T>& repoDat);
	~Service();

	Repo<T>& getRepo();
	void setRepo(Repo<T> repoDat);
	int size();
	Book findByCod(int codDat);

	void addElem(T elem);
	void deleteElem(int codDat);
	void updateElem(int codDat, T elem);
	vector<T> read();

	void orderBooks(vector<int> codes, int& pretTotal, int& reducere);

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
	this->repo.addElem(elem);
}

/// <summary>
/// Sterge pe baza de ID un obiect din repository-ul pe obiecte T ; apelul nu are niciun efect in caz de inexistenta a ID-ului
/// </summary>
/// <typeparam name="T">tipul elementelor asupra carora actioneaza serviciul</typeparam>
/// <param name="idDat">ID-ul dupa care se cauta</param>
template<class T>
inline void Service<T>::deleteElem(int codDat)
{
	this->repo.deleteElem(codDat);
}

/// <summary>
/// Actualizeaza dupa ID un obiect din repository-ul pe obiecte T ; apelul nu are niciun efect in caz de inexistenta a ID-ului
/// </summary>
/// <typeparam name="T">tipul elementelor asupra carora actioneaza serviciul</typeparam>
/// <param name="idDat">ID-ul dupa care se cauta</param>
/// <param name="elem">elementul nou ce il va inlocui pe cel gasit, in caz de existenta</param>
template<class T>
inline void Service<T>::updateElem(int codDat, T elem)
{
	this->repo.updateElem(codDat, elem);
}

/// <summary>
/// Returneaza tabloul de obiecte T memorate in repository
/// </summary>
/// <typeparam name="T">tipul elementelor asupra carora actioneaza serviciul</typeparam>
/// <returns>tabloul repository-ului</returns>
template<class T>
inline vector<T> Service<T>::read()
{
	return this->repo.getAll();
}


template<class T>
inline void Service<T>::orderBooks(vector<int> codes, int& pretTotal, int& reducere)
{
	pretTotal = 0;  reducere = 0;
	vector<T> books = this->repo.getAll(); T bAux;
	int cartiValide = 0; char categorie[] = "dezvoltare personala";
	for (int i = 0; i < codes.size(); i++)
	{
		for (int j = 0; j < books.size(); j++)
			if (books[j].getCod() == codes[i])
			{
				bAux = books[j];
				int stoc = bAux.getStoc();
				bAux.setStoc(stoc - 1);
				this->repo.updateElem(bAux.getCod(), bAux);
				pretTotal += bAux.getPret();
				if (strcmp(bAux.getGen(), categorie) == 0 && cartiValide < 2)
				{
					cartiValide++;
					if (cartiValide == 2)
						reducere = 15;
				}
			}
	}
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
