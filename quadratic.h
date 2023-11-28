/*
 * quadratic.h
 *
 *  Created on: 12/11/2023
 *      Author: Diego Quezada Colorado
 *      Matricula A01710024
 */

#ifndef QUADRATIC_H_
#define QUADRATIC_H_

#include <string>
#include <sstream>

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

template <class Key, class Value>
class Quadratic {
private:
	unsigned int (*func) (const Key);
	unsigned int size;
	unsigned int count;

	Key *keys;
	Key initialValue;
	Value *values;

	long indexOf(const Key) const;

public:
	Quadratic(unsigned int, Key, unsigned int (*f) (const Key)) ;
	~Quadratic();
	bool full() const;
	bool put(Key, Value) ;
	bool contains(const Key) const;
	Value get(const Key) ;
	void clear();
	string toString() const;
};

template <class Key, class Value>

Quadratic<Key, Value>::Quadratic(unsigned int sze, Key init, unsigned int (*f) (const Key))  {
    size = sze;
    keys = new Key[size];
    if (keys == 0) {
        throw OutOfMemory();
    }
    initialValue = init;
    for (unsigned int i = 0; i < size; i++) {
        keys[i] = init;
    }
    values = new Value[size];
    if (values == 0) {
        throw OutOfMemory();
    }
    for (int i = 0; i  < sze; i++){
        values[i] = 0;
    }

    func = f;
    count = 0;
}

template <class Key, class Value>

Quadratic<Key, Value>::~Quadratic() {
    delete [] keys;
    keys = 0;
    delete [] values;
    values = 0;
    size = 0;
    func = 0;
    count = 0;
}

template <class Key, class Value>

bool Quadratic<Key, Value>::full() const {
    return (count > size);
}

template <class Key, class Value>

long Quadratic<Key, Value>::indexOf(const Key k) const {
    unsigned int i, start;
    start = i = func(k) % size;
    do {
        if (keys[i] == k) {
            return i;
        }
        i = (i + 1) % size;
    } while (start != i);
    return -1;
}

template <class Key, class Value>
bool Quadratic<Key, Value>::put(Key k, Value v)  {
	unsigned int i, start;
	long pos;

	if (full()) {
		throw Overflow();
	}

	pos = indexOf(k);
	if (pos != -1) {
		values[pos] = v;
		return true;
	}

	start = i = func(k) % size;
    int quad = 1;
	do {
		if (keys[i] == initialValue) {
			keys[i] = k;
			values[i] = v;
			count++;
			return true;
		}
		i = (start + quad*quad) % size;
        quad++;
	} while (start != i);
	return false;
}

template <class Key, class Value>

bool Quadratic<Key, Value>::contains(const Key k) const {
    return (indexOf(k) != -1);
}

template <class Key, class Value>

Value Quadratic<Key, Value>::get(const Key k) {
    long pos;
    pos = indexOf(k);
    if (pos == -1) {
        throw NoSuchElement();
    }
    return values[pos];
}

template <class Key, class Value>

void Quadratic<Key, Value>::clear() {
    for (unsigned int i = 0; i < size; i++) {
        keys[i] = initialValue;
    }
    count = 0;
}

template <class Key, class Value>

string Quadratic<Key, Value>::toString() const {
    	std::stringstream aux;
    	for (int i = 0; i < size; i++){
    			if (keys[i] != initialValue){
    				aux << "(" << i << " ";
    			  aux << keys[i] << " : " << values[i] << ") ";
    			}
    	}
    	return aux.str();
    }

#endif /* QUADRATIC_H_ */