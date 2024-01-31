// challenge_7.cpp

#include "cmpt_error.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//Function Declarations
void sum_columns(fstream& file);

int main() {
	fstream file;
    //1000 rows, 500 columns in "bits7.txt"
    file.open("bits7.txt", ios::in);

    sum_columns(file);
    file.close();
}

void sum_columns(fstream& file){
    const int COLS = 500; //number of columns
    const int vSIZE = 1000; //size of the vectors
    int greatest = -1; //greatest sum
    int colNum = -1; //column # of greatest sum
    string line;

    for(int j = 0;j < COLS-1;j++){
        vector <int> c1(vSIZE, 0); 
        vector <int> c2(vSIZE, 0);
        int sum1 = 0, sum2 = 0; //sums to compare
        int i = 0; //indexing vectors

        file.clear(); //clear buffer
        file.seekg(0, ios::beg); //reset reading position
        while(getline(file, line)){
            //convert char to int using ASCII; '0' has value of 48
            c1[i] = line[j] - '0';
            c2[i] = line[j+1] - '0';
            i++;
        }
        //Calculate column sums
        for(int k = 0;k < vSIZE;k++){
            sum1 += c1[k];
            sum2 += c2[k];
        }
        //Store greatest sum
        if(sum1 > sum2 && sum1 >= greatest){
            greatest = sum1;
            colNum = j + 1;
        }
        else if(sum2 >= sum1 && sum2 >= greatest){
            greatest = sum2;
            colNum = j + 2;
        }
    }
    cout << "Greatest: " << greatest << endl;
    cout << "Col Num: " << colNum << endl;
}