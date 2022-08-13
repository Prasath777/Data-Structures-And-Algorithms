
#include "Stack.h"

#include <stdexcept>



Stack::Stack(){
    size = 0; // the number of elements are zero initially
}

void Stack::push(int x){
    //when the stack is full, we throw a logic error
    if (size == STACKCAP){
        throw std::logic_error("The stack has reached it's maximum capacity, no more values can be inserted");
    }
    //if push is possible
    else{
        int i;
        //shifting the existing elements to the right of the array by one position
        for(i=(int)size-1;i >= 0;i--)
        {
            arr[i+1] = arr[i]; 
        }
        arr[0] = x; //pushing the the value to be inserted at index 0
        size++; //size has increased since we have added a value
    }
}

int Stack::pop(){
    //when the stack is empty, we throw a logic error
    if(size == 0){
        throw std::logic_error("The stack is empty, unable to pop");
    }
    //when the stack has elements in it
    else{
        int poppedNum = arr[0]; //storing the value to be popped in a temporary variable
        int i;
        //shifting the existing elements to the left of the array by one position
        for(i=1;i<(int)size;i++)
        {   
            arr[i-1] = arr[i];
        }
        arr[size-1] =0; //the value present in the last postion before popping should be made zero as the value has shifted to the left
        size--; //the number of values have decreased
        return poppedNum;
    }
}

int Stack::peek() const{
    //when the stack is empty, we throw a logic error
    if(size == 0){
        throw std::logic_error("The stack is empty, unable to peek");
    }
    //otherwise return the value at index 0 which is the the top
    else{
        return arr[0];
    }
}

bool Stack::isEmpty()const{
    return size==0; //return true if size is 0 which is when the stack is empty
}


