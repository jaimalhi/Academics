//ncurses_demo.cpp
#include <ncurses.h>
#include <string>
#include <iostream>
using namespace std;
//g++ ncurses_demo.cpp -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g -lncurses -o ncurses_demo

string get_name();

int main() {
    initscr(); //initialize the screen
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    //Create a window in memory
    WINDOW* win = newwin(9, xMax-12, yMax-yMax, 3);
    refresh();

    //draw box on screen
    box(win, 0, 0);
    refresh();
    mvwprintw(win, 1, 2, "Welcome to the Song Database!");
    mvwprintw(win, 7, 2, "Hit enter to choose!");
    wrefresh(win);

    //Read user input, allow using arrow keys
    keypad(win, true);
    string choices[5] = {"Add a song","Find a song","Delete a song", "List songs","Quit"};
    int choice;
    int highlight = 0;

    //Use arrow keys to select
    while(true){
        //User has 5 choices
        for(int i = 0;i < 5;i++){
            if(i == highlight) wattron(win, A_REVERSE);
            mvwprintw(win, i+2, 4, choices[i].c_str());
            wattroff(win, A_REVERSE);
        }
        choice = wgetch(win);

        switch(choice){
            case KEY_UP:
                highlight--;
                if(highlight == -1) highlight = 0;
                break;
            case KEY_DOWN:
                highlight++;
                if(highlight == 5) highlight = 4;
                break;
            default:
                break;
        }
        //If user hits enter, confirm choice and break while
        if(choice == 10) break;
    }

    if(choices[highlight] == choices[0]){
        mvprintw(9, 3, "Choosing to Add a song");
        move(10,3);
        add_song();
    }
    else if(choices[highlight] == choices[1]){
        mvprintw(9, 3, "Choosing to Find a song");
        move(10,3);
        find_song();
    }
    else if(choices[highlight] == choices[2]){
        mvprintw(9, 3, "Choosing to Delete a song");
        move(10,3);
        del_song();
    }
    else if(choices[highlight] == choices[3]){
        mvprintw(9, 3, "Choosing to List songs");
        move(10,3);
        list_song();
    }
    else if(choices[highlight] == choices[4]){
        mvprintw(9, 3, "Choosing to Quit");
        move(10,3);
        quit_db();
    }

    refresh();
    getch(); //read a character to pause the program
    endwin(); //deallocate memory and ends ncurses
}

string get_name(){
    endwin(); //deallocate memory and ends ncurses
    string name;
    while(true){
        cout << "Enter the Songs name: ";
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