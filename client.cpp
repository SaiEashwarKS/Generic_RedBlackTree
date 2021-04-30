#include<iostream>
#include<vector>

#include"rbt.h"
using namespace std;

int main()
{
    #if 0
	RBT<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(50);
    tree.insert(40);
    vector<int> v = tree.get_inorder();
    for(auto e: v)
    {
        cout << e << "\t";
    }
    cout << "\n";
    v = tree.get_preorder();
    for(auto e: v)
    {
        cout << e << "\t";
    }
    cout << "\n";
    v = tree.get_postorder();
    for(auto e: v)
    {
        cout << e << "\t";
    }
    cout << "\n";
    #endif

    //RBT<int> tree {10, 30, 50, 20};


    #if 1
    vector<int>v{10, 30, 20, 50, 40};
    RBT<int> tree(v.begin(), v.end());
    vector<int> v2 = tree.get_inorder();
    for(auto e: v2)
    {
        cout << e << "\t";
    }
    cout << "\n";
    #endif
	return 0;
}