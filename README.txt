Files : 
- rbt.h :
    - contains declarations and definitions of the necessarry classes for the red black tree and their methods
- client.cpp :
    - contains the client code
- make.mk : 
    - makefile containing the commands to execute the programs

----------------------------

Commands to run to execute the files :
- Linux : 
    $ make -f make.mk
    $ ./a.out

    OR

    compile client.cpp and run the executable

- Windows and Mac:
    compile client.cpp and run the executable

----------------------------

The interface and intent of the classes and their functions :

enum Colour :
    - has two colours : black and red

----------------------------

class Node :
- Template parameters : 
    - T : datatype of the data that is to be stored in the tree

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
            - single argument constructor
            - creates a new node and initialises data_ to data, the pointers to nullptr and the colour_ to red

- Class RBT is a friend of class Node.

----------------------------

class RBT :
- Template parameters :
    - T : datatype of the data that is to be stored in the tree
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
        - calls the constructor of Node class to create a new node and returns a pointer to the new node
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
    - Public methods :
        - Constructors : (explicitly defined)
            - Iterator(Node<T> *node_ptr)
                - single argument constructor
                - initialises iterator_ to node_ptr
        - operator bool() const :
            - overload bool typecasting
            - returns true if the iterator_ is not nullptr
        - const T& operator*() :
            - overload dereferencing
            - returns the data pointed to by iterator_
        - operator==(const Iterator& rhs) : bool
            - return true if both the iterators point to the same node
        - operator!=(const Iterator& rhs) : bool
            - return negation of operator==
        - Iterator& operator++() :
            - pre increment
            - return inorder successor
        - Iterator operator++(int)
            - post increment
            - perform increment and return the old value
        - Iterator& operator() :
            - pre decrement
            - return inorder predecessor
        - Iterator operator--(int)
            - post decrement
            - perform decrement and return the old value
        
    - Constructors : (explicitly defined)
        - RBT()
            - initialises root_ to nullptr and instantiates Compare 
        - RBT(const RBT<T, Compare> & rhs) 
            - copy constructor
            - initialises root_ to nullptr
            - iterate through rhs and insert its nodes
        - RBT(initializer_list<T> init_list)
            - braced initializer list constructor
            - calls range constructor by passing the begin and end of init_list as parameters
        - RBT(InputIterator first, InputIterator last)
            - range constructor
            - template parameters : InputIterator
            - initialises root_ to nullptr
            - iterate using the iterators and insert the nodes pointed to by them
    
    - Destructor : 
        - ~RBT()
            - calls delete_node on root_

    - begin() const : Iterator
        - return iterator to the minimum node of the tree
    - delete_node(Node<T>* node) : void
        - deletes nodes rooted by node
    - end() const : Iterator
        - return nullptr
    - find(T data) : Iterator
        - if data is present, return iterator to the node containing the data, else return nullptr
    - get_inorder() const : vector<T>
        - returns a vector of data contained, in inorder
    - get_postorder() const : vector<T>
        - returns a vector of data contained, in postorder
    - get_preorder() const : vector<T>
        - returns a vector of data contained, in preorder
    - height() : int
        - return height of the tree
    - insert(T data) : void
        - insert data into the tree
    - leaf_count() : int
        - return the number of leaves in the tree
    - max() : Iterator
        - returns Iterator to the max node in the tree
    - min() : Iterator
        - returns Iterator to the min node in the tree
    - operator+(const RBT<T, Compare>& rhs) : RBT<T, Compare>&
        - copies the nodes from one tree to another
        - return the reference to the tree thats calling the function
    - operator+(const RBT<T, Compare> &t1, const RBT<T, Compare> &t2) : RBT<T, Compare>
        - creates a new tree with the nodes of both t1 and t2 (in the same order)
        - returns reference to this tree
    - operator-(const RBT<T, Compare> &t1, const RBT<T, Compare> &t2) : RBT<T, Compare>
        - creates a new tree with nodes of t1 and from this tree, removes the nodes of t2
        - returns reference to this tree
    - print_level_order() : void
        - prints the data in level order
    - remove(T data) void
        - remove the node containing data
    - size() : int  
        - return the number of nodes in the tree
     
