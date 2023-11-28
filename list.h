/*
 * list.h
 *
 *  Created on: 24/09/2023
 *      Author: Diego Quezada Colorado
 *      Matricula A01710024
 */

#ifndef LIST_H_
#define LIST_H_
using namespace std;

#include <string>

template <class T> class List;

/**
 * Clase Link
 * Esta clase nos va a ayudar a crear los nodos de la lista ligada
 * @param value es el valor que va a contener el nodo
 * @param next es un apuntador al siguiente nodo
 * Es clase amiga de la clase List
*/
template <class T>
class Link {
private:
    Link(T);
    Link(T, Link<T>*);

    T	    value;
    Link<T> *next;

    friend class List<T>;
};
/**
 * Constructor de la clase Link
 * @param val es el valor que va a contener el nodo
 * @param nxt es un apuntador al siguiente nodo
 * @return un objeto de la clase Link
 * Este constructor crea un nodo con el valor y el apuntador al siguiente nodo
 * que se le pasan como parámetros
 * Es privado porque solo se va a usar dentro de la clase
*/
template <class T>
Link<T>::Link(T val) {
    value = val;
    next = nullptr;
}
/**
 * Constructor de la clase Link
 * @param val es el valor que va a contener el nodo
 * @param nxt es un apuntador al siguiente nodo
 * @return un objeto de la clase Link
 * Este constructor crea un nodo con el valor y el apuntador al siguiente nodo
 * que se le pasan como parámetros
 * Es privado porque solo se va a usar dentro de la clase
 * Este constructor es sobrecargado para poder crear un nodo con el valor y el
 * apuntador al siguiente nodo que se le pasan como parámetros
*/
template <class T>
Link<T>::Link(T val, Link* nxt) {
    value= val;
    next= nxt;
}
/**
 * Clase List
 * Esta clase nos va a ayudar a crear la lista ligada
 * @param head es un apuntador al primer nodo de la lista
 * @param size es el tamaño de la lista
 * Es clase amiga de la clase Link
 * Tiene como métodos:
 * insertion
 * search
 * update
 * deleteAt
 * toString
 * empty
 * Constructor
 * Constructor copia
*/
template <class T>
class List {
public:
    List();

    void insertion(T);
    int search(T);
    void update(int, T);
    void deleteAt(int);
    string toString() const;
    bool empty() const;
    
private:
    Link<T> *head;
    int size;
};
/**
 * Constructor de la clase List
 * @param
 * @return un objeto de la clase List
 * Este constructor crea una lista vacía
 * El apuntador al primer nodo se inicializa en nullptr
 * El tamaño se inicializa en 0
 * Es público porque se va a usar en el main
 * Es un constructor sobrecargado para poder crear una lista vacía
*/
template <class T>
List<T>::List() {
    head = nullptr;
    size = 0;
}
/**
 * Método empty
 * @param
 * @return un booleano
 * Este método regresa un booleano que nos dice si la lista está vacía o no
*/
template <class T>
bool List<T>::empty() const {
    return (head == nullptr);
}
/**
 * Método insertion
 * @param val es el valor que se va a insertar en la lista
 * @return
 * Este método inserta un valor al final de la lista
 * Si la lista está vacía, el valor se inserta en el primer nodo
 * Si la lista no está vacía, el valor se inserta en el último nodo
*/


template <class T>
void List<T>::insertion(T val) {
    Link<T> *newLink, *p;

    newLink = new Link<T>(val);
    if (empty()) {
        newLink->next = head;
        head = newLink;
        size++;
        return;
    }
    p = head;
    while (p->next != nullptr) {
        p = p->next;
    }
    newLink->next = nullptr;
    p->next = newLink;
    size++;
}

/**
 * Método search
 * @param val es el valor que se va a buscar en la lista
 * @return un entero
 * Este método busca un valor en la lista
 * Si el valor se encuentra en la lista, regresa la posición en la que se encuentra
 * Si el valor no se encuentra en la lista, regresa -1
*/

template <class T>
int List<T>::search(T val) {
    int pos;
    Link<T> *p;

    p = head;
    pos = 0;
    while (p != nullptr) {
        if (p->value == val) {
            return pos;
        }
        p = p->next;
        pos++;
    }
    return -1;
}

/**
 * Método update
 * @param index es la posición en la que se va a actualizar el valor
 * @param val es el valor que se va a actualizar
 * @return
 * Este método actualiza el valor de un nodo en la lista
 * Si la lista está vacía, no hace nada
 * Si la lista no está vacía, busca el nodo en la posición que se le pasa como parámetro
 * y actualiza el valor del nodo
*/

template <class T>
void List<T>::update(int index, T val) {
    int pos;
    Link<T> *p;

    p = head;
    pos = 0;
    while (p != nullptr) {
        if (pos == index) {
            p->value = val;
            return;
        }
        p = p->next;
        pos++;
    }
}

/**
 * Método deleteAt
 * @param index es la posición en la que se va a eliminar el nodo
 * @return
 * Este método elimina un nodo de la lista
 * Si la lista está vacía, no hace nada
 * Si la lista no está vacía, busca el nodo en la posición que se le pasa como parámetro
 * y elimina el nodo
*/

template <class T>
void List<T>::deleteAt(int index) {
    int pos;
    Link<T> *p, *q;

    if (index == 0) {
        p = head;
        head = p->next;
        delete p;
        size--;
        return;
    }
    pos = 0;
    p = head;
    q = nullptr;
    while (p != nullptr) {
        if (pos == index) {
            q->next = p->next;
            delete p;
            size--;
            return;
        }
        q = p;
        p = p->next;
        pos++;
    }
}

/**
 * Método toString
 * @param
 * @return un string
 * Este método regresa una cadena con los valores de la lista
 * Si la lista está vacía, regresa una cadena vacía
 * Si la lista no está vacía, recorre la lista y va agregando los valores a la cadena
*/

template <class T>
string List<T>::toString() const {
    stringstream aux;
    Link<T> *p;

    p = head;
    aux << "[";
    while (p != nullptr) {
        aux << p->value;
        if (p->next != nullptr) {
            aux << ", ";
        }
        p = p->next;
    }
    aux << "]";
    return aux.str();
}









#endif