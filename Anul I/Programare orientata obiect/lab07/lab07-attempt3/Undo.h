#pragma once
#include "Repo.h"
#include <stack>
using namespace std;

template <class T>
class Undo
{
private:
	stack<Repo<T>> undoStack;
public:
	Undo();
	Undo(const Undo<T>& other);
	~Undo();

	bool aiUndo();
	void registerUndo(Repo<T> r);
	Repo<T> doUndo();
};

template<class T>
inline Undo<T>::Undo()
{
}

template<class T>
inline Undo<T>::Undo(const Undo<T>& other)
{
	this->undoStack = other.undoStack;
}

template<class T>
inline Undo<T>::~Undo()
{
}

template<class T>
inline bool Undo<T>::aiUndo()
{
	return this->undoStack.size() > 0;
}

template<class T>
inline void Undo<T>::registerUndo(Repo<T> r)
{
	this->undoStack.push(r);
}

template<class T>
inline Repo<T> Undo<T>::doUndo()
{
	Repo<T> previous = this->undoStack.top();
	this->undoStack.pop();
	return previous;
}
