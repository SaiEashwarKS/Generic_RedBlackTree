#ifndef RBT_H
#define RBT_H

#include <vector>
using namespace std;

enum Colour
{
    black,
    red
};

template <typename T>
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

    friend class RBT<T>;
};

template <typename T>
class RBT
{
private:
    Node<T> *root_;
    void get_inorder_util(Node<T> *, vector<T> *) const;
    void get_preorder_util(Node<T> *, vector<T> *) const;
    void get_postorder_util(Node<T> *, vector<T> *) const;
    Node<T> *create_node(T data);
    Node<T> *bst_insert(T data);
    void bst_insert_util(Node<T> *temp, Node<T> *node);
    void rebalance_insert(Node<T> *root, Node<T> *node_ptr);
    void rotate_left(Node<T> *node);
    void rotate_right(Node<T> *node);
    void remove_util(Node<T> *node_ptr);
    void rebalance_remove(Node<T> *node_ptr); //remove double black
    Node<T> *succ_remove(Node<T> *node_ptr);
    Node<T> *max_subtree(Node<T> *node_ptr); //max of the subtree rooted by the node
    Node<T> *min_subtree(Node<T> *node_ptr); //min of the subtree rooted by the node
    int height_util(Node<T> *node_ptr);
    int leaf_count_util(Node<T> *node_ptr);

public:
    RBT();  //ctor
    ~RBT(); //dtor
    void delete_node(Node<T> *node);
    RBT(const RBT<T> &); //copy
    template <typename InputIterator>
    RBT(InputIterator first, InputIterator last); //range
    RBT<T> &operator=(const RBT<T> &);            //copy assn
    void insert(T data);
    void remove(T data);
    vector<T> get_inorder() const;
    vector<T> get_preorder() const;
    vector<T> get_postorder() const;
    bool search(T data) const;
    template <typename T2>
    friend RBT<T2> &operator+(const RBT<T2> &t1, const RBT<T2> &t2);
    T max();
    T min();
    int height();
    int leaf_count();
};

//-----------Node methods
template <typename T>
Node<T>::Node(T data) : data_(data), colour_(red), left_(nullptr), right_(nullptr), parent_(nullptr)
{
}

//-----------RBT methods
template <typename T>
RBT<T>::RBT() : root_(nullptr)
{
}

template <typename T>
RBT<T>::~RBT()
{
    if (root_)
    {
        delete_node(root_);
    }
    root_ = nullptr;
}

template <typename T>
void RBT<T>::delete_node(Node<T> *node)
{
    if (node)
    {
        delete_node(node->left_);
        delete_node(node->right_);
        delete node;
    }
}

template <typename T>
RBT<T>::RBT(const RBT<T> &rhs) : root_(nullptr)
{
    vector<T> preorder_vector = rhs.get_preorder();
    for (auto node : preorder_vector)
        this->insert(node);
}

template <typename T>
template <typename InputIterator>
RBT<T>::RBT(InputIterator first, InputIterator last) : root_(nullptr)
{
    InputIterator it(first);
    while (it != last)
    {
        insert(*it);
        ++it;
    }
}

template <typename T>
RBT<T> &RBT<T>::operator=(const RBT<T> &rhs)
{
    if (this != &rhs)
    {
        RBT<T> temp(rhs);
        swap(temp.root_, root_);
    } //dtor called on temp
    return *this;
}

template <typename T>
RBT<T> &operator+(const RBT<T> &t1, const RBT<T> &t2)
{
    RBT<T> *res_tree = new RBT<T>(t1);
    vector<T> preorder_vector = t2.get_preorder();
    for (auto node : preorder_vector)
        res_tree->insert(node);
    return *res_tree;
}

template <typename T>
Node<T> *RBT<T>::create_node(T data)
{
    Node<T> *node = new Node<T>(data);
    return node;
}

template <typename T>
void RBT<T>::bst_insert_util(Node<T> *temp, Node<T> *node)
{
    if (node->data_ > temp->data_)
    {
        if (temp->right_)
            bst_insert_util(temp->right_, node);
        else
        {
            temp->right_ = node;
            node->parent_ = temp;
        }
    }
    else if (node->data_ < temp->data_)
    {
        if (temp->left_)
            bst_insert_util(temp->left_, node);
        else
        {
            temp->left_ = node;
            node->parent_ = temp;
        }
    }
}

template <typename T>
Node<T> *RBT<T>::bst_insert(T data)
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

template <typename T>
bool RBT<T>::search(T data) const
{
    Node<T> *node = root_;
    while (node)
    {
        if (node->data_ == data)
            return true;
        node = data < node->data_ ? node->left_ : node->right_;
    }
    return false;
}

template <typename T>
void RBT<T>::rotate_right(Node<T> *node)
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

template <typename T>
void RBT<T>::rotate_left(Node<T> *node)
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

template <typename T>
void RBT<T>::rebalance_insert(Node<T> *root, Node<T> *node_ptr)
{
    if (root == node_ptr)
    {
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
            parent_ptr->colour_ = black;
            uncle_ptr->colour_ = black;
            grandparent_ptr->colour_ = red;
            rebalance_insert(root, grandparent_ptr);
        }
        else //uncle is black
        {
            if (parent_ptr == grandparent_ptr->left_ && node_ptr == node_ptr->parent_->left_)
            // Left left case (parent left of grandparent, node left of parent)
            {
                rotate_right(grandparent_ptr);
                swap(grandparent_ptr->colour_, parent_ptr->colour_);
            }
            else if (parent_ptr == grandparent_ptr->left_ && node_ptr == node_ptr->parent_->right_)
            //left right case (parent left of grandparent, node right of parent)
            {
                rotate_left(parent_ptr);
                rotate_right(grandparent_ptr);
                swap(grandparent_ptr->colour_, node_ptr->colour_);
            }
            else if (parent_ptr == grandparent_ptr->right_ && node_ptr == node_ptr->parent_->right_)
            //right right case (parent right of grandparent, node right of parent)
            {
                rotate_left(grandparent_ptr);
                swap(grandparent_ptr->colour_, parent_ptr->colour_);
            }
            else
            //right left case (parent right of grandparent, node left of parent)
            {
                rotate_right(parent_ptr);
                rotate_left(grandparent_ptr);
                swap(grandparent_ptr->colour_, node_ptr->colour_);
            }
        }
    }
}

template <typename T>
void RBT<T>::insert(T data)
{
    bool node_exists = search(data);
    //cout << "search result : " << node_exists << "\n";
    if (node_exists)
        return;
    Node<T> *node_ptr = bst_insert(data);
    //cout << "bst insert done, node_ptr : " << node_ptr << "\n";
    rebalance_insert(root_, node_ptr);
}

template <typename T>
void RBT<T>::get_inorder_util(Node<T> *node, vector<T> *res) const
{
    if (node)
    {
        get_inorder_util(node->left_, res);
        res->push_back(node->data_);
        get_inorder_util(node->right_, res);
    }
}

template <typename T>
vector<T> RBT<T>::get_inorder() const
{
    vector<T> res;
    if (root_)
    {
        get_inorder_util(root_, &res);
    }
    return res;
}

template <typename T>
void RBT<T>::get_preorder_util(Node<T> *node, vector<T> *res) const
{
    if (node)
    {
        res->push_back(node->data_);
        get_preorder_util(node->left_, res);
        get_preorder_util(node->right_, res);
    }
}

template <typename T>
vector<T> RBT<T>::get_preorder() const
{
    vector<T> res;
    if (root_)
    {
        get_preorder_util(root_, &res);
    }
    return res;
}

template <typename T>
void RBT<T>::get_postorder_util(Node<T> *node, vector<T> *res) const
{
    if (node)
    {
        get_postorder_util(node->left_, res);
        get_postorder_util(node->right_, res);
        res->push_back(node->data_);
    }
}

template <typename T>
vector<T> RBT<T>::get_postorder() const
{
    vector<T> res;
    if (root_)
    {
        get_postorder_util(root_, &res);
    }
    return res;
}

template <typename T>
Node<T> *RBT<T>::max_subtree(Node<T> *node_ptr)
{
    Node<T> *temp = node_ptr;
    while (temp->right_)
        temp = temp->right_;
    return temp;
}

template <typename T>
T RBT<T>::max()
{
    return max_subtree(root_)->data_;
}

template <typename T>
Node<T> *RBT<T>::min_subtree(Node<T> *node_ptr)
{
    Node<T> *temp = node_ptr;
    while (temp->left_)
        temp = temp->left_;
    return temp;
}

template <typename T>
T RBT<T>::min()
{
    return min_subtree(root_)->data_;
}

template <typename T>
void RBT<T>::remove(T data)
{
    if (root_ == nullptr)
        return;
    if (!search(data)) //node doesn't exist
        return;
    Node<T> *node_ptr = root_;
    while (node_ptr->data_ != data)
    {
        if (data < node_ptr->data_)
            node_ptr = node_ptr->left_;
        else
            node_ptr = node_ptr->right_;
    }
    remove_util(node_ptr);
}

template <typename T>
Node<T> *RBT<T>::succ_remove(Node<T> *node_ptr)
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

template <typename T>
void RBT<T>::remove_util(Node<T> *node_ptr)
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

template <typename T>
void RBT<T>::rebalance_remove(Node<T> *node_ptr)
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

template<typename T>
int RBT<T>::height_util(Node<T> *node_ptr)
{
    if(node_ptr == nullptr)
        return 0;
    int left_height = height_util(node_ptr->left_);
    int right_height = height_util(node_ptr->right_);
    return left_height > right_height ? left_height + 1 : right_height + 1;
}

template<typename T>
int RBT<T>::height()
{
    return height_util(root_);
}

template<typename T>
int RBT<T>::leaf_count_util(Node<T> *node_ptr)
{
    if(node_ptr == nullptr)
        return 0;
    if(node_ptr->left_ == nullptr && node_ptr->right_ == nullptr)
        return 1;
    return leaf_count_util(node_ptr->left_) + leaf_count_util(node_ptr->right_);
}

template<typename T>
int RBT<T>::leaf_count()
{
    return leaf_count_util(root_);
}

#endif