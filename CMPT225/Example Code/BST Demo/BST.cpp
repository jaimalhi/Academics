
#include "BST.h"
#include "assert.h"

#include <iostream>
#include <cassert>

using namespace std;

BST::BST() {
	root = NULL;
}


bool BST::isEmpty() const {
	return root == NULL;
}


void BST::insert(int key) {
	root = insert(root, key); // helper function
} // insert


void BST::print() const {
    ascii(root);
    cout << endl;
} // print


void BST::ascii(BTnode *tree) const {
    if (tree == NULL) return;

    ascii(tree->right);

    for (int i = 0; i < tree->depth; i++) {
        cout << "  ";
    }
    cout << tree->key << endl;

    ascii(tree->left);

    
    /*
    if (tree == NULL) return;

    cout << '[' << tree->key;

    if (tree->left) {
        cout << " L";
        ascii(tree->left);
    }
    if (tree->right) {
        cout << " R";
        ascii(tree->right);
    }
    
    cout << ']';

    */
} // ascii


void BST::inorder(BTnode *tree) const {

} // inorder


BTnode * BST::insert(BTnode *tree, int key) {
	// Base case
	if (tree == NULL) {
        //tree = new BTnode(key, NULL, NULL, NULL);
		return new BTnode(key, NULL, NULL, NULL);
	}

	if (key <= tree->key) { // left subtree
		tree->left = insert(tree->left, key);
		// assert(tree->left);
		tree->left->parent = tree;
		tree->left->depth = tree->depth + 1;
	} else { // right subtree
		tree->right = insert(tree->right, key);
		// assert(tree->right);
		tree->right->parent = tree;
		tree->right->depth = tree->depth + 1;
	}
	return tree;
} // insert

/*
if((tree->left == nullptr) || (tree->right == nullptr)){
            AVLTreeNode<K, V>* temp = tree->left ? tree->left : tree->right;
            //No children
            if(temp == nullptr){
                temp = tree;
                tree = nullptr;
            }
            else{
                *tree = *temp; //copy content of non-empty child
            }
            delete temp;
        }
        else{
            //has two children, get smallest in right subtree
            AVLTreeNode<K, V>* temp = minValue(tree->right);
            tree->key = temp->key;
            tree->right = removeHelper(tree->right, temp->key); //delete inorder successor
        }
*/




