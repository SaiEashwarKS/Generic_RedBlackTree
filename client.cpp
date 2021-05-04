#include<iostream>
#include<vector>
#include<string>
#include<list>

#include "rbt.h"
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

    #if 0
    vector<int>v{10, 30, 20, 50, 40};
    RBT<int> tree(v.begin(), v.end());
    vector<int>v2{100, 300, 200, 500, 400};
    RBT<int> tree2(v2.begin(), v2.end());
    tree2 = tree;
    vector<int> v3 = tree2.get_preorder();
    for(auto e: v3)
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
    
    #if 0
    RBT<int> tree;
    tree.insert(3);
    tree.insert(21);
    tree.insert(32);
    tree.insert(15);
    tree.insert(1);
    tree.insert(50);
    tree.insert(30);
    //tree.insert(30);
    vector<int> v = tree.get_preorder();
    for(auto e: v)
    {
        
        cout << e << "\t";
    }
    cout << "\n";
    #endif

    #if 0
    //vector<int> v{10, 20, 60, 30, 11, 20, 40, 5, 100, 20, 35, 32, 15, 69, 69420};
    vector<int> v{10, 20, 60, 30, 11, 20, 40, 5, 100, 20, 35, 32, 15, 69, 69420};
    RBT<int> tree(v.begin(), v.end());
    vector<int> v2 = tree.get_postorder();
    
    for(auto e: v2)
    {
        cout << e << "\t";
    }

    cout << "\n";
    #endif

    #if 0
    vector<int> v{10, 20, 30};
    vector<int> v2{100, 200, 300};
    RBT<int> t1(v.begin(), v.end());
    RBT<int> t2(v2.begin(), v2.end());
    RBT<int> t3;
    t3 = t1+t2;
    vector<int> v3 = t3.get_preorder();
    
    for(auto e: v3)
    {
        cout << e << "\t";
    }

    cout << "\n";
    #endif

    #if 0
    vector<string> v{"cde", "abc", "xyz", "abc"};
    RBT<string> tree(v.begin(), v.end());
    vector<string> v2 = tree.get_preorder();
    for(auto e: v2)
    {
        cout << e << "\t";
    }

    cout << "\n";
    cout << tree.min() << "\t" << tree.max() << endl;
    #endif

    #if 0
    RBT<int> tree;
    vector<int> v3;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    // tree.remove(20);
    // tree.insert(20);
    tree.insert(30);
    tree.insert(1);
    tree.insert(7);
    tree.insert(15);
    tree.insert(199);
    tree.insert(0);
    tree.insert(32);
    v3 = tree.get_preorder();
    for(auto e: v3)
    {
        cout << e << "\t";
    }
    cout << endl;
    
    tree.remove(10);
    tree.remove(20);
    tree.remove(5);
    tree.remove(30);
    tree.remove(1);
    tree.remove(7);
    tree.remove(15);
    tree.remove(199);
    tree.remove(30);
    tree.remove(0);
    tree.remove(1);
    tree.remove(32);
    tree.remove(199);
    v3 = tree.get_preorder();
    for(auto e: v3)
    {
        cout << e << "\t";
    }

    cout << "\n";
    #endif

    #if 0
    vector<int> v {1, 2,3, 4, 5, 6, 7, 8, 9, 10};
    RBT<int> tree(v.begin(), v.end());
    vector<int> v3;
    v3 = tree.get_preorder();
    for(auto e: v3)
    {
        cout << e << "\t";
    }
    cout << endl;

    tree.remove(5);
    tree.remove(8);
    v3 = tree.get_preorder();
    for(auto e: v3)
    {
        cout << e << "\t";
    }
    cout << endl;
    cout << "height : " << tree.height() << endl;
    cout << "leaf count : " << tree.leaf_count() << endl;
    cout << "level order : " << endl;
    tree.print_level_order();
    #endif

    #if 0
    RBT<int> tree {1, 2, 3};
    vector<int> v3;
    v3 = tree.get_preorder();
    for(auto e: v3)
    {
        cout << e << "\t";
    }
    cout << endl;
    cout << "height : " << tree.height() << endl;
    cout << "leaf count : " << tree.leaf_count() << endl;
    cout << "level order : " << endl;
    tree.print_level_order();
    #endif

    #if 0
    RBT<int, greater<int>> tree {1, 2, 3};
    vector<int> v3;
    v3 = tree.get_preorder();
    for(auto e: v3)
    {
        cout << e << "\t";
    }
    cout << endl;
    #endif

    #if 0
    struct my_compare
    {
        bool operator()(const string& a, const string& b)const{return a.size() < b.size();}
    };
    RBT<string, my_compare>tree{"aa", "a", "aaa"};
    vector<string> v3;
    v3 = tree.get_preorder();
    for(auto e: v3)
    {
        cout << e << "\t";
    }
    cout << endl;
    #endif

    #if 0
    RBT<int> tree {5, 4, 1, 2, 3};
    cout << *tree.begin() << endl;
    for(auto e: tree)
    {
        cout << e << "\t";
    }
    cout << endl;
    auto it = tree.begin();
    while(it != tree.end())
    {
        cout << *it << "\t";
        ++it;
    }
    cout << endl;

    cout << "max : " << *tree.max() << " min : " << *tree.min() << endl;
    #endif

    #if 0
    RBT<list<string>> tree;
    tree.insert({"b", "a", "c"});
    tree.insert({"x", "y", "w"});
    tree.insert({"a", "b", "c"});
    tree.insert({"m", "o", "n", "i", "s", "h"});
    tree.insert({"s", "ai"});
    tree.insert({"n", "m", "p"});
    tree.insert({"d", "e"});
    tree.insert({"o", "p"});
    tree.insert({"g", "g"});
    tree.insert({"w", "p"});
    tree.insert({"g", "g"});
    tree.insert({"ondu"});
    tree.insert({"eradu", "mooru"});

    for(auto e : tree)
    {
        for(auto e2 : e)
        {
            cout << e2 << "\t";
        }
        cout << endl;
    }
    #endif

    #if 0
    RBT<int> t1 {1, 2, 3};
    RBT<int> t2 {2, 3, 5, 6, 7};
    cout << "t1 size (3) " << t1.size() <<endl;
    cout << "t2 size (5) " << t2.size() <<endl;
    RBT<int> t3; 
    t3 = t1 + t2;
    RBT<int> t4 = t1 - t2;
    for(auto e: t3)
    {
        cout << e << "\t";
    }
    cout << endl;
    for(auto e: t4)
    {
        cout << e << "\t";
    }
    cout << endl;
    #endif

    #if 0
    RBT<int> t {3, 2, 1, 6, 5, 9, 7, 4, 8, 10};
    cout << "forward : \n";
    for(auto e: t)
    {
        cout << e << "\t";
    }
    cout << endl;

    auto it = t.rbegin();
    cout << "reverse : \n";
    while(it != t.rend())
    {
        cout << *it << "\t";
        ++it;
    }
    cout << endl;
    #endif

    #if 1
    cout << "\nnode root\n";
    RBT<int> tree1 {6};
    //RBT<int> t3(t1);
    for(auto e: tree1)
    {
        cout << e << "\t";
    }
    cout << "\n------------------------" <<endl;
    #endif

    //RR
    #if 1
    cout << "\nRR\n";
    RBT<int> t1 {6, 7, 8};
    //RBT<int> t3(t1);
    for(auto e: t1)
    {
        cout << e << "\t";
    }
    cout << "\n------------------------" <<endl;
    #endif

    //LL
    #if 1
    cout << "\nLL\n";
    RBT<int> t2{8, 7, 6};
    for(auto e: t1)
    {
        cout << e << "\t";
    }
    cout << "\n------------------------" <<endl;
    #endif

    #if 1
    cout << "\nLR\n";
    RBT<int> t3{8, 7, 6, 1, 2, 3};
    for(auto e: t1)
    {
        cout << e << "\t";
    }
    cout << "\n------------------------" <<endl;
    #endif  

    #if 1
    cout << "\nRL\n";
    RBT<int> t4{1, 2,3, 8, 7};
    for(auto e: t1)
    {
        cout << e << "\t";
    }
    cout << "\n------------------------" <<endl;
    #endif


	return 0;
}
