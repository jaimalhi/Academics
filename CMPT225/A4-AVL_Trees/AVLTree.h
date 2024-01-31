//AVLTree.h
#include <iostream>
#include <vector>
#include <string>
#include <algorithm> //sort
using namespace std;

// AVL Node Class
template <typename K, typename V> //K=key, V=value
class AVLTreeNode {
public:
    //Attributes
    AVLTreeNode* parent; //parent - pointer to parent
    AVLTreeNode* left;   //left - pointer to left child
    AVLTreeNode* right;  //right - pointer to right child
	K key;               //key - node's key
	V value;             //value - node's value
	unsigned int height; //height - node's height

	//Constructors
    AVLTreeNode(K key, V value)
    : parent(nullptr), left(nullptr), right(nullptr), key(key), value(value), height(0) 
    {} //default constructor
};
 
// AVL Tree class
//* similar to arrays, keys = indices and value = array element
template <typename K, typename V> //K=key, V=value
class AVLTree
{
private:
	//Tree attributes 
    AVLTreeNode<K, V>* root;
    unsigned int treeSize;
    //Helper functions
    AVLTreeNode<K, V>* insertHelper(AVLTreeNode<K, V>* tree, K key, V value);
    AVLTreeNode<K, V>* removeHelper(AVLTreeNode<K, V>* tree, K key);
    AVLTreeNode<K, V>* copyTree(AVLTreeNode<K, V>* root);
    AVLTreeNode<K, V>* minValue(AVLTreeNode<K, V>* tree);
    AVLTreeNode<K, V>* rightRotate(AVLTreeNode<K, V>* y); 
    AVLTreeNode<K, V>* leftRotate(AVLTreeNode<K, V>* x);
    AVLTreeNode<K, V>* rotations(AVLTreeNode<K, V>* tree, K key);
    unsigned int max(unsigned int a, unsigned int b);
    unsigned int min(unsigned int a, unsigned int b);
    void keysHelper(AVLTreeNode<K, V>* tree, vector<K>& keys) const ;
    void valuesHelper(AVLTreeNode<K, V>* tree, vector<V>& values) const ;
    bool searchKey(AVLTreeNode<K, V>* tree, K key) const ;
    void updateHeight(AVLTreeNode<K, V>* root);
    void deleteTree(AVLTreeNode<K, V>* tree);
    int checkBalance(AVLTreeNode<K, V>* tree);
    int height(AVLTreeNode<K, V>* tree);
    V searchHelper(AVLTreeNode<K, V>* tree, K key) const ;
public:
    //Desc: Default Constructor, creates an empty tree whose root is a null pointer
    AVLTree();

    //Desc: Copy Constructor, a constructor that creates a deep copy of its AVLTree reference parameter
    AVLTree(const AVLTree<K, V> &other);

    //Desc: Assignment operator, overloads the assignment operator for AVLTree objects to make a deep copy of its AVLTree reference parameter and return a reference to the calling object
    AVLTree<K, V>& operator=(const AVLTree<K, V> &other);
	
    //Desc: Destructor, deletes dynamic memory allocated by the tree
    ~AVLTree();

    //Desc: if the tree does not contain the method's first parameter which represents the key, inserts the key and value (the second parameter) and returns true; otherwise returns false without insertion
    bool insert(K key, V value);

    //Desc: removes the key and associated value from the tree where the key matches the method's parameter and returns true; if the tree does not contain the a key matching the parameter returns false
    bool remove(K Key);

    //Desc: searches the tree for the key that equals the method's single parameter, returning the corresponding value if it is found and throwing a runtime_error exception if it is not
    V search(K key) const ;

    //Desc: returns a vector that contains all of the values in the tree; the contents of the vector are in ascending key - not value - order; if the tree is empty the returned vector should also be empty
    vector<V> values() const ;

    //Desc: returns a vector that contains all of the keys in the tree; the contents of the vector are in ascending order; if the tree is empty the returned vector should also be empty
    vector<K> keys() const ;

    //Desc: returns an unsigned int equal to the number of items stored in the tree
    unsigned int size() const ;

	void* getRoot() const { return root; }; //DO NOT REMOVE
};


//*AVL Tree Private Methods go here
template <typename K, typename V>
void AVLTree<K, V>::deleteTree(AVLTreeNode<K, V>* node){
    if(node != nullptr){
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
} //deleteTree

template <typename K, typename V>
AVLTreeNode<K, V>* AVLTree<K, V>::copyTree(AVLTreeNode<K, V>* root){
    if(root == nullptr){
        return nullptr;
    }
    AVLTreeNode<K, V>* node = new AVLTreeNode<K, V>(root->key, root->value);
    node->left = copyTree(root->left);
    if(node->left) node->left->parent = node;
    node->right = copyTree(root->right);
    if(node->right) node->right->parent = node;
    node->height = root->height;
    return node;
} //copyTree

template <typename K, typename V>
void AVLTree<K, V>::updateHeight(AVLTreeNode<K, V>* root){
    if(root != nullptr){
        //Store the height of the current node
        int value = 0;
        //Store the height of the left and right subtree
        if(root->left != nullptr){
            value = height(root->left) + 1;
        }
        if(root->right != nullptr){
            value = max(value, height(root->right) + 1);
        }
        //Update the height of the current node
        root->height = value;
    }
}

template <typename K, typename V> 
AVLTreeNode<K, V>* AVLTree<K, V>::leftRotate(AVLTreeNode<K, V>* x){ 
    if(x == nullptr) return x;
    if(x->right != nullptr){
        AVLTreeNode<K, V>* y = x->right; //right subtree of x
        if(y->left != nullptr){
            AVLTreeNode<K, V>* t2 = y->left; //left subtree of y
            //Perform rotation
            y->left = x;
            y->parent = x->parent;
            x->right = t2;
            x->parent = y;
            //Update heights
            updateHeight(x);
            updateHeight(y); 
            return y;
        } 
    }
    return x;
} //leftRotate

template <typename K, typename V>
AVLTreeNode<K, V>* AVLTree<K, V>::rightRotate(AVLTreeNode<K, V>* y){
    if(y == nullptr) return y;
    if(y->left != nullptr){
        AVLTreeNode<K, V>* x = y->left; //left subtree of y
        if(x->right != nullptr){
            AVLTreeNode<K, V>* t2 = x->right; //right subtree of x
            //Perform rotation
            x->right = y;
            x->parent = y->parent;
            y->left = t2;
            y->parent = x;
            //Update heights
            updateHeight(y);
            updateHeight(x);
            return x;
        } 
    }
    return y;
} //rightRotate

template <typename K, typename V>
AVLTreeNode<K, V>* AVLTree<K, V>::insertHelper(AVLTreeNode<K, V>* tree, K key, V value){ 
    //Base case
	if (tree == nullptr) {
        return new AVLTreeNode<K, V>(key, value);
	}
    //Recursive case
	if (key < tree->key){ //left subtree
        tree->left = insertHelper(tree->left, key, value);
        if(tree->parent != nullptr) tree->left->parent = tree;
	}
    else if(key > tree->key){ //right subtree
        tree->right = insertHelper(tree->right, key, value);
        if(tree->parent != nullptr) tree->right->parent = tree;
	}
    else{ //duplicate key
        cout << "Duplicate key!\n";
        return tree;
    }
    updateHeight(tree);
    tree = rotations(tree, key);
    return tree;
} //insertHelper

template <typename K, typename V>
AVLTreeNode<K, V>* AVLTree<K, V>::rotations(AVLTreeNode<K, V>* tree, K key){
    int bal = checkBalance(tree);
    if(bal > 1 && key < tree->left->key){
        return rightRotate(tree);
    } //left-heavy, right rotate
    if(bal < -1 && key > tree->right->key){
        return leftRotate(tree);
    } //right-heavy, left rotate
    if(bal > 1 && key > tree->left->key){
        tree->left = leftRotate(tree->left);
        return rightRotate(tree);
    } //left-heavy, left-right rotate
    if(bal < -1 && key < tree->right->key){
        tree->right = rightRotate(tree->right);
        return leftRotate(tree);
    } //right-heavy, right-left rotate
    return tree;
} //rotations

template <typename K, typename V>
int AVLTree<K, V>::checkBalance(AVLTreeNode<K, V>* tree){
    if(tree == nullptr){
        return -1;
    }
    else{
        int r = (height(tree->left) - height(tree->right));
        return r;
    }
} //checkBalance

template <typename K, typename V>
int AVLTree<K, V>::height(AVLTreeNode<K, V>* tree){
    if(tree == nullptr) return 0;
    return tree->height;
}

template <typename K, typename V>
unsigned int AVLTree<K, V>::max(unsigned int a, unsigned int b){
    return (a >= b) ? a : b;
} //max

template <typename K, typename V>
unsigned int AVLTree<K, V>::min(unsigned int a, unsigned int b){
    return (a <= b) ? a : b;
} //min

template <typename K, typename V>
AVLTreeNode<K, V>* AVLTree<K, V>::removeHelper(AVLTreeNode<K, V>* tree, K key){
    /// Base case
    if(tree == nullptr){
        return tree;
    }
	//Recursive case
    if(key < tree->key){ //left subtree
        tree->left = removeHelper(tree->left, key);
    }
    else if(key > tree->key){ //right subtree
        tree->right = removeHelper(tree->right, key);
    }
    else{ //key found, delete it
        //Case 1: node is a leaf
        if(tree->left == nullptr && tree->right == nullptr){
            delete tree;
            tree = nullptr;
        }
        //Case 2: node has only one child
        else if(tree->left == nullptr){ //right-child
            AVLTreeNode<K, V>* temp = tree;
            tree = tree->right;
            delete temp;
        }
        else if(tree->right == nullptr){  //left-child
            AVLTreeNode<K, V>* temp = tree;
            tree = tree->left;
            delete temp;
        }
        //Case 3: has both children
        else{
            AVLTreeNode<K, V>* temp = minValue(tree->right);
            tree->key = temp->key;
            tree->right = removeHelper(tree->right, temp->key);
        }
    }
    updateHeight(tree);
    tree = rotations(tree, key);
    return tree;
} //removeHelper

template <typename K, typename V>
AVLTreeNode<K, V>* AVLTree<K, V>::minValue(AVLTreeNode<K, V>* tree){
    AVLTreeNode<K, V>* curr = tree;
    while(curr->left != nullptr){
        curr = curr->left;
    }
    return curr;
} //minValue

template <typename K, typename V>
void AVLTree<K, V>::keysHelper(AVLTreeNode<K, V>* tree, vector<K>& keys) const {
    if(tree != nullptr){
        keysHelper(tree->left, keys);
        keys.push_back(tree->key);
        keysHelper(tree->right, keys);
    }
    return;
}

template <typename K, typename V>
void AVLTree<K, V>::valuesHelper(AVLTreeNode<K, V>* tree, vector<V>& values) const{
    if(tree != nullptr){
        valuesHelper(tree->left, values);
        values.push_back(tree->key);
        valuesHelper(tree->right, values);
    }
    return;
}

template <typename K, typename V>
bool AVLTree<K, V>::searchKey(AVLTreeNode<K, V>* tree, K key) const {
    //Base case
     if(tree == nullptr){
        return false;
    }
    if(key == tree->key){
        return true;
    }
    //Recursive case
    if(key < tree->key){ //left subtree
        return searchKey(tree->left, key);
    }
    else if(key > tree->key){ //right subtree
        return searchKey(tree->right, key);
    }
    return false;
}

template <typename K, typename V>
V AVLTree<K, V>::searchHelper(AVLTreeNode<K, V>* tree, K key) const {
    //Base case
    if(tree == nullptr){
        throw std::runtime_error("Key not found, nullptr\n");
    }
    if(key == tree->key){
        return tree->value;
    }
    //Recursive case
    if(key < tree->key){ //left subtree
        searchHelper(tree->left, key);
    }
    else if(key > tree->key){ //right subtree
        searchHelper(tree->right, key);
    }
    else{
        throw std::runtime_error("Key not found, else\n");
    }
    return tree->value;
}

//*AVL Tree Public Methods go here
template <typename K, typename V>
AVLTree<K, V>::AVLTree(){
    root = nullptr;
    treeSize = 0;
} //Default Constructor

template <typename K, typename V>
AVLTree<K, V>::AVLTree(const AVLTree<K, V> &other){
    treeSize = other.treeSize;
    root = copyTree(other.root);
} //Copy Constructor

template <typename K, typename V>
AVLTree<K, V>& AVLTree<K, V>::operator=(const AVLTree<K, V> &other){
    if (this != &other){
        root = copyTree(other.root);
        treeSize = other.treeSize;
        deleteTree(other.root);
    }
    return *this;
} //Assignment operator

template <typename K, typename V>
AVLTree<K, V>::~AVLTree(){ 
    deleteTree(root);
} //Destructor

template <typename K, typename V>
bool AVLTree<K, V>::insert(K key, V value){
    bool keyFound = searchKey(root, key);
    if(keyFound){ //if keyFound == true
        return false;
    } 
    else{
        treeSize++; //increment tree size
        root = insertHelper(root, key, value);
        return true;
    }
} //insert

template <typename K, typename V>
bool AVLTree<K, V>::remove(K key){ 
    bool keyFound = searchKey(root, key);
    if(keyFound){ //if keyFound == true
        treeSize--; //decrement tree size
        root = removeHelper(root, key);
        return true;
    } 
    else{
        return false;
    }
} //remove

template <typename K, typename V>
V AVLTree<K, V>::search(K key) const {
    AVLTreeNode<K, V>* temp = root;
    return searchHelper(temp, key);
} //search

template <typename K, typename V>
vector<V> AVLTree<K, V>::values() const {
    AVLTreeNode<K, V>* temp = root;
    vector<V> allValues;
    valuesHelper(temp, allValues);
    return allValues;
} //values

template <typename K, typename V>
vector<K> AVLTree<K, V>::keys() const {
    AVLTreeNode<K, V>* temp = root;
    vector<K> allKeys; 
    keysHelper(temp, allKeys);
    return allKeys;
} //keys

template <typename K, typename V>
unsigned int AVLTree<K, V>::size() const {
    return treeSize;
} //size