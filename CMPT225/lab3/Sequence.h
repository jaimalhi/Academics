//Sequence.h
#include <iostream>

class Sequence {
    public:
        Sequence(unsigned size);
        void set(unsigned index, int x);

        // Desc: returns the int value at arr[index] (given index)
        //  Pre: 0 <= index <= length of array-1
        // Post: int value at arr[index] is returned
        int get(unsigned index);
        void append(int x);
        void trunc(unsigned newSize);
        unsigned getSize();

        void print(std::ostream& os);

    private:
        int * arr;
        unsigned size;
};

