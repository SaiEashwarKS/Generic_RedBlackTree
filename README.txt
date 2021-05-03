This document explains the interface and intent of the classes and their functions.

Colour is an enumeration and has two colours : black and red

----------------------------

class Node :
- Template parameters : 
    - T : data type of the data that is to be stored in the tree

- Private fields :
    - data_ : T
        - the data that is to be stored in the tree
    - colour_ : Colour
        - colour of the node
    - left_ : Node<T>*
        - pointer to the left child of the node
    - right_ : Node<T>*
        - pointer to the right child of the node
    - parent_ : Node<T>*
        - pointer to the parent of the node

- Private methods :
    - Constructors : (explicitly defined)
        - Node(T data)
            - single value constructor
            - creates a new node and initialises data_ to data, the pointers to nullptr and the colour_ to red

- Class RBT is a friend of class Node.

----------------------------

class RBT :
- Template parameters :
    - T : data type of the data that is to be stored in the tree
    - Compare : functor class which has operator() overloaded to provide custom predicate to compare two nodes
        - default type : less<T>

- Private fields :
    - root_ : Node<T>*
        - points to the root of the tree        
    - compare_ : Compare
        - functor which will be used as a predicate to compare two nodes

- Private methods :
    - bst_insert(T data) : Node<T>*
        - initialises BST (Binary Search Tree) insertion of the node and return a pointer to the inserted node
    - bst_insert_util(Node<T>* root, Node<T>* node) : void
        - performs BST insertion on the node to the tree rooted by root
    - create_node : Node<T>*
        - calls the constructor of Node class to create a new node and returns a pointre to the new node
    - get_inorder_util(Node<T> *node, vector<T> *res) : void 
        - pushes the data in nodes to res in inorder
    - get_postorder_util(Node<T> *node, vector<T> *res) : void 
        - pushes the data in nodes to res in postorder
    - get_preorder_util(Node<T> *node, vector<T> *res) : void 
        - pushes the data in nodes to res in preorder
    - 


- Public fields :
    - class Iterator :
        - defines the iterator for class RBT
    - Private fields :
        - iterator_ : Node<T>*
            : an iterator that points to a node in the tree