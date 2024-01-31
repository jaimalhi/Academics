//Sequence.h
class Sequence {
    public:
        Sequence(unsigned size);
        void set(unsigned index, int x);
        int get(unsigned index);
        void append(int x);
        void trunc(unsigned newSize);
        unsigned getSize();

    private:
        int * arr;
        unsigned size;
};

