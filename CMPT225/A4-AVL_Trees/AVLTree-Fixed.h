#pragma once

#include <vector>
#include <algorithm>
#include <stdexcept>

using std::vector;
using std::max;
using std::runtime_error;

// AVL Node Clas
template<class k, class v>
class AVLTreeNode {
public:

	k key;
	v value;
	unsigned height;

	AVLTreeNode<k, v>* parent;
	AVLTreeNode<k, v>* left;
	AVLTreeNode<k, v>* right;

	// Constructor
	AVLTreeNode(k Akey, v Aval) :
		key(Akey),
		value(Aval),
		height(0),
		parent(nullptr),
		left(nullptr),
		right(nullptr)
		{}
};

// AVL Tree class
template<class k, class v>
class AVLTree
{
private:

	AVLTreeNode<k, v>* root;
	unsigned a_size; // Number of nodes in given AVLTree

	// Constructor/destructor helpers

	void memClear(AVLTreeNode<k, v>* nd);
	AVLTreeNode<k, v>* copyHelper(const AVLTreeNode<k, v>* ond);

	// Accessors

	int ndHeight(AVLTreeNode<k, v>* nd) const;
	int getBal(AVLTreeNode<k, v>* nd) const;
	AVLTreeNode<k, v>* findPred(AVLTreeNode<k, v>* nd) const;
	void valuesH(AVLTreeNode<k, v>* nd, vector<v>& vals) const;
	void keysH(AVLTreeNode<k, v>* nd, vector<k>& keys) const;

	// Mutators

	AVLTreeNode<k, v>* newNode(k key, v val);
	AVLTreeNode<k, v>* rotateRight(AVLTreeNode<k, v>* nd);
	AVLTreeNode<k, v>* rotateLeft(AVLTreeNode<k, v>* nd);
	AVLTreeNode<k, v>* insertH(k key, v val, AVLTreeNode<k, v>* nd);
	AVLTreeNode<k, v>* removeH(k key, AVLTreeNode<k, v>* nd);
	AVLTreeNode<k, v>* reBal(AVLTreeNode<k, v>* nd);

public:

	// Constructors

	AVLTree();
	AVLTree(const AVLTree<k, v>& oth);
	AVLTree<k, v>& operator=(const AVLTree<k, v>& oth);
	~AVLTree();

	// Mutators

	bool insert(k key, v val);
	bool remove(k key);

	// Accessors

	v search(k key) const;

	vector<v> values() const;
	vector<k> keys() const;

	unsigned size() const;
	void* getRoot() const { return root; }; // DO NOT REMOVE
};

// -------------------------------------------------
// Private constructor/destructor helpers
// -------------------------------------------------

// PARAM: The node to be deleted
// POST: Deletes all nodes of a tree in postorder
template<class k, class v>
void AVLTree<k, v>::memClear(AVLTreeNode<k, v>* nd)
{
	if(nd){
		memClear(nd->left);
		memClear(nd->right);
		delete nd;
		a_size--;
	}
}

// PRE: ond is not the same as the calling object
// PARAM: ond, the AVLTree root node to be copied
// POST: copies the content of ond into calling object in pre-order
template<class k, class v>
AVLTreeNode<k, v>* AVLTree<k, v>::copyHelper(const AVLTreeNode<k, v>* ond)
{	
	AVLTreeNode<k, v>* nn = nullptr;
	if(ond){
		// Make new node, copy height, increment size
		nn = new AVLTreeNode<k, v> (ond->key, ond->value);
		nn->height = ond->height;
		a_size++;

		// Copy left sub-tree
		nn->left = copyHelper(ond->left);
		if(nn->left) nn->left->parent = nn;

		// Copy right sub-tree
		nn->right = copyHelper(ond->right);
		if(nn->right) nn->right->parent = nn;
	}

	// Return node
	return nn;
}

// -------------------------------------------------
// Private Accessors
// -------------------------------------------------

// PARAM: node for which we want the height
// POST: sets and returns height of the node (returns -1 if nullptr)
template<class k, class v>
int AVLTree<k, v>::ndHeight(AVLTreeNode<k, v>* nd) const
{	
	return(!nd ? -1 : nd->height);
}

// PARAM: node for which we want balance
// POST: returns the balance of the node
template<class k, class v>
int AVLTree<k, v>::getBal(AVLTreeNode<k, v>* nd) const
{
	return (nd ? ndHeight(nd->left) - ndHeight(nd->right) : 0);
}

// PRE: node exists and has a left child
// PARAM: node for which we want a predecessor
// POST: pointer to the predecessor node
template<class k, class v>
AVLTreeNode<k, v>* AVLTree<k, v>::findPred(AVLTreeNode<k, v>* nd) const
{
	AVLTreeNode<k, v>* cur = nd->left;
	while(cur->right) cur = cur->right;
	return cur;
}

// PARAM: node for which we will add value to the vector passed by reference
// POST: vector is altered with all node-values inorder (keys) of this nodes sub-tree 
template<class k, class v>
void AVLTree<k, v>::valuesH(AVLTreeNode<k, v>* nd, vector<v>& vals) const
{
	if(!nd) return;
	valuesH(nd->left, vals);
	vals.push_back(nd->value);
	valuesH(nd->right, vals);
}

// PARAM: node for which we will add key to the vector passed by reference
// POST: vector is altered with all node-keys inorder (keys) of this nodes sub-tree 
template<class k, class v>
void AVLTree<k, v>::keysH(AVLTreeNode<k, v>* nd, vector<k>& keys) const
{
	if(!nd) return;
	keysH(nd->left, keys);
	keys.push_back(nd->key);
	keysH(nd->right, keys);
}

// -------------------------------------------------
// Private Mutators
// -------------------------------------------------

// PRE: valid key and value
// PARAM: key, value
// POST: new dynamically allocated node's pointer
template<class k, class v>
AVLTreeNode<k, v>* AVLTree<k, v>::newNode(k key, v val)
{	
	return new AVLTreeNode<k, v>(key, val);
}

// PRE: node is unbalanced and requires a rotation, and has a left child
// PARAM: node to be right rotated
// POST: pointer to the new node in the place of the original, with sub-tree right rotated
template<class k, class v>
AVLTreeNode<k, v>* AVLTree<k, v>::rotateRight(AVLTreeNode<k, v>* nd)
{	
	// temp node and move y->right
	AVLTreeNode<k, v>* y = nd->left;
	nd->left = y->right;
	if(y->right)
		y->right->parent = nd;

	// Set y's parent
	y->parent = nd->parent;

	// set node's parent child to y
	if(nd->parent){
		if(nd == nd->parent->right)
			nd->parent->right = y;
		else
			nd->parent->left = y;
	}

	// move nd
	y->right = nd;
	nd->parent = y;

	// update heights
	nd->height = max(ndHeight(nd->left), ndHeight(nd->right)) + 1;
	y->height = max(ndHeight(y->left), (int) nd->height) + 1; // Easier to just typecast than do some fancy stuff

	return y;
}

// PRE: node is unbalanced and requires a rotation, and has a right child
// PARAM: node to be left rotated
// POST: pointer to the new node in the place of the original, with sub-tree left rotated
template<class k, class v>
AVLTreeNode<k, v>* AVLTree<k, v>::rotateLeft(AVLTreeNode<k, v>* nd)
{	
	// temp node and move y->left
	AVLTreeNode<k, v>* y = nd->right;
	nd->right = y->left;
	if(y->left)
		y->left->parent = nd;

	// Set y's parent
	y->parent = nd->parent;

	// set node's parent child to y
	if(nd->parent){
		if(nd == nd->parent->left)
			nd->parent->left = y;
		else
			nd->parent->right = y;
	}

	// move nd
	y->left = nd;
	nd->parent = y;

	// update heights
	nd->height = max(ndHeight(nd->left), ndHeight(nd->right)) + 1;
	y->height = max(ndHeight(y->left), (int) nd->height) + 1;

	return y;
}

// PRE: key and val are valid
// PARAM: key, value, root-sub-tree node pointer
// POST: node is inserted, or the tree is unchanged
template<class k, class v>
AVLTreeNode<k, v>* AVLTree<k, v>::insertH(k key, v val, AVLTreeNode<k, v>* nd)
{	
	// if is empty, insert here
	if(!nd){
		a_size++;
		return newNode(key, val);
	}

	// If less than, search left sub-tree
	if(key < nd->key){
		nd->left = insertH(key, val, nd->left);
		nd->left->parent = nd;
	}
	// If greater than, search right sub-tree
	else if(key > nd->key){
		nd->right = insertH(key, val, nd->right);
		nd->right->parent = nd;
	}
	// If equal, return unchanged node
	else return nd;

	// Update height
	nd->height = 1 + max(ndHeight(nd->left), ndHeight(nd->right));

	return reBal(nd);
}

// PRE: key is valid type
// PARAM: key of desired node, root-sub-tree node pointer
// POST: key/val is removed from tree, or if not there, returns unchanged root node
template<class k, class v>
AVLTreeNode<k, v>* AVLTree<k, v>::removeH(k key, AVLTreeNode<k, v>* nd)
{	
	// BST Removal

	// If bottom of tree, return unchanged (not found)
	if(!nd){
		return nd;
	}
	// If less than, search left sub-tree
	if(key < nd->key){
		nd->left = removeH(key, nd->left);
		if(nd->left) nd->left->parent = nd;
	}
	// If greater than, search right sub-tree
	else if(key > nd->key){
		nd->right = removeH(key, nd->right);
		if(nd->right) nd->right->parent = nd;
	}
	// If equal, remove node
	else{
		AVLTreeNode<k, v>* tmp;

		// Zero or one child nodes
		if(!nd->left || !nd->right){

			// Only de-increment size if it will not make a recursive call
			a_size--;
			tmp = nd;

			if(!nd->left)
				nd = nd->right;
			else if(!nd->right)
				nd = nd->left;

			if(nd) nd->parent = tmp->parent;

			delete tmp;
		}
		else{
			// Find predecessor, move data, remove predecessor
			tmp = findPred(nd);
			nd->key = tmp->key;
			nd->value = tmp->value;
			nd->left = removeH(nd->key, nd->left);
			// I asked John if this was allowed, and he said yes. I understand that 
			// for high data sizes this is inefficient, as the data must be moved.
			// However, an easy solution for that would to just have pointers to the 
			// data itself. All this to say, I know what I did, I know why its bad, I 
			// know how to do it better, but this situation does not require it to be
		}
	}
	// If spot is empty, return (no need to balance or update height)
	if(!nd) return nd;

	// Fix height and get balance
	nd->height = 1 + max(ndHeight(nd->left), ndHeight(nd->right));

	return reBal(nd);
}

// PRE:	node is not nullptr
// PARAM: root node of subtree to be balanced
// POST: balances the subtree of nd
template<class k, class v>
AVLTreeNode<k, v>* AVLTree<k, v>::reBal(AVLTreeNode<k, v>* nd)
{
	int bal = getBal(nd);

	// Rotations
	if(bal > 1 && getBal(nd->left) >= 0){ 
		return rotateRight(nd); // LL
	}
	else if(bal < -1 && getBal(nd->right) <= 0){ 
		return rotateLeft(nd); // RR
	}
	else if(bal > 1 && getBal(nd->left) < 0){
		nd->left = rotateLeft(nd->left);
		return rotateRight(nd);
	} // LR
	else if(bal < -1 && getBal(nd->right) > 0){
		nd->right = rotateRight(nd->right);
		return rotateLeft(nd);
	} // RL

	return nd;
}

// -------------------------------------------------
// Constructors
// -------------------------------------------------

// POST: sets root to null and size to 0
template<class k, class v>
AVLTree<k, v>::AVLTree()
{
	root = nullptr;
	a_size = 0;
}

// PARAM: other tree to be copied
// POST: deep copy of oth is created
template<class k, class v>
AVLTree<k, v>::AVLTree(const AVLTree& oth)
{	
	a_size = 0;
	root = copyHelper(oth.root);
}

// PARAM: other tree to be copied
// POST: removes contents of current tree, deep copies oth
template<class k, class v>
AVLTree<k, v>& AVLTree<k, v>::operator=(const AVLTree& oth)
{	
	if(this != &oth){
		memClear(root);
		root = copyHelper(oth.root);
	}
	return *this;
}

// POST: deletes tree
template<class k, class v>
AVLTree<k, v>::~AVLTree()
{
	memClear(root);
}

// -------------------------------------------------
// Mutators
// -------------------------------------------------

// PARAM: key, value pair
// POST: node is inserted (returns true), or tree is unchanged (returns false)
template<class k, class v>
bool AVLTree<k, v>::insert(k key, v val)
{	
	// determines boolean success based on change in size of tree
	unsigned tmp = a_size;
	root = insertH(key, val, root);
	return (tmp < a_size);
}

// PARAM: key to find
// POST: node of key is removed (returns true), or tree is unchanged (returns false
template<class k, class v>
bool AVLTree<k, v>::remove(k key)
{	
	// determines boolean success based on change in size of tree
	unsigned tmp = a_size;
	root = removeH(key, root);
	return (tmp > a_size);
}

// -------------------------------------------------
// Accessors
// -------------------------------------------------

// PARAM: key to search for
// POST: returns value of key searched for or throws error (not found)
template<class k, class v>
v AVLTree<k, v>::search(k key) const
{	
	// Iteratively traverse tree, if bottom is reached, throw error
	// If found, return val
	AVLTreeNode<k, v>* cur = root;
	while(cur){
		if(key < cur->key)
			cur = cur->left;
		else if(key > cur->key)
			cur = cur->right;
		else
			return cur->value;
	}
	throw runtime_error("Key not found in tree");
}

// POST: returns a vector with all values inorder of keys
template<class k, class v>
vector<v> AVLTree<k, v>::values() const
{
	vector<v> vals;
	valuesH(root, vals);
	return vals;
}

// POST: returns a vector with all keys inorder
template<class k, class v>
vector<k> AVLTree<k, v>::keys() const
{
	vector<k> keys;
	keysH(root, keys);
	return keys;
}

// POST: returns total number of nodes
template<class k, class v>
unsigned AVLTree<k, v>::size() const
{
	return a_size;
}