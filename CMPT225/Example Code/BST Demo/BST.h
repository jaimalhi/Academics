
class BTnode {
    public:

        int key;
        int depth;
        BTnode *left, *right, *parent;
        BTnode(int key, BTnode *left, BTnode *right, BTnode *parent) : key(key), left(left), right(right), parent(parent) { depth = 0; };
};


class BST {
    private:

        BTnode *root;
        BTnode *insert(BTnode *root, int key);
        void inorder(BTnode *root) const;
        void ascii(BTnode *root) const;

    public:

        BST();
        bool isEmpty() const;
        void insert(int key);

        void print() const;
};


