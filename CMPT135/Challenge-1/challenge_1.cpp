//challenge_1.cpp
#include "cmpt_error.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//using command line
// make challenge_1  --> to compile
// ./challenge_1 numbers.txt --> to take file input

//Function Prototypes
int sumOfNums(fstream& file);

//Main
int main(int argc, char *argv[]){
    fstream file;

    ///check that one or more filename arguments provided
    if (argc < 2) {
            cout << "Wrong number of arguments\n";
            return -1;
        }

    //argv[1] is the first command-line arugment, ie. the file name
    file.open(argv[1], ios::in);

    cout << "Sum of numbers not containing three = " << sumOfNums(file) << endl;

    return 0;
}

//Find the sum of number that doesnt/does contain the digit 3
int sumOfNums(fstream& file){
    char three = '3';
    int sum = 0;
    string line;

    //get() reads every line of the command line
    while(getline(file, line)){ 
        //find() accepts a char, and returns char's position. If char isn't in the string it returns "string::npos"
        if(line.find(three) == string::npos){
            //stoi() changes string to an integer value -> included in <string>
            sum += stoi(line); 
        }
    }
    return sum;
}

//Bonus Ideas:
//To sum only numbers that contain the digit three I would change the '==' in my if statement on 
//line 45 to a '!=' as this would now only sum the numbers that were found to have three in them