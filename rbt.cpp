#include<iostream>
#include<vector>
#include"rbt.h"
using namespace std;

template<typename T>
RBT<T>::RBT()
{
	this->root = nullptr;
}

template<typename T>
Node<T>* RBT<T>::create_node(T data)
{
	Node<T>* node = new Node(data);
	return node;
}

template<typename T>
void RBT<T>::bst_insert_util(Node<T>* temp, Node<T>* node)
{
	int dataIsGreater = node->data > temp->data;
	if(dataIsGreater)
	{
		if(temp->right)
			bst_insert_util(temp->right, node);
		else
			temp->right = node;
	}
	else
	{
		if(temp->left)
			bst_insert_util(temp->left, node);
		else
			temp->left = node;
	}
}

template<typename T>
void RBT<T>::bst_insert(T data)
{
	Node<T>* node = create_node(data);
	if(root == nullptr)
		root = node;
	else
	{
		bst_insert_util(root, node);
	}
}

template<typename T>
void RBT<T>::get_inorder_util(Node<T>* node, vector<T>* res)
{
	if(node)
	{
		get_inorder_util(node->left);
		res->push_back(node->data);
		get_inorder_util(node->right);
	}
}

template<typename T>
vector<T> RBT<T>::get_inorder()
{
	vector<T> res;
	if(root)
	{
		get_inorder_util(root, res);
	}
	return res;
}

template<typename T>
void RBT<T>::get_preorder_util(Node<T>* node, vector<T>* res)
{
	if(node)
	{
		res->push_back(node->data);
		get_preorder_util(node->left);
		get_preorder_util(node->right);
	}
}

template<typename T>
vector<T> RBT<T>::get_preorder()
{
	vector<T> res;
	if(root)
	{
		get_preorder_util(root, res);
	}
	return res;
}

template<typename T>
void RBT<T>::get_preorder_util(Node<T>* node, vector<T>* res)
{
	if(node)
	{
		get_postorder_util(node->left);
		get_postorder_util(node->right);
		res->push_back(node->data);
	}
}

template<typename T>
vector<T> RBT<T>::get_postorder()
{
	vector<T> res;
	if(root)
	{
		get_postorder_util(root, res);
	}
	return res;
}