// Desc:  Implementation of an int sequence with push/pop in a LIFO order
class Stack {

    private:

        // Desc:  arr = static array of capacity STACKCAP
        //        size = the number of elements presently in the stack
        //  Inv:  Follows the A2 Spec, namely that the stack elements 
        //        are in order within A[0..size-1], where the top of
        //        the stack is A[0].
        static const unsigned STACKCAP = 8;
        int arr[STACKCAP];
        unsigned size;

    public:

        // Desc:  Object constructor
        // Post:  sets intial size to 0
        Stack();


        // Desc:  Insert element x to the top of the stack.
        //  Pre:  size <= STACKCAP
        // Post:  Inserts element x at the top of stack and moves 
        //        all other elements one index over (i+1)
        void push(int x);


        // Desc:  Remove and return element at the top of the stack.
        //  Pre:  size > 0
        // Post:  removes and returns element the top of stack and
        //        moves all other elements one index over (i-1)  
        int pop();


        // Desc:  Return the topmost element of the stack.
        //  Pre:  size > 0
        // Post:  Returns the topmost element of the stack at arr[0]
        int peek() const;


        // Desc:  returns true if stack is empty, false otherwise
        // Post:  returns true if stack is empty, false otherwise
        bool isEmpty() const;
};


