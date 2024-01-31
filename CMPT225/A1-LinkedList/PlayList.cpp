// Write your name and date here
#include "PlayList.h"
#include <iostream> 
using std::cout;

//simplifying PlayListNode usage
typedef PlayListNode node; 

// PlayList method implementations go here:

//default constructor, O(1) since this is just assignment of variables
PlayList::PlayList() : NumOfSongs(0), head(nullptr) {} 

//Copy Constructor, O(N) since this iterates through
//and copies every node present in the list
PlayList::PlayList(const PlayList& pl) { 
    memCopy(pl);
} 

//Destructor, O(N) since this iterates through the entire
//list once while deleting every node
PlayList::~PlayList(){ 
    memClear();
}

//op-overload=, O(N) similar to the copy constructor, this iterates
//through and copies every node present in the list
PlayList& PlayList::operator=(const PlayList & pl){ 
    if(this != &pl){ //ptr to calling object
        memClear();
        memCopy(pl); 
    }
    return *this;
}

//Insert a song at pos, O(N) since it iterates until pos and in worst
//case it must iterate through the entire list to insert the value
void PlayList::insert(Song sng, unsigned int pos){
    NumOfSongs++; //increase number of songs
    node* prev = nullptr;
    node* curr = head;
    if(pos == 0){
        node* newNode = new node(sng, head);
        head = newNode;
        return;
    }
    while(curr != nullptr && pos--){
        prev = curr;
        curr = curr->next;
    }
    node* newNode = new node(sng, curr);
    prev->next = newNode;
}

//Song at position pos is removed and returned, O(N) similar to insert except
//this iterates until pos and removes a node in the list, worst case it must
//iterate through the entire list to reach last node
Song PlayList::remove(unsigned int pos){ 
    NumOfSongs--; //decrease number of songs
    node* temp = head;
    //If list is empty
    if(head == nullptr){ 
        return head->song;
    }
    //if head is being removed
    if(pos == 0){ 
        head = temp->next; //change head
        Song sng = temp->song; //copy song
        delete temp; //delete old head
        return sng;
    }
    //find prev node of the node to be removed
    for(int i = 0; temp != nullptr && i < pos-1;i++){
        temp = temp->next;
    }
    //temp->next needs to get removed, need a pointer to the following node
    node* next = temp->next->next;
    //Copy song from temp->next
    Song sng = temp->next->song;
    //delete the removed node from the list
    delete temp->next;
    //Unlink the removed node from the list
    temp->next = next;

    return sng;
}

//Songs at positions pos1 and pos2 are swapped, O(N) since this is iterating
//through the list until nodes at pos1 and pos2 are found, worst case the
//nodes are at the end of the list
void PlayList::swap(unsigned int pos1, unsigned int pos2){ 
    node* node1 = head;
    node* node2 = head;

    //Move to where the node values are
    for(int i = 0;i < pos1;i++){
        node1 = node1->next;
    }
    for(int i = 0;i < pos2;i++){
        node2 = node2->next;
    }

    //Swap the values of the two nodes
    Song val = node1->song;
    node1->song = node2->song;
    node2->song = val;
}

//returns the Song at position pos, O(N) iterating through a single loop
//to reach a node in the list, worst case node is at the end of the list
Song PlayList::get(unsigned int pos) const {
    node* temp = head;
    for(int i = 0;i < pos;i++){
        if(temp == nullptr){
            cout << "Out of Index\n";
            break;
        }
        temp = temp->next;
    }
    return temp->song;
}

//returns the number of songs in the PlayList, O(1) since this is checking
//a single value and returning a single value
unsigned int PlayList::size() const {
    if(head == nullptr){
        return 0;
    }
    return NumOfSongs;
}

//Deallocates memory of list, O(N) as stated in the Destructor
void PlayList::memClear(){
    while(head != nullptr){
        node* temp = head;
        head = head->next;
        delete temp;
    }
}

//Creates a deep copy of the list, O(N) as stated in the Copy Cons.
void PlayList::memCopy(const PlayList& pl){
    head = nullptr;
    node* og = pl.head; //og = original
    if(og != nullptr){
        //Copy start of list
        head = new node(og->song);
        og = og->next;
        node* temp = head;

        //Copy rest of list
        while(og != nullptr){
            node* newNode = new node(og->song);
            temp->next = newNode;
            temp = temp->next;
            og = og->next;
        }
    }
}