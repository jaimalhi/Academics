// challenge_8.cpp
#include "cmpt_error.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

//four legal operators: +, -, *, and @
//The expression a @ b evaluates to the maximum of a and b
//operators all have the same precedence, order of ops not relevant
//how many expressions (per line) evaluate to a multiple of 8?

//Function Declaration
void arithmetic(fstream& file);
int max(int num1, int num2);

int main() {
	fstream file;
    file.open("expr8.txt", ios::in);

    arithmetic(file);
    file.close();
}

int max(int num1, int num2){
    if(num1 >= num2) return num1;
    else return num2;
}

void arithmetic(fstream& file){
    vector<int> output;
    vector<int> eights; //multiples of 8
    vector<string> ops = {"+","-","*","@"};
    string line;
    int result = -1, num = -1; //nums to operate on
    string op = ""; //arithmetic operator

    while(getline(file, line)){
        stringstream stream(line);
        string s;
        int i = 0;
    
        //gets each number/operator, stores into s
        while(stream >> s){
            i++; //count iterations
            //catch the operator
            for(string c : ops){
                if(s == c) op = s;
            }

            //first number starts as the result
            if(i == 1) result = stoi(s);
            if(s != op) num = stoi(s);

            //TESTING
            // cout << "Result: " << result << endl;
            // cout << "Num: " << num << endl;
            // cout << "Op: " << op << endl;
            // cout << "=====================\n";

            //Calculate operations
            if(i == 3 || i == 5 || i == 7 || i == 9){
                if(op == "+") result = result + num;
                else if(op == "-") result = result - num;
                else if(op == "*") result = result * num;
                else if(op == "@") result = max(result, num);
            }
        }
        output.push_back(result);
    }
    //Is a multiple of 8
    for(int x : output){
        if (x % 8 == 0) eights.push_back(x);
    }
    
    cout << eights.size() << " multiples of eight\n";
}