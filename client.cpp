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

    #if 0
    vector<int>v{10, 30, 20, 50, 40};
    RBT<int> tree(v.begin(), v.end());
    vector<int> v2 = tree.get_inorder();
    for(auto e: v2)
    {
        cout << e << "\t";
    }
    cout << "\n";
    #endif
    
    #if 0
    vector<int>v{10, 30, 20, 50, 40};
    RBT<int> tree(v.begin(), v.end());
    RBT<int> tree2(tree);
    vector<int> v2 = tree2.get_preorder();
    for(auto e: v2)
    {
        cout << e << "\t";
    }
    cout << "\n";
    #endif

    #if 1
    vector<int>v{10, 30, 20, 50, 40};
    RBT<int> tree(v.begin(), v.end());
    RBT<int> tree2 = tree;
    tree2 = tree;
    vector<int> v2 = tree2.get_preorder();
    for(auto e: v2)
    {
        cout << e << "\t";
    }
    cout << "\n";
    #endif

    #if 0
    RBT<vector<int>> tree;
    tree.insert({100, 2, 3});
    tree.insert({10, 20, 30});
    tree.insert({10, 20, 30});
    vector<vector<int>> v = tree.get_preorder();
    for(auto e: v)
    {
        for(auto e2 : e)
            cout << e2 << "\t";
        cout << "\n";
    }
    cout << "\n";
    #endif

    

	return 0;
}