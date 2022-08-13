#pragma once
#include <iostream>
#include <cstring>
#include <math.h>    
#include <vector>

using namespace std;


const unsigned scale = 225;


// * * * replace with your own personal modulus * * * //
const unsigned M = 3833;



// Desc:  Dynamic Set of strings using a Hash Table (generic version)
//  Pre:  class T must have an attribute key of type string
template <class T>
class Set {
    private:
        T * A[M];
        int tablevalue(const char& ch) const;
        int hashValueCalc(const string& key) const;
        


        // * * * Add attributes and helper methods here if you wish. * * * //
        

        unsigned size; // * * * remove this * * * //
        


    public:
        // Desc:  Default constructor.  Initialize table to NULL.
        Set() { 
            memset(A, 0, sizeof(T *)*M); 
            size = 0;
        }


        // Desc:  Insert x into the Set, according to its ->key.
        //        If ->key is already present, then replace it by x.
        //        Collisions are resolved via quadratic probing sequence.
        // Post:  returns the table index where x was inserted
        //        returns -1 if x was not inserted
        int insert(T * x);


        // Desc:  Returns T * x such that x->key == key, if and only if 
        //        key is in the Set.
        //        Returns NULL if and only if key is not in the Set.
        // Post:  Set is unchanged
        T * search(const string& key) const;

};


// Desc:  Insert x into the Set, according to its ->key.
//        If ->key is already present, then replace it by x.
//        Collisions are resolved via quadratic probing sequence.
// Post:  returns the table index where x was inserted
//        returns -1 if x was not inserted
template <class T>
int Set<T>::insert(T * x) {

    int hashvalue = hashValueCalc(x->key); //calculates the hash value given the string
    
    if(A[hashvalue] == nullptr || (A[hashvalue]->key).compare(x->key) == 0){ //if the index is free or if it has the same key, then insert or replace accordingly
        A[hashvalue]= x;
        return hashvalue;
    }
    //otherwise we do quadratic probing
    else{
        int square = 1; // quadratic factor
        int newIndex = 0; // keeps track of current index
        int prevIndex = 0; // keeps track of previous index
        bool inserted = true; // used in while loop
        int i=0;
        while(inserted){ 
            newIndex = hashvalue + (square*square); // quadratic probing
            if( newIndex > M-1){ //if the index is out of range, adjust it
                newIndex = newIndex%M;
            }
            if(newIndex == prevIndex){ //if the prev index equals the new index, we stop as it's not possible to find a free space
                break;
            }
            //check the new index            
            if(A[newIndex] == nullptr || (A[newIndex]->key).compare(x->key) == 0){ //if the index is free or if it has the same key, then insert or replace accordingly
                delete A[newIndex]; //delete the current pointer
                A[newIndex] = x; //store the pointer in the free space
                return newIndex; // return the inserted index
            }
            square++;
            i++;
            prevIndex = newIndex; //prev index is the currwnt index in the next iteration
        }
    }
    return -1; //id it's not possible to insert
}


// Desc:  Returns T * x such that x->key == key, if and only if 
//        key is in the Set.
//        Returns NULL if and only if key is not in the Set.
// Post:  Set is unchanged
template <class T>
T * Set<T>::search(const string& key) const {

    int hashvalue = hashValueCalc(key); //calculates the hash value given the string

    if(A[hashvalue] == nullptr || (A[hashvalue]->key).compare(key) == 0){
        return A[hashvalue];
    }
    else{
        int square = 1;// quadratic factor
        int newIndex = 0;
        int prevIndex = 0;
        bool notFound = true;
        int i=0;
        while(notFound){
            newIndex = hashvalue + (square*square);
            if( newIndex > M-1){ //if the index is out of range, adjust it
                newIndex = newIndex%M;
            }
            if(newIndex == prevIndex){//if the index is free or if it has the same key, then insert or replace accordingly
                return nullptr;
            }
            if(A[newIndex] == nullptr || (A[newIndex]->key).compare(key) == 0 ){ //if the index is free, then it's not found(nullptr) or if it has the same key, then return the index
                return A[newIndex];
            }
            square++;
            prevIndex = newIndex;
        }
    }
    return nullptr;
}

//calculates the hash value
template <class T>
int Set<T>::hashValueCalc(const string& key) const{
    int hashvalue = tablevalue(key[0]); // intially hashvalue is the value of the first character
    int length = key.length() - 1 ; // length of the string

    for(int i = 1;i<key.length();i++){

        hashvalue = (hashvalue*64 + tablevalue(key[i]))%M; // hash value calculation using horner's method

    }

    hashvalue = (scale*hashvalue)%M; // using the scale value

    return hashvalue;
}

//returns the character value of a character
template <class T>
int Set<T>::tablevalue(const char& ch) const{
    if(int(ch)>=48 && int(ch) <=57){ // if it's a number
        return ch - '0';
    }
    else if (int(ch)>=65 && int(ch)<= 90){ // if it's an uppercase alphabet
        return int(ch) - 29;
    }
    else if(int(ch)>=97 && int(ch)<= 122){ // if it's a lowercase alphabet
        return int(ch) - 87;
    }
    else if(ch == '_'){ //if it's an underscore
        return 62;
    }
    else{ // if it's an invalid character
        return -1;
    }
}


