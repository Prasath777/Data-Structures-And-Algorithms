/*
Big O complexity of Playlist Methods

1)Default Constructor:  O(1) --> we are just initializing the private variables, so irrespective of the size of the list, the complexity remains the same since we are just assigning the variables 
2)Destructor: O(n) --> deleting the whole liked list involves traversing through each and every node to delete it, this process depends on the size of the list
3)Copy Constructor: O(n) --> we traverse the passed list to copy elements to a new list, so this operation depend on the size of the list as we need to traverse the whole list(n)
4) Overloded assignment operator: O(n) --> this operation is similar to that of a copy contructor, we traverse the whole list
5)Insert: O(n) --> the worst case would be inserting a node in the last possible postion(n), in this scenario we traverse the list till (n-1)th node, so this operation depends on the size(n) of the list 
6)Remove: O(n) --> the worst case would be deleting the last node in the list, in this scenario we traverse the list till (n-1)th node to find the secong last node, so this operation depends on the size(n) of the list 
7)Get: O(n) --> we traverse the list to find the node at the given position, finding the last node will be the worst case as we need to traverse till the end of the list
8)Swap: O(n) --> we traverse the list to find the previous node for both the nodes to be swapped, the worst case is when we swap the last node and the second last node as we need to traverse the entire list for that
9)Size: O(1)--> we just return the private variable songcount, this operation is irrespective of the size of the list, so this is done in constant time

Big O complexity of Main Function Commands
1)Enter a song --> Given that we have a valid input, the complexity of this command is O(n) as it calls the insert method, which itself has the worst case complexity of O(n)
2)Remove a song --> Given that we have a valid input, the complexity of this command is O(n) as it calls the remove method, which itself has the worst case complexity of O(n)
3) Swap two songs --> Given that we have a valid inputs, the complexity of this command is O(n) as it calls the swap method, which itself has the worst case complexity of O(n)
4) Print all songs --> we traverse the list to access each position, and we call the get method each time, since the get method has a worst case complexity of O(n), we have a worst case run time of  O(n*n)(quadratic time) 
*/
#include "PlayList.h"
#include "Song.h"

#include<iostream>
using std::cout;
using std::cin;
using std::endl;
using std::getline;

int main(){
    int userChoice = -1;
    PlayList songs; //creating the playlist object
    std::cout<<"1 - Enter a song in the play list at a given position \n2 - Remove a song from the play list at a given position \n3 - Swap two songs in the play list \n4 - Print all the songs in the play list \n5 - Quit\n\n";
    //loop continues run until the user inputs 5(quit) as the userChoice
    while(userChoice!=5){
        std::cout<<"Menu:"<<std::endl;
        std::cout<<"Enter 1 (insert), 2 (remove), 3 (swap), 4 (print) or 5 (quit): ";    
        std::cin>>userChoice;
        // initializing input variables
        string songName="";
        string artist="";
        int length=0;
        int pos=-1;
        //if the user wants to insert a node
        if(userChoice == 1){
            //getting necessary input
            std::cout<<"Song name: ";
            std::getline(cin>>std::ws,songName);
            std::cout<<"Artist: ";
            std::getline(cin>>std::ws,artist);
            // std::cout<<artist<<std::endl;
            std::cout<<"Length: ";
            std::cin>>length;
            //if the it's the first song, the printed information is different
            if(songs.size()==0){
                while(pos!=1){
                    std::cout<<"Position(1): ";
                    std::cin>>pos;    
                }
            }
            else{
                //prompting the user for a valid input
                while(pos<0||(unsigned)pos>songs.size()+1){
                    std::cout<<"Position (1 to "<<songs.size()+1<<"):";
                    std::cin>>pos;
                }
            }    
                 
            Song newSong = Song(songName,artist,length); // creating a song object using the inputs
            songs.insert(newSong,pos-1); // inserting the node in the playlist
            std::cout<<"You entered "<<songName<< " at position "<<pos<<" in the playlist"<<std::endl;
        }
        //if the user wants to remove a node
        else if(userChoice == 2){
            //it is is not possible to remove when the playlisy is empty
            if(songs.size()==0){
                std::cout<<"Nothing to remove, Playlist is empty"<<std::endl;
            }
            //if the playlist is not empty
            else{
                //when there's just a single song in the playlist
                if(songs.size()==1){
                    while(pos!=1){
                    std::cout<<"Position(1): ";
                    std::cin>>pos;    
                }
                }
                else{
                    pos=0;
                    //prompting the user for a valid input
                    while(pos<=0||(unsigned)pos>songs.size()){
                        std::cout<<"Position(1 to "<<songs.size()<<"):";
                        std::cin>>pos;
                    }
                
                }
                Song deletedSong = songs.remove(pos-1); // receiving the song object of the deleted node
                std::cout<<"You removed "<<deletedSong.getName()<<" from the playlist"<<std::endl;
            }
                    
            
        }
        //if the user wants to swap
        else if(userChoice==3){
            //it is impossible to swap when there's less than 2 songs in the playlist
            if(songs.size()<2){
                std::cout<<"Not enough songs to swap"<<std::endl;
            }
            //otherwise, we can swap
            else{
                int pos2=-1;
                //prompting the user for a valid input
                while(pos<=0||(unsigned)pos>songs.size()){
                    std::cout<<"Swap song at position(1 to "<<songs.size()<<"):";
                    std::cin>>pos;
                }    
                //prompting the user for a valid input
                while(pos2<=0||(unsigned)pos2>songs.size()){
                    std::cout<<"with the song at position(1 to "<<songs.size()<<"):";
                    std::cin>>pos2;
                }
                //we cannot swape given a single node
                if(pos==pos2){
                    std::cout<<"This is not a swap!"<<std::endl;
                    continue;
                }
                songs.swap(pos-1,pos2 -1);//swapping nodes
                std::cout<<"You swapped the songs at positions "<<pos<<" and "<<pos2<<std::endl;
            }
        }
        //when the user wants to print the playlist
        else if(userChoice==4){
            int i;
            //we cannot print when the playlost is empty
            if(songs.size()==0){
                std::cout<<"Playlist is Empty"<<std::endl;
            }
            //otherwise, we loop through the list to print the sonsg
            else{
                for(i=1;(unsigned)i<=songs.size();i++){
                    Song getSong = songs.get(i-1); // gets the song object
                    std::cout<< i<<" "<<getSong.getName()<<" ("<<getSong.getArtist()<<") " << getSong.getLength()<<"s"<<std::endl;
                }
                std::cout<<"There are "<<songs.size()<<" songs in the play list."<<std::endl;
            }    

        }
        else{}
        

    }
    std::cout<<"You have chosen to quit the program."<<std::endl;
    

}