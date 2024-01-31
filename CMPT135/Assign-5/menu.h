//menu.h
#ifndef MENU_H
#define MENU_H

#include "song.h"
#include "cmpt_error.h"
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <ncurses.h>
using namespace std;

//represents a menu of choices that the user can choose from
class Menu : public Song { //Menu inherits publicly from Song
private:
    char input;
public:
    //Default Constructor
    Menu();

    //Starting Menu
    void start_menu();

    //Set what happens for each input and allow invalid choice
    void read_input();

    //User menu options
    void add_song();
    void find_song();
    void del_song();
    void list_song();
    void quit_db();

    ~Menu();
};

#endif