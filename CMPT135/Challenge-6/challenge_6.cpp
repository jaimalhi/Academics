// challenge_6.cpp
#include "cmpt_error.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//Function Declarations
void letter_count(fstream& file);

int main(int argc, char *argv[]) {
	fstream file;

    //check that one or more filename arguments provided
    if (argc < 2) {
		cout << "Wrong number of arguments\n";
		return -1;
    }

    //argv[1] is the first command-line arugment, ie. the file name
    file.open(argv[1], ios::in);
    
    letter_count(file);
}

void letter_count(fstream& file){
    //vec of size 26, initialize all values to 0
    vector <int> count(26, 0);
    char c;

    while(file >> c){
        //[c - 'a'] gives distance between letter ASCII values
        count[c - 'a']++;
    }

    for(int i = 0;i < count.size();i++){
        if(count[i] > 0){
            cout << static_cast<char>(i + 'a') << ": " << count[i] << " times" << endl;
        }
    }
}

//Most occurrences of letters in order: esairontlducgpmhbyfkwvzxjq