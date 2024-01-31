//Main file
#include "Song.h"
#include "PlayList.h"
#include <iostream>
#include <string>
using namespace std;

//Function declarations
void start_menu();
void user_input(PlayList& list);
void insert_song(PlayList& list);
void remove_song(PlayList& list);
void swap_song(PlayList& list);
void print_song(PlayList& list);
unsigned int pos_checker(PlayList& list);
unsigned int insert_posChecker(PlayList& list);

int main(){
    PlayList list;
    start_menu();
    user_input(list);
}

//Starting menu
void start_menu() {
    cout << "\nMenu:\n";
    cout << "1 - Enter a song in the play list\n";
    cout << "2 - Remove a song from the play list\n";
    cout << "3 - Swap two songs in the play list\n";
    cout << "4 - Print all the songs in the play list\n";
    cout << "5 - Quit\n";
}

//Take user input for start menu
void user_input(PlayList& list){
    int input;
    while(true){
        cout << "\nEnter 1 (insert), 2 (remove), 3 (swap), 4 (print) or 5 (quit): ";
        if(!(cin >> input)){ //Invalid Inputs
            cout << "Invalid Input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if(input == 1){
            insert_song(list);
        }
        else if(input == 2){
            remove_song(list);
        }
        else if(input == 3){
            swap_song(list);
        }
        else if(input == 4){
            print_song(list);
        }
        else if(input == 5){
            //Quit program
            cout << "You have chosen to quit the program!\n";
            return;
        }
        else{
            cout << "Invalid Input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
    cin.clear();
    cin.ignore(1000, '\n');
}

//Insert a song at pos, O(N) same as the insert function
//within PlayList.cpp since this calls insert()
void insert_song(PlayList& list){
    string name;
    string artist;
    int length;
    unsigned int pos;

    while(true){ //Input checking for song name
        cout << "Song Name: ";
        cin.clear();
        cin.ignore(1000, '\n');
        if(!(getline(cin, name))){ //Invalid Inputs
            cout << "Invalid Input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else{
            break;
        }
    }

    while(true){ //Input checking for artist name
        cout << "Artist Name: ";
        if(!(getline(cin, artist))){ //Invalid Inputs
            cout << "Invalid Input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else{
            break;
        }
    }
    
    while(true){ //Input checking for length
        cout << "Song Length: ";
        if(!(cin >> length)){ //Invalid Inputs
            cout << "Invalid Input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if(length <= 0){
            cout << "Invalid Input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else{
            break;
        }
    }
    cin.clear();
    cin.ignore(1000, '\n');

    pos = insert_posChecker(list);
    Song sng(name, artist, length);
    list.insert(sng, pos-1);
    cout << "You entered " << name << " at position " << pos << endl;
}

//Song at position pos is removed and returned, O(N) same as the remove
//function within PlayList.cpp since this calls remove()
void remove_song(PlayList& list){
    unsigned int pos = pos_checker(list);
    Song rm_song = list.remove(pos-1);
    cout << "You removed " << rm_song.getName() << " from the playlist\n";
}

//Swap two songs to pos1 and pos2, O(N) same as the swap function within
//PlayList.cpp since this calls swap()
void swap_song(PlayList& list){ 
    unsigned int pos1, pos2;
    cout << "Swap song at ";
    pos1 = pos_checker(list);
    cout << "With the song at ";
    pos2 = pos_checker(list);
    list.swap(pos1-1, pos2-1);

    cout << "You swapped songs at positions " << pos1 << " and " << pos2 << endl;
}

//Printing list of songs, O(N^2) since we have nested for loops, this 
//being the initial for loop and the loop used inside the get function
void print_song(PlayList& list){
    for(int i = 0;i < list.size();i++){
        cout << i+1 << " " << list.get(i).getName() << " ("
             << list.get(i).getArtist() << ") "
             << list.get(i).getLength() << "s\n";
    }
    cout << "There are " << list.size() << " songs in the playlist\n";
}

//Input checking for swap() and remove() inputs, O(1) since
//this is checking a single value for each input
unsigned int pos_checker(PlayList& list){
    string options = "ERROR";
    unsigned int pos;

    if(list.size() < 1){
        options = "1";
    }
    else{
        options = "1 to " + to_string(list.size());
    }

    while(true){ 
        cout << "position (" << options << "): ";
        if(!(cin >> pos)){ //Invalid Inputs
            cout << "Invalid Input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if(pos <= 0){
            cout << "Invalid Input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if(pos < 1 || pos > list.size()+1){
            cout << "Invalid Position! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else{
            break;
        }
    }
    cin.clear();
    cin.ignore(1000, '\n');
    return pos;
}

//Input checking for insert() inputs, O(1) since
//this is checking a single value for each input
unsigned int insert_posChecker(PlayList& list){
    string options = "ERROR";
    unsigned int pos;

    if(list.size() < 1){
        options = "1";
    }
    else{
        options = "1 to " + to_string(list.size()+1);
    }

    while(true){ 
        cout << "position (" << options << "): ";
        if(!(cin >> pos)){ //Invalid Inputs
            cout << "Invalid Input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if(pos <= 0){
            cout << "Invalid Input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if(pos < 1 || pos > list.size()+1){
            cout << "Invalid Position! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else{
            break;
        }
    }
    cin.clear();
    cin.ignore(1000, '\n');
    return pos;
}

