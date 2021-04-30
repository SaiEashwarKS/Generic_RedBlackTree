#include<iostream>
#include"node.h"
using namespace std;

template<typename T>
Node<T>::Node(T data)
{
	this->data = data;
	this->colour = black;
	this->left = this->right = this->parent = nullptr;
}