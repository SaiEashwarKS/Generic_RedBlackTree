#ifndef RBT_H
#define RBT_H

#include"node.h"
#include<vector>
using namespace std;


template<typename T>
class RBT
{	
	private:
	Node<T> *root;
	void get_inorder_util(Node<T>*, vector<T>*);
	Node<T>* create_node(T data);
	void bst_insert(T data);
    void bst_insert_util(Node<T>* temp, Node<T>* node);

	public:
	RBT();
	vector<T> get_inorder();
};

#endif