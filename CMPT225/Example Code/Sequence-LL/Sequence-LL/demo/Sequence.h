
#include <iostream>

struct node {
	int data;
	node * next;

	node(int data = 0, node * next = NULL) : data(data), next(next) { };
};


class Sequence {
    public:
        Sequence();
        void set(unsigned index, int x);
        void insert(unsigned index, int x);
        int get(unsigned index);
        void append(int x);
        void trunc(unsigned newSize);
        unsigned getSize();

        void print(std::ostream& os);

    private:
		node * head;
		node * tail;
		



};

