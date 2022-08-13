
#include "Queue.h"

#include <iostream>
using namespace std;


// Desc:  Constructor
Queue::Queue() : size(0), capacity(INITIAL_SIZE), frontindex(0), backindex(0) {
    arr = new int[capacity]; //creates an array of size capacity
} // constructor


// Desc:  Destructor
Queue::~Queue() {
   deleteQueue();//deletes the queue
} // destructor


// Desc:  Copy Constructor
Queue::Queue(const Queue &other) {
    copyQueue(other); // copies the passed object
    
} // copy constructor


// Desc:  Assignment operator
Queue & Queue::operator=(const Queue &rhs) {
    if (this != &rhs) { //checking if the passed object is same as the calling object
        deleteQueue();
        copyQueue(rhs);        
    }
    return *this; //returns pointer pointing to the calling object
 // lhs = rhs
} 


// Desc:  Inserts element x at the back (O(1))
void Queue::enqueue(int x) {
    if(size==capacity){ //when the queue is full
        growSize(); //expand the array
    }
    size++;
    arr[backindex] = x; //adding the value to the queue
    backindex = (backindex + 1) % capacity; //backindex has changed
} // enqueue


// Desc:  Removes the frontmost element (O(1))
//  Pre:  Queue not empty
void Queue::dequeue() {
    if(isEmpty()){ //if the queue is empty, we throw a logic error since we cannot dequeue
        throw std::logic_error("The queue is empty, unable to dequeue");
    }
    else{
        size--;
        frontindex = (frontindex + 1) % capacity; //front index has changed
        shrinkSize(); // the array is shrinked if it's necessary
    }    
} // dequeue


// Desc:  Returns a copy of the frontmost element (O(1))
//  Pre:  Queue not empty
int Queue::peek() const {  
     if(isEmpty()){ //if the queue is empty, we throw a logic error since we cannot peek
        throw std::logic_error("The queue is empty, unable to peek");
    }
    else{
        return arr[frontindex]; //peek at the top value
    }
} // top


// Desc:  Returns true if and only if queue empty (O(1))
bool Queue::isEmpty() const {
    return size == 0; //return true if the queue is empty
} // isempty

void Queue::deleteQueue(){
     delete [] arr; //deallocating the array
}

void Queue::copyQueue(const Queue& other){
        //copying all the private variables
        size = other.size;
        capacity = other.capacity;
        arr= new int[capacity]; //creating the arr in dynamic memory
        frontindex = other.frontindex;
        backindex = other.backindex;

        //loop to copy over all the elements
        for (int i = 0; i < (int)capacity; i++) {
            arr[i] = other.arr[i];
        }
}

void Queue::growSize(){
    if(size == capacity){// the queue is only expanded if the queue is full
        
        int* temp = new int [capacity*2]; // creating an array of twice the size of the current array in dynamic memory
        int j=0; //this variable keeps track of the index of the
        int i=frontindex;
        //copying elements of the array that exist between the front index and the end of the array
        while(i<(int)capacity){
            temp[j++] = arr[i];
            i++;
        }
        //since the queue is implemeted in a circular array, we might have elements behind the front index in the array
        //so we copy the elements of the array that exist between index 0 and the back index
        i = 0;
        while(i<(int)backindex){
            temp[j++] = arr[i];
            i++;
        }
        //the front index and the back index changes
        frontindex=0;
        backindex= j;
        deleteQueue();//deleting the array we copied from as we no longer need that
        arr= temp; //making arr to point to the new array
        capacity = capacity*2; // now the array is twice the (initial)capacity in size
    }
    
}

void Queue::shrinkSize(){
    //we only shrink if the only a quarter of the array is filled and the array after shrinking does drop below initial capacity
    if(size<(capacity/4) && (capacity/2)>=INITIAL_SIZE){
        int* temp = new int [capacity/2]; // creating an array of half the capacity
        int j=0;
        int i=frontindex;
        if(frontindex<backindex){ //if this statement is true, there won't be any elements inn a circular fashion
            //so, we just coppy the elements from the fron index to the back index
            while(i<(int)backindex){
                temp[j++] = arr[i];
                i++;
             }       
        }
        else{// otherwise, there are elements stored in a circular fashion
            //copying elements of the array that exist between the front index and the end of the array
            while(i<(int)capacity){
                temp[j++] = arr[i];
                i++;
             }
            i = 0;
             //so we copy the elements of the array that exist between index 0 and the back index
            while(i<(int)backindex){
                temp[j++] = arr[i];
                i++;
            }
        }
        //the front index and the back index changes
        frontindex=0;
        backindex= j;
        deleteQueue();//deleting the array we copied from as we no longer need that
        arr=temp;//making arr to point to the new array
        capacity = capacity/2; // now the array is half the (initial)capacity in size
    }

}



