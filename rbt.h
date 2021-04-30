#ifndef RBT_H
#define RBT_H

#include<vector>
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

template<typename T>
class RBT
{	
	private:
	Node<T> *root;
	void get_inorder_util(Node<T>*, vector<T>*);
    void get_preorder_util(Node<T>*, vector<T>*);
    void get_postorder_util(Node<T>*, vector<T>*);
	Node<T>* create_node(T data);
	void bst_insert(T data);
    void bst_insert_util(Node<T>* temp, Node<T>* node);

	public:
	RBT();
    void insert(T data);
	vector<T> get_inorder();
    vector<T> get_preorder();
    vector<T> get_postorder();
};


//-----------Node methods
template<typename T>
Node<T>::Node(T data)
{
	this->data = data;
	this->colour = black;
	this->left = this->right = this->parent = nullptr;
}


//-----------RBT methods
template<typename T>
RBT<T>::RBT()
{
	this->root = nullptr;
}

template<typename T>
Node<T>* RBT<T>::create_node(T data)
{
	Node<T>* node = new Node<T>(data);
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
void RBT<T>::insert(T data)
{
    bst_insert(data);
}

template<typename T>
void RBT<T>::get_inorder_util(Node<T>* node, vector<T>* res)
{
	if(node)
	{
		get_inorder_util(node->left, res);
		res->push_back(node->data);
		get_inorder_util(node->right, res);
	}
}

template<typename T>
vector<T> RBT<T>::get_inorder()
{
	vector<T> res;
	if(root)
	{
		get_inorder_util(root, &res);
	}
	return res;
}

template<typename T>
void RBT<T>::get_preorder_util(Node<T>* node, vector<T>* res)
{
	if(node)
	{
		res->push_back(node->data);
		get_preorder_util(node->left, res);
		get_preorder_util(node->right, res);
	}
}

template<typename T>
vector<T> RBT<T>::get_preorder()
{
	vector<T> res;
	if(root)
	{
		get_preorder_util(root, &res);
	}
	return res;
}

template<typename T>
void RBT<T>::get_postorder_util(Node<T>* node, vector<T>* res)
{
	if(node)
	{
		get_postorder_util(node->left, res);
		get_postorder_util(node->right, res);
		res->push_back(node->data);
	}
}

template<typename T>
vector<T> RBT<T>::get_postorder()
{
	vector<T> res;
	if(root)
	{
		get_postorder_util(root, &res);
	}
	return res;
}

#endif