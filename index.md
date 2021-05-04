# Generic Red Black Trees
### A generic implementation of Red Black Trees in C++
## By _Sai Eashwar K S, Monisha Chandra_

A red-black tree is a binary search tree with one extra bit of storage per node: its color, which can be either RED or BLACK. By constraining the way nodes can be colored on any path from the root to a leaf, red-black trees ensure that no such path is more than twice as long as any other, so that the tree is approximately balanced. 

Each node of the tree now contains the fields color, key, left, right, and parent.
A binary search tree is a red-black tree if it satisfies the following red-black properties:

1. Every node is either red or black.
2. Every leaf (NIL) is black.
3. If a node is red, then both its children are black.
4. Every simple path from a node to a descendant leaf contains the same number of black nodes.

### Documentation and execution info
[![readme.txt](https://www.iconspng.com/uploads/readme-document-icon/readme-document-icon.png)](https://github.com/SaiEashwarKS/Generic_RedBlackTree/blob/main/README.txt)

### RBT.h
```cpp
#ifndef RBT_H
#define RBT_H

#define DEBUG 0

#include <vector>
#include <queue>
#include <initializer_list>
using namespace std;

enum Colour
{
    black,
    red
};

template <typename T, typename Compare>
class RBT;

template <typename T>
class Node
{
private:
    T data_;
    Colour colour_;
    Node<T> *left_;
    Node<T> *right_;
    Node<T> *parent_;

    Node(T data);
    template<typename, typename >
    friend class RBT;
};

template <typename T, typename Compare = less<T>>
class RBT
{
private:
    Node<T> *root_;
    Compare compare_;
    Node<T> *bst_insert(T data);
    void bst_insert_util(Node<T> *temp, Node<T> *node);
    Node<T> *create_node(T data);
    void get_inorder_util(Node<T> *node, vector<T> *res) const;
    void get_postorder_util(Node<T> *node, vector<T> *res) const;
    void get_preorder_util(Node<T> *node, vector<T> *res) const;
    int height_util(Node<T> *node_ptr);
    static Node<T>* inorder_predecessor(Node<T> *node_ptr);
    static Node<T>* inorder_successor(Node<T> *node_ptr);
    int leaf_count_util(Node<T> *node_ptr);
    static Node<T> *max_subtree(Node<T> *node_ptr); //max of the subtree rooted by the node
    static Node<T> *min_subtree(Node<T> *node_ptr); //min of the subtree rooted by the node
    void print_level_order_util(Node<T> *node_ptr);
    void rebalance_insert(Node<T> *node_ptr);
    void rebalance_remove(Node<T> *node_ptr); //remove double black
    void remove_util(Node<T> *node_ptr);
    void rotate_left(Node<T> *node);
    void rotate_right(Node<T> *node);
    int size_util(Node<T> *node_ptr);
    Node<T> *succ_remove(Node<T> *node_ptr); //get successor while performing remove

public:
    class Iterator
    {
        private:
        Node<T>* iterator_;
        int is_reverse_iterator_;

        public:
        Iterator(Node<T> *node_ptr, int is_reverse = 0);
        operator bool() const;
        const T& operator*();
        bool operator==(const Iterator& rhs);
        bool operator!=(const Iterator& rhs);
        
        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);

        typedef T value_type;
		typedef const Node<T>& reference; 
		typedef const Node<T>* pointer; 
		typedef bidirectional_iterator_tag iterator_category;
    };

    ~RBT(); //dtor
    RBT();  //ctor
    RBT(const RBT<T, Compare> & rhs); //copy
    RBT(initializer_list<T> init_list); //braced-init-list
    template <typename InputIterator>
    RBT(InputIterator first, InputIterator last); //range

    Iterator begin() const;
    void delete_node(Node<T> *node);
    Iterator end() const;
    Iterator find(T data) const;
    vector<T> get_inorder() const;
    vector<T> get_postorder() const;
    vector<T> get_preorder() const;
    int height();
    void insert(T data);
    int leaf_count();
    Iterator max();
    Iterator min();
    RBT<T, Compare> &operator=(const RBT<T, Compare> &); //copy assignment
    template <typename T2, typename Compare2>
    friend RBT<T2, Compare2> &operator+(const RBT<T2, Compare2> &t1, const RBT<T2, Compare2> &t2);
    template <typename T2, typename Compare2>
    friend RBT<T2, Compare2> &operator-(const RBT<T2, Compare2> &t1, const RBT<T2, Compare2> &t2);
    void print_level_order();
    Iterator rbegin() const;
    void remove(T data);
    Iterator rend() const;
    int size();
};

//-----------Node methods
template <typename T>
Node<T>::Node(T data) : data_(data), colour_(red), left_(nullptr), right_(nullptr), parent_(nullptr)
{
}

//-----------RBT methods

        //-----------RBT private methods
template<typename T, typename Compare>
Node<T> *RBT<T, Compare>::bst_insert(T data)
{
    Node<T> *node_ptr = create_node(data);
    if (root_ == nullptr)
    {
        root_ = node_ptr;
    }
    else
    {
        bst_insert_util(root_, node_ptr);
    }
    return node_ptr;
}

template<typename T, typename Compare>
void RBT<T, Compare>::bst_insert_util(Node<T> *root, Node<T> *node)
{
    if (!compare_(node->data_, root->data_))
    {
        if (root->right_)
            bst_insert_util(root->right_, node);
        else
        {
            root->right_ = node;
            node->parent_ = root;
        }
    }
    else if (compare_(node->data_, root->data_))
    {
        if (root->left_)
            bst_insert_util(root->left_, node);
        else
        {
            root->left_ = node;
            node->parent_ = root;
        }
    }
}

template<typename T, typename Compare>
Node<T> *RBT<T, Compare>::create_node(T data)
{
    Node<T> *node = new Node<T>(data);
    return node;
}

template<typename T, typename Compare>
void RBT<T, Compare>::get_inorder_util(Node<T> *node, vector<T> *res) const
{
    if (node)
    {
        get_inorder_util(node->left_, res);
        res->push_back(node->data_);
        get_inorder_util(node->right_, res);
    }
}

template<typename T, typename Compare>
void RBT<T, Compare>::get_postorder_util(Node<T> *node, vector<T> *res) const
{
    if (node)
    {
        get_postorder_util(node->left_, res);
        get_postorder_util(node->right_, res);
        res->push_back(node->data_);
    }
}

template<typename T, typename Compare>
void RBT<T, Compare>::get_preorder_util(Node<T> *node, vector<T> *res) const
{
    if (node)
    {
        res->push_back(node->data_);
        get_preorder_util(node->left_, res);
        get_preorder_util(node->right_, res);
    }
}

template<typename T, typename Compare>
int RBT<T, Compare>::height_util(Node<T> *node_ptr)
{
    if(node_ptr == nullptr)
        return 0;
    int left_height = height_util(node_ptr->left_);
    int right_height = height_util(node_ptr->right_);
    return left_height > right_height ? left_height + 1 : right_height + 1;
}

template<typename T, typename Compare>
Node<T>* RBT<T, Compare>::inorder_predecessor(Node<T> *node_ptr)
{
    if(node_ptr == nullptr)
        return nullptr;
    if(node_ptr->left_)
        return max_subtree(node_ptr->left_);
    Node<T>* parent_ptr = node_ptr->parent_;
    //find a node which is a right child, return it's parent
    while(parent_ptr && node_ptr == parent_ptr->left_)
    {
        node_ptr = parent_ptr;
        parent_ptr = node_ptr->parent_;
    }
    return parent_ptr;
}

template<typename T, typename Compare>
Node<T>* RBT<T, Compare>::inorder_successor(Node<T> *node_ptr)
{
    if(node_ptr == nullptr)
        return nullptr;
    if(node_ptr->right_)
        return min_subtree(node_ptr->right_);
    Node<T>* parent_ptr = node_ptr->parent_;
    //find a node which is a left child, return it's parent
    while(parent_ptr && node_ptr == parent_ptr->right_)
    {
        node_ptr = parent_ptr;
        parent_ptr = node_ptr->parent_;
    }
    return parent_ptr;
}

template<typename T, typename Compare>
int RBT<T, Compare>::leaf_count_util(Node<T> *node_ptr)
{
    if(node_ptr == nullptr)
        return 0;
    if(node_ptr->left_ == nullptr && node_ptr->right_ == nullptr)
        return 1;
    return leaf_count_util(node_ptr->left_) + leaf_count_util(node_ptr->right_);
}

template<typename T, typename Compare>
Node<T> *RBT<T, Compare>::max_subtree(Node<T> *node_ptr)
{
    Node<T> *temp = node_ptr;
    while (temp->right_)
        temp = temp->right_;
    return temp;
}

template<typename T, typename Compare>
Node<T> *RBT<T, Compare>::min_subtree(Node<T> *node_ptr)
{
    Node<T> *temp = node_ptr;
    while (temp->left_)
        temp = temp->left_;
    return temp;
}

template<typename T, typename Compare>
void RBT<T, Compare>::print_level_order_util(Node<T> *node_ptr)
{
    if(node_ptr == nullptr)
        return;
    queue<Node<T>*> q;
    Node<T>* curr_node_ptr;
    q.push(node_ptr);
    while(!q.empty())
    {
        curr_node_ptr = q.front();
        q.pop();
        cout << curr_node_ptr->data_ << "\t";
        if(curr_node_ptr->left_)
            q.push(curr_node_ptr->left_);
        if(curr_node_ptr->right_)
            q.push(curr_node_ptr->right_);
    }
    cout << "\n";
}


template<typename T, typename Compare>
void RBT<T, Compare>::rebalance_insert(Node<T> *node_ptr)
{
    if (root_ == node_ptr)
    {
        #if DEBUG
                cout << "node is root\n";
                cout << "node : " << node_ptr->data_ << " colour : "<< node_ptr->colour_ << endl;
                cout << endl;
        #endif
        node_ptr->colour_ = black;
    }
    else
    {
        Node<T> *parent_ptr = node_ptr->parent_;
        if (parent_ptr->colour_ == black)
            return;
        Node<T> *grandparent_ptr = parent_ptr->parent_;
        Node<T> *uncle_ptr;
        if (parent_ptr == grandparent_ptr->left_)
        {
            uncle_ptr = grandparent_ptr->right_;
        }
        else
        {
            uncle_ptr = grandparent_ptr->left_;
        }
        if (uncle_ptr && uncle_ptr->colour_ == red)
        {
            #if DEBUG
                cout << "parent is red, uncle is black\n";
                cout << "node : " << node_ptr->data_ << " colour : "<< node_ptr->colour_ << endl;
                cout << "parent : " << parent_ptr->data_ << " colour : " << parent_ptr->colour_ << endl;
                cout << "grandparent : " << grandparent_ptr->data_ << " colour : " <<  grandparent_ptr->colour_ << endl;
                cout << endl;
            #endif
            parent_ptr->colour_ = black;
            uncle_ptr->colour_ = black;
            grandparent_ptr->colour_ = red;
            rebalance_insert(grandparent_ptr);
        }
        else //uncle is black
        {
            if (parent_ptr == grandparent_ptr->left_ && node_ptr == node_ptr->parent_->left_)
            // Left left case (parent left of grandparent, node left of parent)
            {
                #if DEBUG
                cout << "Performing right rotation (LL case)\n";
                cout << "node : " << node_ptr->data_ << " colour : "<< node_ptr->colour_ << endl;
                cout << "parent : " << parent_ptr->data_ << " colour : " << parent_ptr->colour_ << endl;
                cout << "grandparent : " << grandparent_ptr->data_ << " colour : " <<  grandparent_ptr->colour_ << endl;
                cout << endl;
                #endif
                rotate_right(grandparent_ptr);
                swap(grandparent_ptr->colour_, parent_ptr->colour_);
            }
            else if (parent_ptr == grandparent_ptr->left_ && node_ptr == node_ptr->parent_->right_)
            //left right case (parent left of grandparent, node right of parent)
            {
                #if DEBUG
                cout << "Performing right rotation (LR case)\n";
                cout << "node : " << node_ptr->data_ << " colour : "<< node_ptr->colour_ << endl;
                cout << "parent : " << parent_ptr->data_ << " colour : " << parent_ptr->colour_ << endl;
                cout << "grandparent : " << grandparent_ptr->data_ << " colour : " <<  grandparent_ptr->colour_ << endl;
                #endif
                rotate_left(parent_ptr);
                #if DEBUG
                cout << "Performing left rotation (LR case)\n";
                cout << "node : " << node_ptr->data_ << " colour : "<< node_ptr->colour_ << endl;
                cout << "parent : " << parent_ptr->data_ << " colour : " << parent_ptr->colour_ << endl;
                cout << "grandparent : " << grandparent_ptr->data_ << " colour : " <<  grandparent_ptr->colour_ << endl;
                cout << endl;
                #endif
                rotate_right(grandparent_ptr);
                swap(grandparent_ptr->colour_, node_ptr->colour_);
            }
            else if (parent_ptr == grandparent_ptr->right_ && node_ptr == node_ptr->parent_->right_)
            //right right case (parent right of grandparent, node right of parent)
            {
                #if DEBUG
                cout << "Performing left rotation (RR case)\n";
                cout << "node : " << node_ptr->data_ << " colour : "<< node_ptr->colour_ << endl;
                cout << "parent : " << parent_ptr->data_ << " colour : " << parent_ptr->colour_ << endl;
                cout << "grandparent : " << grandparent_ptr->data_ << " colour : " <<  grandparent_ptr->colour_ << endl;
                cout << endl;
                #endif
                rotate_left(grandparent_ptr);
                swap(grandparent_ptr->colour_, parent_ptr->colour_);
            }
            else
            //right left case (parent right of grandparent, node left of parent)
            {
                #if DEBUG
                cout << "Performing right rotation (RL case)\n";
                cout << "node : " << node_ptr->data_ << " colour : "<< node_ptr->colour_ << endl;
                cout << "parent : " << parent_ptr->data_ << " colour : " << parent_ptr->colour_ << endl;
                cout << "grandparent : " << grandparent_ptr->data_ << " colour : " <<  grandparent_ptr->colour_ << endl;
                #endif
                rotate_right(parent_ptr);
                #if DEBUG
                cout << "Performing left rotation (RL case)\n";
                cout << "node : " << node_ptr->data_ << " colour : "<< node_ptr->colour_ << endl;
                cout << "parent : " << parent_ptr->data_ << " colour : " << parent_ptr->colour_ << endl;
                cout << "grandparent : " << grandparent_ptr->data_ << " colour : " <<  grandparent_ptr->colour_ << endl;
                cout << endl;
                #endif
                rotate_left(grandparent_ptr);
                swap(grandparent_ptr->colour_, node_ptr->colour_);
            }
        }
    }
}

template<typename T, typename Compare>
void RBT<T, Compare>::rebalance_remove(Node<T> *node_ptr)
{
    if (node_ptr == root_)
    {
        return;
    }
    Node<T> *parent_ptr = node_ptr->parent_;
    Node<T> *sibling_ptr;
    if(node_ptr == parent_ptr->left_)
    {
        sibling_ptr = parent_ptr->right_;
    }
    else
    {
        sibling_ptr = parent_ptr->left_;
    }
    if(sibling_ptr == nullptr)
    {
        rebalance_remove(parent_ptr);
    }
    else
    {
        if(sibling_ptr->colour_ == red)
        {
            parent_ptr->colour_ = red;
            sibling_ptr->colour_ = black;
            if(sibling_ptr == parent_ptr->left_)
            {   
                rotate_right(parent_ptr);
            }
            else
            {
                rotate_left(parent_ptr);
            }
            rebalance_remove(node_ptr);
        }
        else
        {
            bool sib_has_red_child = ((sibling_ptr->left_ && sibling_ptr->left_->colour_== red)
                                    || sibling_ptr->right_ && sibling_ptr->right_->colour_ == red);
            if(sib_has_red_child)
            {
                if(sibling_ptr->left_ && sibling_ptr->left_->colour_ == red)
                {
                    if(sibling_ptr == parent_ptr->left_)
                    {
                        sibling_ptr->left_->colour_ = sibling_ptr->colour_;
                        sibling_ptr->colour_ = parent_ptr->colour_;
                        rotate_right(parent_ptr);
                    }
                    else
                    {
                        sibling_ptr->left_->colour_ = parent_ptr->colour_;
                        rotate_right(sibling_ptr);
                        rotate_left(parent_ptr);
                    }
                }
                else
                {
                    if(sibling_ptr == parent_ptr->left_)
                    {
                        sibling_ptr->right_->colour_ = sibling_ptr->colour_;
                        rotate_right(sibling_ptr);
                        rotate_right(parent_ptr);
                    }
                    else
                    {
                        sibling_ptr->right_->colour_ = sibling_ptr->colour_;
                        sibling_ptr->colour_ = parent_ptr->colour_;
                        rotate_left(parent_ptr);
                    }
                }
                parent_ptr->colour_ = black;
            }
            else //2 black children
            {
                sibling_ptr->colour_ = red;
                if(parent_ptr->colour_ = black)
                {
                    rebalance_remove(parent_ptr);
                }
                else
                {
                    parent_ptr->colour_ = black;
                }
            }
        }
    }
}

template<typename T, typename Compare>
void RBT<T, Compare>::remove_util(Node<T> *node_ptr)
{
    Node<T> *succ_ptr = succ_remove(node_ptr);
    bool succ_is_black = (succ_ptr == nullptr || succ_ptr->colour_ == black);
    bool node_is_black = (node_ptr->colour_ == black);
    bool both_are_black = succ_is_black && node_is_black;
    Node<T> *parent_ptr = node_ptr->parent_;

    if (succ_ptr == nullptr) //node_ptr is leaf
    {
        if (root_ == node_ptr)
        {
            root_ = nullptr;
        }
        else
        {
            if (both_are_black) //fix double black at node_ptr
            {
                rebalance_remove(node_ptr);
            }
            else //either succ_ptr or node_ptr is red
            {
                Node<T> *sibling_ptr;
                if (parent_ptr)
                {
                    if (node_ptr == parent_ptr->left_)
                        sibling_ptr = parent_ptr->right_;
                    else
                        sibling_ptr = parent_ptr->left_;
                }
                if (sibling_ptr != nullptr)
                {
                    sibling_ptr->colour_ = red;
                }
            }

            //delete node_ptr
            if (node_ptr == parent_ptr->left_)
                parent_ptr->left_ = nullptr;
            else
                parent_ptr->right_ = nullptr;
            delete node_ptr;
        }
        return;
    }

    if (node_ptr->left_ == nullptr || node_ptr->right_ == nullptr) //node_ptr has only one child
    {
        if (root_ == node_ptr)
        {
            //node_ptr is root; assign data of succ_ptr to node_ptr and delete succ_ptr
            node_ptr->data_ = succ_ptr->data_;
            node_ptr->left_ = node_ptr->right_ = nullptr;
            delete succ_ptr;
        }
        else
        {
            if (node_ptr == parent_ptr->left_)
                parent_ptr->left_ = succ_ptr;
            else
                parent_ptr->right_ = succ_ptr;
            delete node_ptr;
            succ_ptr->parent_ = parent_ptr;

            if (both_are_black) //fix double black at succ_ptr
            {
                rebalance_remove(succ_ptr);
            }
            else
            {
                succ_ptr->colour_ = black;
            }
        }
        return;
    }
    //node_ptr has both children
    //swap data with successor and delete the successor
    swap(node_ptr->data_, succ_ptr->data_);
    remove_util(succ_ptr);
}

template<typename T, typename Compare>
void RBT<T, Compare>::rotate_left(Node<T> *node)
{
    Node<T> *right_node = node->right_;
    node->right_ = right_node->left_;
    if (node->right_)
    {
        node->right_->parent_ = node;
    }
    right_node->parent_ = node->parent_;
    if (!node->parent_)
    {
        root_ = right_node;
    }
    else if (node == node->parent_->right_)
    {
        node->parent_->right_ = right_node;
    }
    else
    {
        node->parent_->left_ = right_node;
    }
    right_node->left_ = node;
    node->parent_ = right_node;
}

template<typename T, typename Compare>
void RBT<T, Compare>::rotate_right(Node<T> *node)
{
    Node<T> *left_node = node->left_;
    node->left_ = left_node->right_;
    if (node->left_)
    {
        node->left_->parent_ = node;
    }
    left_node->parent_ = node->parent_;
    if (!node->parent_)
    {
        root_ = left_node;
    }
    else if (node == node->parent_->left_)
    {
        node->parent_->left_ = left_node;
    }
    else
    {
        node->parent_->right_ = left_node;
    }
    left_node->right_ = node;
    node->parent_ = left_node;
}

template<typename T, typename Compare>
int RBT<T, Compare>::size_util(Node<T> *node_ptr)
{
    if(node_ptr)
    {
        return 1+size_util(node_ptr->left_)+size_util(node_ptr->right_);
    }
    else
        return 0;
}

template<typename T, typename Compare>
Node<T> *RBT<T, Compare>::succ_remove(Node<T> *node_ptr)
{
    //node_ptr has 2 children
    if (node_ptr->left_ != nullptr && node_ptr->right_ != nullptr)
    {
        return min_subtree(node_ptr->right_); //inorder successor
    }
    //node_ptr is leaf
    if (node_ptr->left_ == nullptr && node_ptr->right_ == nullptr)
    {
        return nullptr;
    }
    //mode_ptr has one child
    if (node_ptr->left_ == nullptr)
    {
        return node_ptr->right_;
    }
    return node_ptr->left_;
}

        //-----------RBT public methods
template <typename T, typename Compare>
RBT<T, Compare>::~RBT()
{
    if (root_)
    {
        delete_node(root_);
    }
    root_ = nullptr;
}

template <typename T, typename Compare>
RBT<T, Compare>::RBT() : root_(nullptr), compare_(Compare())
{
}

template <typename T, typename Compare>
RBT<T, Compare>::RBT(const RBT<T, Compare> &rhs) : root_(nullptr)
{
    for (T node : rhs)
        this->insert(node);
}

template <typename T, typename Compare>
template <typename InputIterator>
RBT<T, Compare>::RBT(InputIterator first, InputIterator last) : root_(nullptr), compare_(Compare())
{
    InputIterator it(first);
    while (it != last)
    {
        insert(*it);
        ++it;
    }
}

template<typename T, typename Compare>
RBT<T, Compare>::RBT(initializer_list<T> init_list) : RBT(init_list.begin(), init_list.end())
{}

template<typename T, typename Compare>
typename RBT<T, Compare>::Iterator RBT<T, Compare>::begin() const
{
    return Iterator(min_subtree(root_));
}

template <typename T, typename Compare>
void RBT<T, Compare>::delete_node(Node<T> *node)
{
    if (node)
    {
        delete_node(node->left_);
        delete_node(node->right_);
        delete node;
    }
}

template<typename T, typename Compare>
typename RBT<T, Compare>::Iterator RBT<T, Compare>::end() const
{
    return nullptr;
}

template<typename T, typename Compare>
typename RBT<T, Compare>::Iterator RBT<T, Compare>::find(T data) const
{
    Node<T> *node_ptr = root_;
    while (node_ptr)
    {
        if (node_ptr->data_ == data)
            return Iterator(node_ptr);
        if(compare_(data, node_ptr->data_))
            node_ptr =  node_ptr->left_;
        else
            node_ptr = node_ptr->right_;
    }
    return nullptr;
}

template<typename T, typename Compare>
vector<T> RBT<T, Compare>::get_inorder() const
{
    vector<T> res;
    if (root_)
    {
        get_inorder_util(root_, &res);
    }
    return res;
}

template<typename T, typename Compare>
vector<T> RBT<T, Compare>::get_postorder() const
{
    vector<T> res;
    if (root_)
    {
        get_postorder_util(root_, &res);
    }
    return res;
}

template<typename T, typename Compare>
vector<T> RBT<T, Compare>::get_preorder() const
{
    vector<T> res;
    if (root_)
    {
        get_preorder_util(root_, &res);
    }
    return res;
}

template<typename T, typename Compare>
int RBT<T, Compare>::height()
{
    return height_util(root_);
}

template<typename T, typename Compare>
void RBT<T, Compare>::insert(T data)
{
    auto node_iter = find(data);
    //cout << "find result : " << node_exists << "\n";
    if (node_iter)
        return;
    Node<T> *node_ptr = bst_insert(data);
    #if DEBUG
    cout << "node to be inserted : " << node_ptr->data_ << " colour:"<<node_ptr->colour_<<endl;
    #endif
    //cout << "bst insert done, node_ptr : " << node_ptr << "\n";
    rebalance_insert(node_ptr);
}

template<typename T, typename Compare>
int RBT<T, Compare>::leaf_count()
{
    return leaf_count_util(root_);
}

template<typename T, typename Compare>
typename RBT<T, Compare>::Iterator RBT<T, Compare>::max()
{
    return Iterator(max_subtree(root_));
}

template<typename T, typename Compare>
typename RBT<T, Compare>::Iterator RBT<T, Compare>::min()
{
    return Iterator(min_subtree(root_));
}

template<typename T, typename Compare>
RBT<T, Compare> &RBT<T, Compare>::operator=(const RBT<T, Compare> &rhs)
{
    if (this != &rhs)
    {
        RBT<T, Compare> temp(rhs); //copy ctor
        swap(temp.root_, root_);
    } //dtor called on temp
    return *this;
}

template<typename T, typename Compare>
RBT<T, Compare> &operator+(const RBT<T, Compare> &t1, const RBT<T, Compare> &t2)
{
    RBT<T, Compare> *res_tree = new RBT<T, Compare>(t1);
    for (auto node : t2)
        res_tree->insert(node);
    return *res_tree;
}

template<typename T, typename Compare>
RBT<T, Compare> &operator-(const RBT<T, Compare> &t1, const RBT<T, Compare> &t2)
{
    RBT<T, Compare> *res_tree = new RBT<T, Compare>(t1);
    for (auto node : t2)
        res_tree->remove(node);
    return *res_tree;
}

template<typename T, typename Compare>
void RBT<T, Compare>::print_level_order()
{
    print_level_order_util(root_);
}

template<typename T, typename Compare>
typename RBT<T, Compare>::Iterator RBT<T, Compare>::rbegin() const
{
    return Iterator(max_subtree(root_), 1);;
}

template<typename T, typename Compare>
void RBT<T, Compare>::remove(T data)
{
    if (root_ == nullptr)
        return;
    if (!find(data)) //node doesn't exist
        return;
    Node<T> *node_ptr = root_;
    while (node_ptr->data_ != data)
    {
        if (compare_(data, node_ptr->data_))
            node_ptr = node_ptr->left_;
        else
            node_ptr = node_ptr->right_;
    }
    remove_util(node_ptr);
}


template<typename T, typename Compare>
typename RBT<T, Compare>::Iterator RBT<T, Compare>::rend() const
{
    return Iterator(nullptr, 1);
}

template<typename T, typename Compare>
int RBT<T, Compare>::size()
{
    return size_util(root_);
}

//-------------Iterator functions
template<typename T, typename Compare>
RBT<T, Compare>::Iterator::Iterator(Node<T> *node_ptr, int is_reverse) : iterator_(node_ptr), is_reverse_iterator_(is_reverse)
{};

template<typename T, typename Compare>
RBT<T, Compare>::Iterator::operator bool() const
{
    return iterator_ != nullptr;
}

template<typename T, typename Compare>
const T& RBT<T, Compare>::Iterator::operator*()
{
    return iterator_->data_;
}

template<typename T, typename Compare>
typename RBT<T, Compare>::Iterator& RBT<T, Compare>::Iterator::operator++()
{
    if(is_reverse_iterator_)
        iterator_ = inorder_predecessor(iterator_);
    else
        iterator_ = inorder_successor(iterator_);
    return *this;
}

template<typename T, typename Compare>
typename RBT<T, Compare>::Iterator RBT<T, Compare>::Iterator::operator++(int)
{
    Iterator temp(*this);
    ++(*this);
    return temp;
}

template<typename T, typename Compare>
typename RBT<T, Compare>::Iterator& RBT<T, Compare>::Iterator::operator--()
{
    if(is_reverse_iterator_)
        iterator_ = inorder_successor(iterator_);
    else
        iterator_ = inorder_predecessor(iterator_);
    return *this;
}

template<typename T, typename Compare>
typename RBT<T, Compare>::Iterator RBT<T, Compare>::Iterator::operator--(int)
{
    Iterator temp(*this);
    --(*this);
    return temp;
}

template<typename T, typename Compare>
bool RBT<T, Compare>::Iterator::operator==(const typename RBT<T, Compare>::Iterator& rhs)
{
    return iterator_==rhs.iterator_;
}

template<typename T, typename Compare>
bool RBT<T, Compare>::Iterator::operator!=(const typename RBT<T, Compare>::Iterator& rhs)
{
    return !(*this==rhs);
}

#endif
```

## Contact me


| Handle | Link |
| ------ | ------ |
| GitHub | https://github.com/SaiEashwarKS |
| Linked | https://www.linkedin.com/in/sai-eashwar-k-s|
| Email | saieashwar.ks@gmail.com |
