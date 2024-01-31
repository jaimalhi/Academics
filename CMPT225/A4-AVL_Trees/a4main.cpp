// Basic test program for AVL Tree
// Author: John Edgar
// Date: July 2022
#include <vector>
#include <iostream>
#include "AVLTree.h"
using std::cout;
using std::endl;
using std::vector;

template <class K, class V>
bool checkAVLTree(const AVLTree<K, V>& tree);
void a4marking();

int main(){
    //a4marking();
    AVLTree<int, char> tree;
    tree.insert(3, 'a'); //root
    tree.insert(1, 'b'); //lvl 1 left
    tree.insert(5, 'c'); //lvl 1 right
    tree.insert(6, 'c'); //lvl 2 right-right
    tree.insert(4, 'd'); //lvl 2 right-left
    tree.insert(2, 'e'); //lvl 2 left-right

    tree.remove(5);
}

void a4marking(){
    AVLTree<int, int> aspen;

cout << "=============================================\n";
    cout << "Insert Test\n";
    bool success = aspen.insert(1, 2);
    cout << "Test Passed: " << success << endl;
cout << "=============================================\n";
    cout << "Remove Test\n";
    success = aspen.remove(1);
    cout << "Test Passed: " << success << endl;
cout << "=============================================\n";
    cout << "Search Test\n";
    //int result = aspen.search(1);
    //cout << "  Search Result = " << result << endl;
//=======================================================
    aspen.insert(1, 10);
    aspen.insert(2, 20);
    aspen.insert(3, 30);
    aspen.insert(4, 40);
    aspen.insert(5, 50);
cout << "=============================================\n";
    cout << "Values Test\n  ";
    vector<int> v2 = aspen.values();
    for(int x : v2){
        cout << x << " ";
    }
    cout << "\nTest Passed\n";
cout << "=============================================\n";
    cout << "Keys Test\n  ";
    vector<int> k1 = aspen.keys();
    for(int x : k1){
        cout << x << " ";
    }
    cout << "\nTest Passed\n";
cout << "=============================================\n";
    cout << "Copy-Cons + Op= Test\n";
    AVLTree<int, int> larch(aspen);
    aspen = larch;
    cout << "Test Passed\n";
cout << "=============================================\n";
    checkAVLTree<int, int>(aspen); 
    cout << endl << "end a4 test" << endl;
}

template <class K, class V>
bool checkAVLTree(const AVLTree<K, V>& tree){
    AVLTreeNode<int, int>* nd = (AVLTreeNode<int, int>*)tree.getRoot();
    cout << "height = " << nd->height << endl;

    return false;
}