// challenge_2.cpp

// You may use only the following #includes in your code:
#include "cmpt_error.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
// You don't need to use them all, but you can't use any others.
// Don't change these in any way.

using namespace std;

//Prototypes
void same_different(fstream& file);

int main(int argc, char *argv[]) {
	fstream file;

    //check that one or more filename arguments provided
    if (argc < 2) {
        cout << "Wrong number of arguments\n";
        return -1;
    }

    file.open(argv[1], ios::in);
	same_different(file);

    return 0;
}

void same_different(fstream& file){
    string line;
	int repeated = 0;
	int different = 0;
	int ordinary = 0;
	int ord_diff = 0;

    while(getline(file, line)){ 
		int check = 0;
		for(int i = 0;i < line.size();i++){
			for(int j = i + 1;j < line.size();j++){
				//If any characters are repeated
				if(line[i] == line[j]){
					check++;
				}
			}
		}
		//cout << check << endl;
		cout << line;

		if(line.size() <= 1){
			ord_diff++;
			cout << " - Ordinary & Different" << endl;
		}
		else if(check >= line.size()){
			repeated++;
			cout << " - Repeated" << endl;
		}
		else if(check >= 1){
			ordinary++;
			cout << " - Ordinary" << endl;
		}
		else{
			different++;
			cout << " - Different" << endl;
		}
    } 
	cout << "==================================\n";
	cout << repeated << " repeated strings!" << endl;
	cout << different << " different strings!" << endl;
	cout << ordinary << " ordinary strings!" << endl;
	cout << ord_diff << " Ordinary & Different strings!" << endl;
}
