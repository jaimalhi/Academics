//song.h
#ifndef SONG_H
#define SONG_H

#include "database.h"
#include "cmpt_error.h"
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <cctype>
#include <algorithm>
using namespace std;

//A class that stores a single database record, an individual song
class Song : public Database { //Song inherits publicly from Database
private:
    string name; //song name
    string artist; //artist name
    int date; //length in seconds
    char rating; //rating (Explicit or not)
public:
    Song(); //default constructor

    //Gather all pieces of data for a record
    string get_name();
    string get_artist();
    int get_date();
    char get_rating();
    void add_record();

    //Store the single record into database
    void to_db();

    ~Song();
};

#endif