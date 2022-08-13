


// Desc:  Implementation of an int sequence with push/pop in a LIFO order
class Stack {

    private:

        // Desc:  arr = static array of capacity STACKCAP
        //        size = the number of elements presently in the stack
        //  Inv:  Follows the A2 Spec, namely that the stack elements 
        //        are in order within A[0..size-1], where the top of
        //        the stack is A[0].
        static const unsigned STACKCAP = 8;
        int arr[STACKCAP]={0};
        unsigned size;

    public:

        // Desc:  Object constructor
        // Post:  size is set to 0 as the stack is empty
        Stack();


        // Desc:  Insert element x to the top of the stack.
        //  Pre:  The stack is not full
        // Post:  value x is inserted at the top of the stack
        void push(int x);


        // Desc:  Remove and return element at the top of the stack.
        //  Pre:  The stack is not empty
        // Post:  removes and returns value at the top of the stack
        int pop();


        // Desc:  Return the topmost element of the stack.
        //  Pre:  Stack is not empty
        // Post:  returns value at the top of the stack
        int peek() const;


        // Desc:  check if the stack is stack is empty
        // Post:  returns true if the stack is empty, otherwise false
        bool isEmpty() const;

};


