#include<iostream>
#include<vector>
#include"rbt.h"
using namespace std;

int main()
{
	RBT<int> tree;
    tree.insert(10);
    tree.insert(20);
    vector<int> v = tree.get_inorder();
    for(auto e: v)
    {
        cout << e << "\n";
    }
	return 0;
}