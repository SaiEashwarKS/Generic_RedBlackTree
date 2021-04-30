#ifndef NODE_H
#define NODE_H

using namespace std;
enum Colour {black, red};

template<typename T>
class RBT;

template<typename T>
class Node
{
	private:
	T data;
	Colour colour;
	Node<T> *left;
	Node<T> *right; 
	Node<T> *parent;

    Node(T data);
	
	friend class RBT<T>;
};

#endif