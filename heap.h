/*
 * heap.h
 *
 *  Created on: 19/10/2023
 *      Author: Diego Quezada Colorado
 *      Matricula A01710024
 */
#ifndef HEAP_H_
#define HEAP_H_

#include <string>
#include <sstream>
#include <iostream>
#include <exception>
#include <cstdio>
using namespace std;

class Exception : public exception {
protected:
	string text;

public:
	Exception() throw(): text("Basic exception"){};
	~Exception() throw(){};
	virtual const char* what() const throw(){return text.c_str();};
};	


class OutOfMemory : public Exception {
public:
	OutOfMemory() throw(){
		text = string("OutOfMemory");};
};


class NoSuchElement : public Exception {
public:
	NoSuchElement() throw(){
		text = string("NoSuchElement");};
};


class Overflow : public Exception {
public:
	Overflow() throw(){
		text = string("Overflow");};
};


template <class T>
class Heap {
private:
	T *data;
	unsigned int sze;
	unsigned int count;

	unsigned int parent(unsigned int) const;
	unsigned int left(unsigned int) const;
	unsigned int right(unsigned int) const;
	void heapify(unsigned int);
	void swap(unsigned int, unsigned int);

public:
	Heap(unsigned int) ;
	~Heap();
	bool empty() const;
	bool full() const;
	void push(T) ;
	void pop() ;
    int size() {return count-1;}; 
	void clear();
    T top ();
	string toString() const;
};
template <class T>
Heap<T>::Heap(unsigned int ze)  {
	data = new T[ze];
	if (data == 0) {
		throw OutOfMemory();
	}
	sze = ze+1;
	count = 1;
}

template <class T>
Heap<T>::~Heap() {
	delete [] data; data = 0;
	sze = 0; count = 0;
}

template <class T>
bool Heap<T>::empty() const {
	return (count == 1);
}

template <class T>
bool Heap<T>::full() const {
	return (count == sze);
}

template <class T>
unsigned int Heap<T>::parent(unsigned int pos) const {
	return int(pos/2);
}

template <class T>
unsigned int Heap<T>::left(unsigned int pos) const {
	return pos*2;
}

template <class T>
unsigned int Heap<T>::right(unsigned int pos) const {
	return (pos*2)+1;
}

template <class T>
void Heap<T>::swap(unsigned int i, unsigned int j) {
	T aux = data[i];
	data[i] = data[j];
	data[j] = aux;
}

template <class T>
void Heap<T>::heapify(unsigned int pos) {
	unsigned int le = left(pos);
	unsigned int ri= right(pos);
	unsigned int min = pos;
	if (le <= count && data[le]< data[min]){
		min=le;
	}
	if (ri <= count && data[ri]< data[min]){
		min=ri;
	}
	if (min!=pos){
		swap(pos,min);
		heapify(min);
	}
	
}

template <class T>
void Heap<T>::push(T val)  {
	unsigned int pos;
	if (full()) {
		throw Overflow();
	}
	pos = count;
	count++;
	while (pos > 0 && val < data[parent(pos)]) {
		data[pos] = data[parent(pos)];
		pos = parent(pos);
	}
	data[pos] = val;

}

template <class T>
void Heap<T>::pop()  {
	if (empty()) {
		throw NoSuchElement();
	}
	T aux;
	aux = data[1];
	data[1]= data[--count];
	heapify(1);
}

template <class T>
T Heap<T>::top()  {
	if (!empty()) {
		return data[1];
	}
	return 0;
	
}

template <class T>
void Heap<T>::clear() {
	count = 1;
}


template <class T>
std::string Heap<T>::toString() const {
	std::stringstream aux;

	aux << "[";
	for (unsigned int i = 1; i < count; i++) {
		if (i != 1) {
			aux << " ";
		}
		aux << data[i];
	}
	aux << "]";
	return aux.str();
}

#endif