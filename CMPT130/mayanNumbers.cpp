//Mayan Numbers
#include <iostream>
#include <istream>
#include <cstdlib>
#include <ctime>
using namespace std;

//Function Prototypes
string printMayanNumber(int number);
string mayanNums(int number);
string twenties(int number);
string fourHundrends(int number);
string eightThousands(int number);
void getThreeNums(int &gNum, int &wrong1, int &wrong2);
void startGame(int gNum, int wrong1, int wrong2);
void guessABC(int numGuess, int control, string mAnswer);
void startMsg();
void playAgain();
int initalNum();

int counter = 0; //to count how many times main is called
int replayControl = 0;

int main(){
    cout << "5212\n" << printMayanNumber(5212) << endl;

    //Content for Number Game
    int correctA, wrongA1, wrongA2;

    if(counter == 0){
        startMsg();
    }
    counter++;

    getThreeNums(correctA, wrongA1, wrongA2); //Pass by Reference to get three values, also initial input
    startGame(correctA, wrongA1, wrongA2);

    return 0;
}

void startMsg(){
    cout << "MAYAN NUMBER GAME" << "\n=================" << endl;
    cout << "Welcome to the Mayan Number Game!" << endl;
    cout << "Enter a number greater than 10. The game will choose a number less than or equal to what you entered. ";
    cout << "You will then have to match the decimal number to its Mayan equivalent. Or you can enter a number less ";
    cout << "than 10 to exit: ";
}

int initalNum(){
    int num;

    while(true){
        if(!(cin >> num)){
            cout << "Invalid input! Enter another number, or less than 10 to exit: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if(num >= 10){
            cin.clear();
            cin.ignore();
            return num;
        }
        else if(num < 10){
            cout << " -- EXITING -- " << endl;
            exit(0);
        }
        else{
            cout << "Invalid input! Enter another number, or less than 10 to exit: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
}

void getThreeNums(int &gNum, int &wrong1, int &wrong2){
    int num;
    if(counter > 1){
        num = replayControl; }
    else {
        num = initalNum(); }

    //Getting all three numbers
    srand(time(0));

    gNum = 4 + rand() % ((num + 1) - 4); //the number to guess Mayan value of

    int min = gNum*0.5;
    int max = gNum*1.5;
    wrong1 = min + (rand() % (max - min + 1)); //first incorrect answer
    wrong2 = min + (rand() % (max - min + 1)); //second incorrect answer

    while(wrong1 == gNum || wrong1 == wrong2){ //preventing duplicates
        wrong1 = min + (rand() % (max - min + 1));
    }
    while(wrong2 == gNum || wrong2 == wrong1){
        wrong2 = min + (rand() % (max - min + 1));
    }
}

void startGame(int gNum, int wrong1, int wrong2){
    //Giving Player Options of a, b, c
    string answer1 = printMayanNumber(gNum);
    string answer2 = printMayanNumber(wrong1);
    string answer3 = printMayanNumber(wrong2);

    char options[3] = {'a','b','c'};
    int randIndex = rand()%3; //generates random number between 0 and 2
    char cAnswer = options[randIndex];
    char l2 = options[1];
    char l3 = options[2];
    int control;

    cout << "Which of these Mayan numbers is equal to " << gNum << "? " << endl;
    if(l2 != cAnswer && l3 != cAnswer){ //Answer is a
        cout << cAnswer << endl << answer1 << endl;
        cout << l2 << endl << answer2 << endl;
        cout << l3 << endl << answer3 << endl;
        control = 1;
    }
    while(l2 == cAnswer){ //Answer is b
        l2 = options[0];
        cout << l2 << endl << answer2 << endl;
        cout << cAnswer << endl << answer1 << endl;
        cout << l3 << endl << answer3 << endl;
        control = 2;
    }
    while(l3 == cAnswer){ //Answer is c
        l3 = options[0];
        cout << l3 << endl << answer3 << endl;
        cout << l2 << endl << answer2 << endl;
        cout << cAnswer << endl << answer1 << endl;
        control = 3;
    }

    guessABC(gNum, control, answer1); //player guessing
}

void guessABC(int numGuess,int control, string mAnswer){
    //Tell player is they are correct or incorrect when guessing
    char guess;

    while(true){
        cout << "Enter a, b, or c: ";
        if(!(cin >> guess)){
            cout << "Invalid input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if(guess == 'a' || guess == 'b' || guess == 'c'){
            cin.clear();
            cin.ignore();
            if(control == 1){
                if(guess == 'a'){
                    cout << "\nCORRECT! Tha Mayan representation of " << numGuess << " is" << endl;
                    cout << mAnswer << endl;
                    playAgain();
                }
                else {
                    cout << "\nINCORRECT! Tha Mayan representation of " << numGuess << " is" << endl;
                    cout << mAnswer << endl;
                    playAgain();
                }
            }
            else if(control == 2){
                if(guess == 'b'){
                    cout << "\nCORRECT! Tha Mayan representation of " << numGuess << " is" << endl;
                    cout << mAnswer << endl;
                    playAgain();
                }
                else {
                    cout << "\nINCORRECT! Tha Mayan representation of " << numGuess << " is" << endl;
                    cout << mAnswer << endl;
                    playAgain();
                }
            }
            else if(control == 3){
                if(guess == 'c'){
                    cout << "\nCORRECT! Tha Mayan representation of " << numGuess << " is" << endl;
                    cout << mAnswer << endl;
                    playAgain();
                }
                else {
                    cout << "\nINCORRECT! Tha Mayan representation of " << numGuess << " is" << endl;
                    cout << mAnswer << endl;
                    playAgain();
                }
            }
        }
        else{
            cout << "Invalid input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
}

void playAgain(){
    int num;

    while(true){
        cout << "Enter another number, or less than 10 to exit: ";
        if(!(cin >> num)){
            cout << "Invalid input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if(num >= 10){
            cin.clear();
            cin.ignore(1000, '\n');
            replayControl = num; //take num value from here as new number
            main();
        }
        else if(num < 10){
            cout << " -- EXITING -- " << endl;
            exit(0);
        }
        else{
            cout << "Invalid input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
}

string printMayanNumber(int number){
    if(number >= 8000){
        return eightThousands(number);
    }
    else if(number >= 400){
        return fourHundrends(number);
    }
    else if(number >= 20){
        return twenties(number);
    }
    else if(number >= 0){
        return mayanNums(number);
    }
    else{
        return "";
    }
}

string mayanNums(int number){
    //Mayan representations of numbers 1-19, with zero being 00
    if(number == 0) return "______\n 00 \n";

    if(number == 1) return "______\n o\n";
    if(number == 2) return "______\n oo\n";
    if(number == 3) return "______\n ooo\n";
    if(number == 4) return "______\n oooo\n";
    if(number == 5) return "______\n ====\n";

    if(number == 6) return "______\n o\n ====\n";
    if(number == 7) return "______\n oo\n ====\n";
    if(number == 8) return "______\n ooo\n ====\n";
    if(number == 9) return "______\n oooo\n ====\n";
    if(number == 10) return "______\n ====\n ====\n";

    if(number == 11) return "______\n o\n ====\n ====\n";
    if(number == 12) return "______\n oo\n ====\n ====\n";
    if(number == 13) return "______\n ooo\n ====\n ====\n";
    if(number == 14) return "______\n oooo\n ====\n ====\n";
    if(number == 15) return "______\n ====\n ====\n ====\n";

    if(number == 16) return "______\n o\n ====\n ====\n ====\n";
    if(number == 17) return "______\n oo\n ====\n ====\n ====\n";
    if(number == 18) return "______\n ooo\n ====\n ====\n ====\n";
    if(number == 19) return "______\n oooo\n ====\n ====\n ====\n";

    return "";
}

string twenties(int number){
    int num = number/20; //Number of 20s in number
    int rem = number%20; //Gets numbers 0-19

    string holdNum = mayanNums(num); //Store mayan versions of numbers in variables
    string holdRem = mayanNums(rem);

    return holdNum + holdRem;
}

string fourHundrends(int number){
    int num = number/400; //Number of 400s in number
    string rem = twenties(number%400); //Gets number of twenties

    string holdNum = mayanNums(num); //Store mayan versions of numbers in variables

    return holdNum + rem;
}

string eightThousands(int number){
    int num = number/8000; //Number of 8000s in number
    string rem = fourHundrends(number%8000); //Gets number of four hundreds

    string holdNum = mayanNums(num); //Store mayan versions of numbers in variables

    return holdNum + rem;
}
