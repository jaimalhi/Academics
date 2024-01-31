// challenge_3.cpp
#include "cmpt_error.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//Function Prototypes
int all_vowels(fstream& file);

int main(int argc, char *argv[]) {
	fstream file;

    ///check that one or more filename arguments provided
    if (argc < 2) {
            cout << "Wrong number of arguments\n";
            return -1;
        }

    //argv[1] is the first command-line arugment, ie. the file name
    file.open(argv[1], ios::in);
	
	//cout << all_vowels(file);

	int numOfWords = all_vowels(file);
    cout << numOfWords << " words contain all five vowels exactly once" << endl;

    return 0;
}

int all_vowels(fstream& file){ //aahed
	string line;
	const int numOfVowels = 5;
	int allVowels = 0;

	//While there are lines in the file
    while(getline(file, line)){ 
		char arr[numOfVowels] = {'a','e','i','o','u'}; 
		int i, j;
		int count = 0;

		for(i = 0;i < line.size();i++){
			if(count >= 5){
				//if all 5 vowels have been found but there are repitions following
				if(line[i] == 'a' || line[i] == 'e' || line[i] == 'i' || line[i] == 'o' || line[i] == 'u'){
					count--;
				}
			}
			//Nested Loop to compare letters to array of vowels
			for(j = 0;j < numOfVowels ;j++){
				if(line[i] == arr[j]){
					//if found vowel once, ignore that vowel
					arr[j] = '+';
					count++; 
				}
			}
		}
		if(count >= 5){
			allVowels++;
		}
	}
	return allVowels;
}