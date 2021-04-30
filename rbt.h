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
	T data_;
	Colour colour_;
	Node<T> *left_;
	Node<T> *right_; 
	Node<T> *parent_;

    Node(T data);
	
	friend class RBT<T>;
};

template<typename T>
class RBT
{	
	private:
	Node<T> *root_;
	void get_inorder_util(Node<T>*, vector<T>*);
    void get_preorder_util(Node<T>*, vector<T>*);
    void get_postorder_util(Node<T>*, vector<T>*);
	Node<T>* create_node(T data);
	void bst_insert(T data);
    void bst_insert_util(Node<T>* temp, Node<T>* node);

	public:
	RBT();
    template<typename InputIterator>
    RBT(InputIterator first, InputIterator last);
    void insert(T data);
	vector<T> get_inorder();
    vector<T> get_preorder();
    vector<T> get_postorder();
};


//-----------Node methods
template<typename T>
Node<T>::Node(T data) : data_(data), colour_(black), left_(nullptr), right_(nullptr), parent_(nullptr)
{}


//-----------RBT methods
template<typename T>
RBT<T>::RBT()
{
	this->root_ = nullptr;
}

template<typename T>
template<typename InputIterator>
RBT<T>::RBT(InputIterator first, InputIterator last)
{
    root_ = nullptr;
    InputIterator it(first);
    while(it != last)
    {
        insert(*it);
        ++it;
    }
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
	int dataIsGreater = node->data_ > temp->data_;
	if(dataIsGreater)
	{
		if(temp->right_)
			bst_insert_util(temp->right_, node);
		else
			temp->right_ = node;
	}
	else
	{
		if(temp->left_)
			bst_insert_util(temp->left_, node);
		else
			temp->left_ = node;
	}
}

template<typename T>
void RBT<T>::bst_insert(T data)
{
	Node<T>* node = create_node(data);
	if(root_ == nullptr)
		root_ = node;
	else
	{
		bst_insert_util(root_, node);
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
		get_inorder_util(node->left_, res);
		res->push_back(node->data_);
		get_inorder_util(node->right_, res);
	}
}

template<typename T>
vector<T> RBT<T>::get_inorder()
{
	vector<T> res;
	if(root_)
	{
		get_inorder_util(root_, &res);
	}
	return res;
}

template<typename T>
void RBT<T>::get_preorder_util(Node<T>* node, vector<T>* res)
{
	if(node)
	{
		res->push_back(node->data_);
		get_preorder_util(node->left_, res);
		get_preorder_util(node->right_, res);
	}
}

template<typename T>
vector<T> RBT<T>::get_preorder()
{
	vector<T> res;
	if(root_)
	{
		get_preorder_util(root_, &res);
	}
	return res;
}

template<typename T>
void RBT<T>::get_postorder_util(Node<T>* node, vector<T>* res)
{
	if(node)
	{
		get_postorder_util(node->left_, res);
		get_postorder_util(node->right_, res);
		res->push_back(node->data_);
	}
}

template<typename T>
vector<T> RBT<T>::get_postorder()
{
	vector<T> res;
	if(root_)
	{
		get_postorder_util(root_, &res);
	}
	return res;
}

#endif