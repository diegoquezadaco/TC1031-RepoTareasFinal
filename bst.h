/*
 * list.h
 *
 *  Created on: 5/10/2023
 *      Author: Diego Quezada Colorado
 *      Matricula A01710024
 */
#ifndef BST_H_
#define BST_H_

#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include <queue>

using namespace std;

template <class T> class BST;

template <class T>
class Node {
private:
	T value;
	Node *left, *right;

	Node<T>* succesor();

public:
	Node(T);
	Node(T, Node<T>*, Node<T>*);
	void add(T);
	bool find(T);
	void remove(T);
	void inorder(stringstream&) const;
	void preorder(stringstream&) const;
	void postorder(stringstream&) const;
	void levelorder(stringstream&) const;
	int height() const;
	string ancestors(T) const;
	int whatlevelamI(T) const;


	friend class BST<T>;
};

template <class T>
Node<T>::Node(T val) : value(val), left(0), right(0) {}

template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri)
	: value(val), left(le), right(ri) {}

template <class T>
void Node<T>::add(T val) {
	if (val < value) {
		if (left != 0) {
			left->add(val);
		} else {
			left = new Node<T>(val);
		}
	} else {
		if (right != 0) {
			right->add(val);
		} else {
			right = new Node<T>(val);
		}
	}
}

template <class T>
bool Node<T>::find(T val) {
	if (val == value) {
		return true;
	} else if (val < value) {
		return (left != 0 && left->find(val));
	} else if (val > value) {
		return (right != 0 && right->find(val));
	}
	return false;
}

template <class T>
Node<T>* Node<T>::succesor() {
	Node<T> *le, *ri;

	le = left;
	ri = right;

	if (right == 0) {
		if (left != 0) {
			left = left->left;
		}
		return le;
	}

	if (right->left == 0) {
		right = right->right;
		ri->right = 0;
		return ri;
	}

	Node<T> *parent, *child;
	parent = right;
	child = right->left;
	while (child->left != 0) {
		parent = child;
		child = child->left;
	}
	parent->left = child->right;
	child->right = 0;
	return child;
}

template <class T>
void Node<T>::remove(T val) {
	Node<T> * succ, *old;
	if (val < value) {
		if (left != 0 && left->value == val) {
			old = left;
			succ = left->succesor();
			if (succ != 0) {
				succ->left = old->left;
				succ->right = old->right;
			}
			left = succ;
			delete old;
		} else {
			left->remove(val);
		}
	} else if (val > value) {
		if (right != 0 && right->value == val) {
			old = right;
			succ = right->succesor();
			if (succ != 0) {
				succ->left = old->left;
				succ->right = old->right;
			}
			right = succ;
			delete old;
		} else {
			right->remove(val);
		}
	}
}


template <class T>
void Node<T>::inorder(stringstream &aux) const {
	if (left != 0) {
		left->inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right->inorder(aux);
	}
}


template <class T>
void Node<T>::preorder(stringstream &aux) const {
	aux << value;
	if (left != 0) {
		aux << " ";
		left->preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right->preorder(aux);
	}
}


template <class T>
void Node<T>::postorder(stringstream &aux) const {
	if (left != 0) {
		left->postorder(aux);
	}
	if (right != 0) {
		right->postorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
}

template <class T>
void Node<T>::levelorder(stringstream &aux) const {
	queue<Node<T>*> q;
	q.push(const_cast<Node<T>*>(this));
	while (!q.empty()) {
		Node<T>* current = q.front();
		q.pop();
		if (current->left != 0) {
			q.push(current->left);
		}
		if (current->right != 0) {
			q.push(current->right);
		}
		if (aux.tellp() != 1) {
			aux << " ";
		}
		aux << current->value;
	}
}

template <class T>
int Node<T>::height() const {
	int leftHeight = 0;
	int rightHeight = 0;
	if (left != 0) {
		leftHeight = left->height();
	}
	if (right != 0) {
		rightHeight = right->height();
	}
	if (leftHeight > rightHeight) {
		return leftHeight + 1;
	} else {
		return rightHeight + 1;
	}
}

template <class T>
string Node<T>::ancestors(T val) const {
	stringstream aux;
	if (val < value) {
		if (left != 0) {
			if (left->value == val) {
				aux << value;
			} else {
				aux << value << " " << left->ancestors(val);
			}
		}
	} else if (val > value) {
		if (right != 0) {
			if (right->value == val) {
				aux << value;
			} else {
				aux << value << " " << right->ancestors(val);
			}
		}
	}
	return aux.str();
}	

template <class T>
int Node<T>::whatlevelamI(T val) const {
	if (val == value) {
		return 1;
	} else if (val < value) {
		if (left != 0) {
			return left->whatlevelamI(val) + 1;
		}
	} else if (val > value) {
		if (right != 0) {
			return right->whatlevelamI(val) + 1;
		}
	}
	return -1;
}



template <class T>
class BST {
private:
	Node<T> *root;

public:
	BST();
	bool empty() const;
	void add(T);
	bool find(T) const;
	void remove(T);
	string inorder() const;
	string preorder() const;
	string postorder() const;
	string levelorder() const;
	string visit() const;
	int height() const;
	int whatlevelamI(T) const;
	string ancestors(T) const;
};

template <class T>
BST<T>::BST() : root(0) {}


template <class T>
bool BST<T>::empty() const {
	return (root == 0);
}

template <class T>
void BST<T>::add(T val) {
	if (root != 0) {
		if (!root->find(val)) {
			root->add(val);
		}
	} else {
		root = new Node<T>(val);
	}
}


template <class T>
bool BST<T>::find(T val) const {
	if (root != 0) {
		return root->find(val);
	} else {
		return false;
	}
}

template <class T>
void BST<T>::remove(T val) {
	if (root != 0) {
		if (val == root->value) {
			Node<T> *succ = root->succesor();
			if (succ != 0) {
				succ->left = root->left;
				succ->right = root->right;
			}
			delete root;
			root = succ;
		} else {
			root->remove(val);
		}
	}
}


template <class T>
string BST<T>::inorder() const {
	stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
string BST<T>::preorder() const {
	stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
string BST<T>::postorder() const {
	stringstream aux;

	aux << "[";
	if (!empty()) {
		root->postorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
string BST<T>::levelorder() const {
	stringstream aux;

	aux << "[";
	if (!empty()) {
		root->levelorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
string BST<T>::visit() const {
	string aux = preorder() + "\n";
	aux += inorder() + "\n";
	aux += postorder() + "\n";
	aux += levelorder();
	return aux;
}

template <class T>
int BST<T>::height() const {
	return root->height();
}

template <class T>
int BST<T>::whatlevelamI(T val) const {
	return root->whatlevelamI(val);
}

template <class T>
string BST<T>::ancestors(T val) const {
	stringstream aux;

	aux << "[";
	if (!empty()&&root->find(val)) {
		aux << root->ancestors(val);
	}
	aux << "]";
	return aux.str();
}


#endif