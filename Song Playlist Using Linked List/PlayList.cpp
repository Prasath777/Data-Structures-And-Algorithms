// Write your name and date here
//Lakshmi Narayanaprasath Kannan 2022/06/01
#include "PlayList.h"
#include<iostream>
using std::cout;
using std::endl;
// PlayList method implementations go here

//Default Constructor
PlayList::PlayList(){
    //Initializing the private members of the class
    head = nullptr;
    songcount = 0;
}
//Copy contructor
// used when Playlist s1 = s2;
PlayList::PlayList(const PlayList& pl){

    songcount = pl.songcount;
    copyList(pl);

}

//Destructor - Deallocates heap memory
//Deletes the the list after usage
PlayList::~PlayList(){
    
    deleteList(); //deletes the list
    
}
//overloaded assignment operator
PlayList& PlayList::operator=(const PlayList& pl){
    

    //if the both the calling object and the passed object are the same, we just return the calling object
    if(this == &pl){
        return *this; // return the calling object
    }
    songcount = pl.songcount;
    deleteList();//deleting the calling object's list before copying the passed object's list
    // similar to the copy constructor
    copyList(pl);
    return *this;
}
//Node insertion at a given position
void PlayList::insert(Song sng, unsigned int pos){
       
        if(head == nullptr){
            
            head = new PlayListNode(sng); // the head is null(list is empty), Node is created and inserted at the head

        }
        // when the list is not empty, and the node is inserted at the head
        else if(pos==0){
            PlayListNode* oldHead = head; // pointer to the old head
            //new node inserted at head and the old head is attached next to the new head
            head = new PlayListNode(sng);
            head->next = oldHead;
 
        }
        // conventional way of inserting a node
        else{
            PlayListNode* previousNode = head; // pointer to the head
            int i=0;
            //loop to find the previous node for the newly inserted node
            while((unsigned)i< pos-1){
                previousNode = previousNode->next;
                i++;
            }
            //inserting the new node using a temporary pointer to prevent data loss
            PlayListNode* temp = previousNode->next;
            previousNode->next = new PlayListNode(sng);
            previousNode->next->next = temp; // accesing the next pointer of the newly inserted node
            
        }
        this->songcount++;
    
}
//Node deletion at the given position
Song PlayList::remove(unsigned int pos){

    PlayListNode* deleteNode; // pointer to the node to be deleted
   
    if(pos == 0){
    deleteNode = head;
    head=head->next;// make the second node as the head
    }
    else{
        PlayListNode* prevNode = head;
        int i=0;
        //loop to find the previous node for the node to be deleted
        while((unsigned)i< pos-1){
            prevNode = prevNode->next;
            i++;
        }
        deleteNode = prevNode->next; // node to be deleted
        prevNode->next = deleteNode->next; // linking back the list together after removing the node
        
    }
    
    Song deletedSong = deleteNode->song;
    songcount--;
    delete deleteNode; // Node deleted
    return deletedSong;
}
    
//Swapping nodes present at the given positions
void PlayList::swap(unsigned int pos1, unsigned int pos2){
    
    //initialization of pointers
    PlayListNode* prevNodeA = nullptr;
    PlayListNode* prevNodeB = nullptr;
    PlayListNode* currentNodeA = head;// pointer to the head
    PlayListNode* currentNodeB = head;// pointer to the head
    int i=0;
    // loop to figure out the current node(to be swapped) and its previous node
    while((unsigned)i< pos1){
        prevNodeA = currentNodeA;
        currentNodeA = currentNodeA->next;
        
        i++;
    }
    
    int j=0;
        // loop to figure out the current node(to be swapped with) and its previous node
    while((unsigned)j< pos2){
        prevNodeB = currentNodeB;
        currentNodeB = currentNodeB->next;
        
        j++;
    }
    //if the previous node is NULL, that means we are swapping the head node
    if(prevNodeA == NULL){
        head = currentNodeB; // swapped with the head
    }
    else{
        prevNodeA->next = currentNodeB; // otherwise swapped normally by editing the next pointer of the previous node
    }

    //if the previous node is NULL, that means we are swapping the head node
    if(prevNodeB == NULL){
        head = currentNodeA;// swapped with the head
    }
    else{
        //changing previous Node's next pointers
        prevNodeB->next = currentNodeA; // otherwise swapped normally by editing the next pointer of the previous node
    }

    //changing Swapped Node's next pointers
    PlayListNode* temp = currentNodeA->next;
    currentNodeA->next = currentNodeB->next;
    currentNodeB->next = temp;
    }

Song PlayList::get(unsigned int pos) const{

    int i=0;
    PlayListNode* current= head; // pointer to the head
    //loop to find the node specified by the given position
    while((unsigned)i<pos){
        current=current->next;
        i++;
    }
    return current->song;
    
}
//Returns the size of the playlist
unsigned int PlayList::size() const{

    return this->songcount;
}

//Deletes the list
void PlayList::deleteList(){
    PlayListNode* current = head;// pointer to the head
    PlayListNode* next = nullptr;
    while(current != NULL){
        next = current->next;
        delete current; //deletes the current node
        current = next; //pointer chnages to the next node
    }
}     

//Copies the playlist of the passed object in the parameter
void PlayList::copyList(const PlayList& pl){

    head = new PlayListNode(pl.head->song);
    PlayListNode* copyto = head; // pointer for the calling object
    PlayListNode* copyfrom = pl.head->next; //pointer for the object passed in the parameter
    //copying Nodes from the passed object to the calling object
    while(copyfrom != NULL){
        copyto->next = new PlayListNode(copyfrom->song); // creating a new node to insert it into the new playlist(calling object)
        //moving the pointers for both the objects
        copyfrom = copyfrom->next;
        copyto = copyto->next;
    
    }
}


