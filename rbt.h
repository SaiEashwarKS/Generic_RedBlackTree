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
	void get_inorder_util(Node<T>*, vector<T>*) const;
	void get_preorder_util(Node<T>*, vector<T>*) const;
	void get_postorder_util(Node<T>*, vector<T>*) const;
	Node<T>* create_node(T data);
	void bst_insert(T data);
	void bst_insert_util(Node<T>* temp, Node<T>* node);

	public:
	RBT(); //ctor
	~RBT(); //dtor
	void delete_node(Node<T>* node);
	RBT(const RBT<T>&); //copy
	template<typename InputIterator>
	RBT(InputIterator first, InputIterator last); //range
    RBT<T>& operator=(const RBT<T>&); //copy assn
	void insert(T data);
	vector<T> get_inorder() const;
	vector<T> get_preorder() const;
	vector<T> get_postorder() const;
};


//-----------Node methods
template<typename T>
Node<T>::Node(T data) : data_(data), colour_(black), left_(nullptr), right_(nullptr), parent_(nullptr)
{}


//-----------RBT methods
template<typename T>
RBT<T>::RBT() : root_(nullptr)
{}

template<typename T>
RBT<T>::~RBT()
{
	if(root_)
	{
		delete_node(root_);
	}
	root_ = nullptr;
}

template<typename T>
void RBT<T>::delete_node(Node<T> *node)
{
	if(node)
	{
		delete_node(node->left_);
		delete_node(node->right_);
		delete node;
	}
}

template<typename T>
RBT<T>::RBT(const RBT<T>& rhs) : root_(nullptr)
{
	vector<T> preorder_vector = rhs.get_preorder();
	for(auto node : preorder_vector)
		this->insert(node);
}

template<typename T>
template<typename InputIterator>
RBT<T>::RBT(InputIterator first, InputIterator last) : root_(nullptr)
{
	InputIterator it(first);
	while(it != last)
	{
		insert(*it);
		++it;
	}
}

template<typename T>
RBT<T>& RBT<T>::operator=(const RBT<T>& rhs)
{
    if(this != &rhs)
    {
        RBT<T> temp(rhs);
        swap(temp.root_, root_);
    } //dtor called on temp
    return *this;
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
	if(node->data_ > temp->data_)
	{
		if(temp->right_)
			bst_insert_util(temp->right_, node);
		else
			temp->right_ = node;
	}
	else if(node->data_ < temp->data_)
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
void RBT<T>::get_inorder_util(Node<T>* node, vector<T>* res) const
{
	if(node)
	{
		get_inorder_util(node->left_, res);
		res->push_back(node->data_);
		get_inorder_util(node->right_, res);
	}
}

template<typename T>
vector<T> RBT<T>::get_inorder() const
{
	vector<T> res;
	if(root_)
	{
		get_inorder_util(root_, &res);
	}
	return res;
}

template<typename T>
void RBT<T>::get_preorder_util(Node<T>* node, vector<T>* res) const
{
	if(node)
	{
		res->push_back(node->data_);
		get_preorder_util(node->left_, res);
		get_preorder_util(node->right_, res);
	}
}

template<typename T>
vector<T> RBT<T>::get_preorder() const
{
	vector<T> res;
	if(root_)
	{
		get_preorder_util(root_, &res);
	}
	return res;
}

template<typename T>
void RBT<T>::get_postorder_util(Node<T>* node, vector<T>* res) const
{
	if(node)
	{
		get_postorder_util(node->left_, res);
		get_postorder_util(node->right_, res);
		res->push_back(node->data_);
	}
}

template<typename T>
vector<T> RBT<T>::get_postorder() const
{
	vector<T> res;
	if(root_)
	{
		get_postorder_util(root_, &res);
	}
	return res;
}

#endif
