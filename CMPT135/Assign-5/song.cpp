//song.cpp
#include "song.h"
using namespace std;

//Create definitions here
Song::Song(){}; 

string Song::get_name(){
    while(true){
        cout << "Enter the name of the Song you're adding: ";
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
    return name;
}

string Song::get_artist(){
    while(true){
        cout << "Enter the name of the Artist: ";
        if(!(getline(cin, artist))){ //Invalid Inputs
            cout << "Invalid Input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else{
            break;
        }
    }
    return artist;
}

int Song::get_date(){
    while(true){
        cout << "Enter the songs release year: ";
        if(!(cin >> date)){ //Invalid Inputs
            cout << "Invalid Input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        //First recording of music was in 1888
        else if(date < 1888 || date > 2022){
            cout << "Invalid Input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else{
            break;
        }
    }
    return date;
}   

char Song::get_rating(){
    cout << "A songs rating is explicit (E) or clean (C), ";

    while(true){
        cout << "Enter the songs rating: ";
        if(!(cin >> rating)){ //Invalid Inputs
            cout << "Invalid Input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if(rating == 'c' || rating == 'C'){
            rating = 'C';
            break;
        }
        else if(rating == 'e' || rating == 'E'){
            rating = 'E';
            break;
        }
        else{
            cout << "Invalid Input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
    return rating;
}

void Song::add_record(){
    get_name();
    get_artist();
    get_date();
    get_rating();
    to_db();
}

void Song::to_db(){
    Database::add_records(name, artist, date, rating);
}

Song::~Song(){}