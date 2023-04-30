#pragma once

template <class T> class Repo
{
	private:
		T* storage;
		int dim;
	public:
		Repo();
		Repo(const Repo<T>& other);
		~Repo();

		T* getAll();
		int getDim();

		Repo<T>& operator=(const Repo<T>& other);
		void addElem(T elem);
		void deleteByID(int idDat);
		void updateByID(int idDat, T newElem);
};

/// <summary>
/// Constructor pentru repository pe obiecte T
/// </summary>
/// <typeparam name="T">tipul elementelor memorate in repository</typeparam>
template<class T>
inline Repo<T>::Repo()
{
	this->storage = nullptr;
	this->dim = 0;
}

/// <summary>
/// Constructor de copiere pentru repository pe obiecte T
/// </summary>
/// <typeparam name="T">tipul elementelor memorate in repository</typeparam>
/// <param name="other">repository-ul dupa care se copiaza</param>
template<class T>
inline Repo<T>::Repo(const Repo<T>& other)
{
	if (other.storage != nullptr)
	{
		this->storage = new T[other.dim + 1];
		for (int i = 0; i < other.dim; i++)
			this->storage[i] = other.storage[i];
	}
	else this->storage = nullptr;
	this->dim = other.dim;
}

/// <summary>
/// Destructor pentru repository pe obiecte T
/// </summary>
/// <typeparam name="T">tipul elementelor memorate in repository</typeparam>
template<class T>
inline Repo<T>::~Repo()
{
	delete[] this->storage;
	this->storage = nullptr;
}

/// <summary>
/// Returneaza tabloul de obiecte T memorate in repository-ul curent
/// </summary>
/// <typeparam name="T">tipul elementelor memorate in repository</typeparam>
/// <returns>tabloul de obiecte memorate</returns>
template<class T>
inline T* Repo<T>::getAll()
{
	return this->storage;
}

/// <summary>
/// Returneaza dimensiunea repository-ului
/// </summary>
/// <typeparam name="T">tipul elementelor memorate in repository</typeparam>
/// <returns>dimensiunea repository-ului</returns>
template<class T>
inline int Repo<T>::getDim()
{
	return this->dim;
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
	if (other.storage != nullptr)
	{
		this->storage = new T[other.dim + 1];
		for (int i = 0; i < other.dim; i++)
			this->storage[i] = other.storage[i];
	}
	else this->storage = nullptr;
	this->dim = other.dim;
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
	T* auxiliar = new T[this->dim + 1];
	for (int i = 0; i < this->dim; i++)
		auxiliar[i] = this->storage[i];
	auxiliar[this->dim] = elem;

	this->storage = new T[this->dim + 1];
	for (int i = 0; i <= this->dim; i++)
		this->storage[i] = auxiliar[i];
	this->dim++;
}

/// <summary>
/// Sterge dupa ID un obiect din repository
/// </summary>
/// <typeparam name="T">tipul elementelor memorate in repository</typeparam>
/// <param name="idDat">ID-ul dupa care se cauta</param>
template<class T>
inline void Repo<T>::deleteByID(int idDat)
{
	bool found = false; int pos = -1;
	int st = 0, dr = this->dim-1, m, cur;
	while (st <= dr && !found)
	{
		m = (st + dr) / 2;
		cur = this->storage[m].getID();
		if (cur == idDat)
			found = true, pos = m;
		else if (idDat < cur)
			dr = m - 1;
		else st = m + 1;
	}
	if (found)
	{
		for (int i = pos; i < dim - 1; i++)
			this->storage[i] = this->storage[i + 1];
		this->dim--;
	}
}

/// <summary>
/// Actualizeaza dupa ID un obiect din repository
/// </summary>
/// <typeparam name="T">tipul elementelor memorate in repository</typeparam>
/// <param name="idDat">ID-ul dupa care se cauta</param>
/// <param name="newElem">elementul nou</param>
template<class T>
inline void Repo<T>::updateByID(int idDat, T newElem)
{
	bool found = false; int pos = -1;
	int st = 0, dr = this->dim - 1, m, cur;
	while (st <= dr && !found)
	{
		m = (st + dr) / 2;
		cur = this->storage[m].getID();
		if (cur == idDat)
			found = true, pos = m;
		else if (idDat < cur)
			dr = m - 1;
		else st = m + 1;
	}
	if (found)
	{
		newElem.setID(idDat);
		this->storage[pos] = newElem;
	}
}
