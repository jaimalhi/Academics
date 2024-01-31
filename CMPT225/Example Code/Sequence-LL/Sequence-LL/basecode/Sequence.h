
#include <iostream>

class Sequence {
    public:
        Sequence();
        void set(unsigned index, int x);
        int get(unsigned index);
        void append(int x);
        void trunc(unsigned newSize);
        unsigned getSize();

        void print(std::ostream& os);

    private:



};

