//database.h
#ifndef DATABASE_H
#define DATABASE_H

#include "cmpt_error.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <fstream>
using namespace std;

//Stores all the records, The methods of this class are probably where
//you want to implement the searching and sorting functions.
class Database {
private:
    vector<string> name;
    vector<string> artist;
    vector<int> date;
    vector<char> rating;
public:
    Database(); //Default Constructor

    void check_record_size() const;
    void add_records(string n, string a, int d, char r); 

    void find_rName() const;
    void find_rArtist() const;
    void find_rDate() const;
    void find_rRating() const;

    void del_record(vector<int> v);
    void del_rName();
    void del_rArtist();
    void del_rDate();
    void del_rRating();

    void list_byName() const;
    void list_byArtist() const;
    void list_byDate() const;
    void list_byRating() const;

    void print_unordered_records() const;
    void print_single_record(int i) const;

    void init_database();
    void save_records();

    ~Database();
};

string trim(const string& s);

#endif