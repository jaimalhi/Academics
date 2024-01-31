//a5_main.cpp
#include "song.h"
#include "database.h"
#include "menu.h"

//Main should only exist in this file
int main(){
    Menu menu;
    menu.init_database(); //database.h
    menu.start_menu(); //menu.h
}