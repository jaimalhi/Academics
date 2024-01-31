//menu.cpp
#include "menu.h"
using namespace std;

//Create definitions here
Menu::Menu(){}; 

void Menu::start_menu(){
    initscr(); //initialize the screen
    noecho();
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    //Create a window in memory
    WINDOW* win = newwin(9, xMax-12, yMax-yMax, 3);
    refresh();

    //draw box on screen
    box(win, 0, 0);
    refresh();
    mvwprintw(win, 1, 2, "Welcome to the Song Database!");
    mvwprintw(win, 7, 2, "Use the arrow keys and hit enter to choose!");
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

    wrefresh(win);
    if(choices[highlight] == choices[0]){
        //mvprintw(9, 3, "Choosing to Add a song (Enter)\t");
        add_song();
    }
    else if(choices[highlight] == choices[1]){
        //mvprintw(9, 3, "Choosing to Find a song (Enter)\t");
        find_song();
    }
    else if(choices[highlight] == choices[2]){
        //mvprintw(9, 3, "Choosing to Delete a song (Enter)\t");
        del_song();
    }
    else if(choices[highlight] == choices[3]){
        //mvprintw(9, 3, "Choosing to List songs (Enter)\t");
        list_song();
    }
    else if(choices[highlight] == choices[4]){
        //mvprintw(9, 3, "Choosing to Quit (Enter)\t\t");
        quit_db();
    }
    endwin(); //deallocate memory and ends ncurses
}

void Menu::add_song(){
    endwin(); //deallocate memory and ends ncurses
    Song::add_record();
    getch();
    start_menu();
}

void Menu::find_song(){
    endwin(); //deallocate memory and ends ncurses
    cout << "\nFind a Song\n";
    cout << "-------------------\n";
    cout << "Search by:\n";
    cout << "  (N)ame of song\n";
    cout << "  (A)rtist of song\n";
    cout << "  (D)ate released\n";
    cout << "  (R)ating of song\n";
    cout << "(M)ain menu\n";
    cout << "-------------------\n";

    while(true){
        cout << "Enter the letter of your choice: ";
        if(!(cin >> input)){ //Invalid Inputs
            cout << "Invalid Input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if(input == 'n' || input == 'N'){
            //find records by song name
            Database::find_rName();
            break;
        }
        else if(input == 'a' || input == 'A'){
            //find records by artist name
            Database::find_rArtist();
            break;
        }
        else if(input == 'd' || input == 'D'){
            //find records by date
            Database::find_rDate();
            break;
        }
        else if(input == 'r' || input == 'R'){
            //find records by rating
            Database::find_rRating();
            break;
        }
        else if(input == 'm' || input == 'M'){
            //Return to main menu
            start_menu();
            break;
        }
        else{
            cout << "Invalid input! ";
			cin.clear();
			cin.ignore(1000, '\n');
        }
    }
    getch();
    start_menu();
}

void Menu::del_song(){
    endwin(); //deallocate memory and ends ncurses
    cout << "\nDelete a Record\n";
    cout << "-------------------\n";
    cout << "Search by:\n";
    cout << "  (N)ame of song\n";
    cout << "  (A)rtist of song\n";
    cout << "  (D)ate released\n";
    cout << "  (R)ating of song\n";
    cout << "(M)ain menu\n";
    cout << "-------------------\n";

    while(true){
        cout << "Enter the letter of your choice: ";
        if(!(cin >> input)){ //Invalid Inputs
            cout << "Invalid Input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if(input == 'n' || input == 'N'){
            //find records by song name
            Database::del_rName();
            break;
        }
        else if(input == 'a' || input == 'A'){
            //find records by artist name
            Database::del_rArtist();
            break;
        }
        else if(input == 'd' || input == 'D'){
            //find records by date
            Database::del_rDate();
            break;
        }
        else if(input == 'r' || input == 'R'){
            //find records by rating
            Database::del_rRating();
            break;
        }
        else if(input == 'm' || input == 'M'){
            //Return to main menu
            start_menu();
            break;
        }
        else{
            cout << "Invalid input! ";
			cin.clear();
			cin.ignore(1000, '\n');
        }
    }
    getch();
    start_menu();
}

void Menu::list_song(){
    endwin(); //deallocate memory and ends ncurses
    cout << "\nList by field\n";
    cout << "-------------------\n";
    cout << "List by:\n";
    cout << "  (N)ame of song\n";
    cout << "  (A)rtist of song\n";
    cout << "  (D)ate released\n";
    cout << "  (R)ating of song\n";
    cout << "  (U)nordered Records\n";
    cout << "(M)ain menu\n";
    cout << "-------------------\n";

    while(true){
        cout << "Enter the letter of your choice: ";
        if(!(cin >> input)){ //Invalid Inputs
            cout << "Invalid Input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if(input == 'n' || input == 'N'){
            //list records by song name
            Database::list_byName();
            break;
        }
        else if(input == 'a' || input == 'A'){
            //list records by artist name
            Database::list_byArtist();
            break;
        }
        else if(input == 'd' || input == 'D'){
            //list records by date
            Database::list_byDate();
            break;
        }
        else if(input == 'r' || input == 'R'){
            //list records by rating
            Database::list_byRating();
            break;
        }
        else if(input == 'u' || input == 'U'){
            //List unordered records
            Database::print_unordered_records();
            break;
        }
        else if(input == 'm' || input == 'M'){
            //Return to main menu
            start_menu();
            break;
        }
        else{
            cout << "Invalid input! ";
			cin.clear();
			cin.ignore(1000, '\n');
        }
    }
    getch();
    start_menu();
}

void Menu::quit_db(){
    endwin(); //deallocate memory and ends ncurses
    cout << "============================\n";
    cout << " Quiting and Saving records\n";
    cout << "============================\n";
    Database::save_records();
}

Menu::~Menu(){}