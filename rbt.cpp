#include<iostream>

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
	
	friend class RBT<T>;
};

template<typename T>
class RBT
{	
	private:
	Node<T> *root;
	
	public:
	RBT();
};

template<typename T>
RBT<T>::RBT()
{
	this->root = nullptr;
}


int main()
{
	RBT<int> tree;
	return 0;
}
