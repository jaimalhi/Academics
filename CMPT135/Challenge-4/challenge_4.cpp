// challenge_4.cpp, get top 3 most frequently occurring items
#include "cmpt_error.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//Function Declarations
void count_items(fstream& file);

int main(int argc, char *argv[]) {
	fstream file;

    ///check that one or more filename arguments provided
    if (argc < 2) {
		cout << "Wrong number of arguments\n";
		return -1;
    }

    //argv[1] is the first command-line arugment, ie. the file name
    file.open(argv[1], ios::in);

	count_items(file);
}

//Count Number of times item appears
void count_items(fstream& file){
	vector <string> items;
	string word;

	//While there are words in the file, get each word
    while(file >> word){ 
		items.push_back(word);
	}

	//Sort the vector of items
	std::sort(items.begin(), items.end());
	int size = items.size(); 

	//fill with 0's, this vector is used to determine if a 
	//element has been seen already or not
	vector <int> seen(size, 0);

	//Occurance counters
	int first = 1;
	int fIndex;
	int second = 1;
	int sIndex;
	int third = 1;
	int tIndex;

	//Main loops
	for(int i = 0;i < size;i++){
		if(seen[i] == 0){
			int count = 0;
			for(int j = i;j < size;j++){
				if(items[j] == items[i]){
					count += 1;
					seen[j] = 1;
				}
			}
			cout << "[" << items[i] << "] appears [" << count << "] times" << endl;

			//first most occuring item
			if(count > first) { 
				first = count;
				fIndex = i;
			}
			//second most occuring item
			if(count < first && count > second) {
				second = count;
				sIndex = i;	
			}
			 //third most occuring item
			if(count < second && count > third) {
				third = count;
				tIndex = i; 	
			}
		}
	}
	//Why is the third value 11 not 12
// 	cout << "First: " << items[fIndex] << " " << first << " times \t index: " << fIndex << endl;
// 	cout << "Second: " << items[sIndex] << " " << second << " times \t index: " << sIndex << endl;
// 	cout << "Third: " << items[tIndex] << " " << third << " times \t index: " << tIndex << endl;
}

/*
[deluxe_carrot] appears [15] times
[medium_apple] appears [13] times
[green_apple] appears [12] times
[massive_chips] appears [12] times
[large_cheese] appears [11] times
*/