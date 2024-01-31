// challenge_5.cpp

#include "cmpt_error.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> 
#include <algorithm>
using namespace std;

//Function Declarations
void read_nums(fstream& file);
string trim(const string& s);

int main(int argc, char *argv[]) {
	fstream file;

    ///check that one or more filename arguments provided
    if (argc < 2) {
		cout << "Wrong number of arguments\n";
		return -1;
    }

    //argv[1] is the first command-line arugment, ie. the file name
    file.open(argv[1], ios::in);

	read_nums(file);
}

string trim(const string& s) {
    int begin = 0;
    while (begin < s.size() && s[begin] == ' ') begin++;
    int end = s.size() - 1;
    while (end >= 0 && s[end] == ' ') end--;

    return s.substr(begin, end - begin + 1);
}

void read_nums(fstream& file){
	vector <double> A;
	vector <double> B;
	string line;

	//Reading file line-by-line, storing in lines
    while(getline(file, line)){ 
		std::stringstream stream(line);
		vector <double> start;
		string n;

		//Get first number on every line
		double x;
		x = std::stod(line);

		//Make first number the max/min value
		double max = x;
		double min = x;

		while(getline(stream, n, ',')){
			//trim strings to elminate white-space
			string trimmed = trim(n); 
			//Convert strings to doubles
			double temp = std::stod(trimmed);

			//Get A: min of all the maxes
			if(temp > max){
				max = temp;
			}
			//Get A: max of all the mins
			if(temp < min){
				min = temp;
			}
		}
		A.push_back(max);
		B.push_back(min);
	}
	std::sort(A.begin(), A.end());
	std::sort(B.begin(), B.end());

	cout << "A: " << A.front() << endl;
	cout << "B: " << B.back() << endl;
}