/*
 * dlist.h
 *
 *  Created on: 24/09/2023
 *      Author: Diego Quezada Colorado
 *      Matricula A01710024
 */

#ifndef DLIST_H_
#define DLIST_H_
using namespace std;
#include <sstream>
#include <string>

template <class T> class DList;

template <class T>
class DLink {
private:
	DLink(T);
	DLink(T, DLink<T>*, DLink<T>*);
	DLink(const DLink<T>&);

	T	    value;
	DLink<T> *previous;
	DLink<T> *next;

	friend class DList<T>;

};

template <class T>
DLink<T>::DLink(T val) : value(val), previous(0), next(0) {}

template <class T>
DLink<T>::DLink(T val, DLink *prev, DLink* nxt) : value(val), previous(prev), next(nxt) {}

template <class T>
DLink<T>::DLink(const DLink<T> &source) : value(source.value), previous(source.previous), next(source.next) {}

template <class T>
class DList {
public:
	DList();
	DList(const DList<T>&);
	~DList();

	void insertion(T);
	int search(T);
	void update(int, T);
	T deleteAt(int);
	void deleteAll();

	string toStringForward() const;
	string toStringBackward() const;

private:
	DLink<T> *head;
	DLink<T> *tail;
	int 	 size;
};

template <class T>
DList<T>::DList() : head(0), tail(0), size(0) {}

template <class T>
DList<T>::~DList() {
	deleteAll();
}

template <class T>
void DList<T>::insertion(T val) {
	DLink<T> *newLink;

	newLink = new DLink<T>(val);

	if (head == 0) {
		head = newLink;
		tail = newLink;
	} else {
		tail->next = newLink;
		newLink->previous = tail;
		tail = newLink;
	}
	size++;
}

template <class T>
int DList<T>::search(T val) {
	DLink<T> *p;
	int i = 0;

	p = head;
	while(p != 0) {
		if (p->value == val) {
			return i;
		}
		p = p->next;
		i++;
	}
	return -1;
}

template <class T>
void DList<T>::update(int index, T val) {
	DLink<T> *p;
	int pos = 0;

	p = head;
	while(p != 0) {
		if (pos == index) {
			p->value = val;
			return;
		}
		p = p->next;
		pos++;
	}
}

template <class T>
T DList<T>::deleteAt(int index) {
	DLink<T> *p;
	T val;
	int pos = 0;

	p = head;
	while(p != 0) {
		if (pos == index) {
			val = p->value;

			if (p == head) {
				if (p->next == 0) {
					head = tail = 0;
				} else {
					head = p->next;
					p->next->previous = 0;
				}
			} else if (p == tail) {
				tail = p->previous;
				p->previous->next = 0;
			} else {
				p->previous->next = p->next;
				p->next->previous = p->previous;
			}

			delete p;
			size--;
			return val;
		}
		p = p->next;
		pos++;
	}
	return val;
}

template <class T>
void DList<T>::deleteAll() {
	DLink<T> *p, *q;

	p = head;
	while(p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0;
	tail = 0;
	size = 0;
}

template <class T>
string DList<T>::toStringForward() const {
	stringstream aux;
	DLink<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

template <class T>
string DList<T>::toStringBackward() const {
	stringstream aux;
	DLink<T> *p;

	p = tail;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->previous != 0) {
			aux << ", ";
		}
		p = p->previous;
	}
	aux << "]";
	return aux.str();
}



#endif