// evenwins.cpp

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Gamestate {
    int marbles_in_middle = -1;
    int human_marbles     = -1;
    int computer_marbles  = -1;
    int total = 0; //total games played
    int cWin = 0; //computer wins
    int hWin = 0; //human wins
};

//Enumerator
enum class Player {
    human,
    computer
};

Player whose_turn;


void welcome_screen() {
    cout << "+-----------------------+\n";
    cout << "| Welcome to Even Wins! |\n";
    cout << "+-----------------------+\n";
    cout << "Even Wins is a two-person game. You start with\n";
    cout << "27 marbles in the middle of the table.\n";
    cout << "\n";
    cout << "Players alternate taking marbles from the middle.\n";
    cout << "A player can take 1 to 4 marbles on their turn, and\n";
    cout << "turns cannot be skipped. The game ends when there are\n";
    cout << "no marbles left, and the winner is the one with an even\n";
    cout << "number of marbles.";
    cout << "\n";
}

string marbles_str(int n) {
    if (n == 1) return "1 marble";
    return to_string(n) + " marbles";
}

void choose_first_player() {
   for (;;) {
        cout << "\nDo you want to play first? (y/n) --> ";
        string ans;
        cin >> ans;
        if (ans == "y") {
            whose_turn = Player::human;
            return;
        } else if (ans == "n") {
            whose_turn = Player::computer;
            return;
        } else {
            cout << "\nPlease enter 'y' if you want to play first,\n";
            cout << "or 'n' if you want to play second.\n";
        }
    }
} // choose_first_player

void next_player() {
    //Using the ? : conditional operator -> var = (condition) ? if_true : if_false;
    whose_turn = (whose_turn == Player::human) ? Player::computer : Player::human;
}

void print_board(Gamestate& gState) {
    cout << "\n";
    cout << " marbles in the middle: " << gState.marbles_in_middle 
         << " " << string(gState.marbles_in_middle, '*') << "\n";
    cout << "    # marbles you have: " << gState.human_marbles << "\n";
    cout << "# marbles computer has: " << gState.computer_marbles << "\n";
    cout <<  "\n";
}

// returns true if s is an int, and false otherwise
// https://www.cplusplus.com/reference/string/stoi/
bool is_int(const string& s) {
    try {
        stoi(s); // throws an invalid_argument exception if conversion fails
        return true;
    } catch (...) {
        return false;
    }
}

void human_turn(Gamestate& gState) {
    // get number in range 1 to min(4, marbles_in_middle)
    int max_choice = min(4, gState.marbles_in_middle);
    cout << "It's your turn!\n";
    for(;;) {
        cout << "Marbles to take? (1 - " << max_choice << ") --> ";
        string s;
        cin >> s;
        if (!is_int(s)) {
            cout << "\n  Please enter a whole number from 1 to " << max_choice
                 << "\n";
            continue;
        }

        // convert s to an int so it can be compared
        int n = stoi(s);
        if (n < 1) {
            cout << "\n  You must take at least 1 marble\n";
            continue;
        }
        if (n > max_choice) {
            cout << "\n  You can take at most " << marbles_str(max_choice)
                 << "\n";
            continue;
        }

        cout << "\nOkay, taking " << marbles_str(n) << " ...\n";
        gState.marbles_in_middle -= n;
        gState.human_marbles += n;

        return;
    } // for
} // human_turn

void computer_turn(Gamestate& gState) {
    cout << "It's the computer's turn ...\n";
    int max_choice = min(4, gState.marbles_in_middle);

    // choose at random
    int n = 1 + rand() % max_choice;
    cout << "Computer takes " << marbles_str(n) << " ...\n";
    gState.marbles_in_middle -= n;
    gState.computer_marbles += n;
}

void computer_taunts(){ 
    srand(time(0));

    const string t1 = "The computer wins: tremble before it's mighty brain!\n";
    const string t2 = "The computer wins: swim in a pool of your regrets!\n";
    const string t3 = "The computer wins: time to shut down your machine!\n";
    const string t4 = "The computer wins: become a bird and fly away!\n";
    const string t5 = "The computer wins: to bad these taunts have to be kid-friendly!\n";

    const string taunts[5] = {t1, t2, t3, t4, t5};

    int rIndex = rand() % 5;
    cout << taunts[rIndex] << endl;
}

void game_over(Gamestate& gState) {
    cout << "\n";
    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"
         << "!! All the marbles are taken: Game Over !!\n"
         << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
    print_board(gState);
    if (gState.human_marbles % 2 == 0) {
        gState.hWin++;
        cout << "You are the winner! Congratulations!\n";
    } else {
        gState.cWin++;
        computer_taunts();
        //cout << "The computer wins: tremble before it's mighty brain!\n";
    }
    gState.total = gState.cWin + gState.hWin;

    cout << "\nStatistics\n----------\n";
    cout << "  total games: " << gState.total << endl;
    cout << "   human wins: " << gState.hWin << endl;
    cout << "computer wins: " << gState.cWin << endl;
}

void play_game(Gamestate& gState) {
    // initialize the game state
    gState.marbles_in_middle = 27;
    gState.human_marbles = 0;
    gState.computer_marbles = 0;
    print_board(gState);

    for (;;) {
        if (gState.marbles_in_middle == 0) {
            game_over(gState);
            return;
        } else if (whose_turn == Player::human) {
            human_turn(gState);
            print_board(gState);
            next_player();
        } else if (whose_turn == Player::computer) {
            computer_turn(gState);
            print_board(gState);
            next_player();
        }
    } // for
} // play_game

int main() {
    srand(time(NULL));
    Gamestate gamestate;

    welcome_screen();

    for(;;) {
        choose_first_player();
        play_game(gamestate);

        // ask if the user if they want to play again
        cout << "\nWould you like to play again? (y/n) --> ";
        string again;
        cin >> again;
        if (again == "y") {
            cout << "\nOk, let's play again ...\n";
        } else {
            cout << "\nOk, thanks for playing ... goodbye!\n";
            return 0;
        }
    } // for
} // main
