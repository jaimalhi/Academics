#include <iostream>
#include <string>
using namespace std;

//Prototypes
void printIntStrings(int start, int end, int interval);
string intToString(int number);
string ones(int number);
string teens(int number);
string tens(int number);
string hundreds(int number);
string thousands(int number);

//All Functions with code
string intToString(int number){

    if(number > 99999){
        return "error";
    }
    else if(number > 999){
        return thousands(number);
    }
    else if(number > 99){
        return hundreds(number);
    }
    else if(number >= 20){
        return tens(number);
    }
    else if(number > 9){
        return teens(number);
    }
    else if(number > 0){
        return ones(number);
    }
    else if(number == 0){
        return "zero";
    }
    else{
        return "error";
    }
}

void printIntStrings(int start, int end, int interval){

    if(start < end){
        for(;start < end;start += interval){
            cout << intToString(start);
            cout << endl;
        }
    }
    if(start > end){
        for(;end < start;start -= interval){
            cout << intToString(start);
            cout << endl;
        }
    }
    if(start == end){
        cout << intToString(start);
        cout << endl;
    }
}

string ones(int number){
    if(number == 1) return "one";
    if(number == 2) return "two";
    if(number == 3) return "three";
    if(number == 4) return "four";
    if(number == 5) return "five";
    if(number == 6) return "six";
    if(number == 7) return "seven";
    if(number == 8) return "eight";
    if(number == 9) return "nine";

    return "";
}

string teens(int number){
    if(number == 10) return "ten";
    if(number == 11) return "eleven";
    if(number == 12) return "twelve";
    if(number == 13) return "thirteen";
    if(number == 14) return "fourteen";
    if(number == 15) return "fifteen";
    if(number == 16) return "sixteen";
    if(number == 17) return "seventeen";
    if(number == 18) return "eighteen";
    if(number == 19) return "nineteen";

    return "";
}

string tens(int number){
    string last = ones(number%10);

    if(number == 90) return "ninety";
    if(number == 80) return "eighty";
    if(number == 70) return "seventy";
    if(number == 60) return "sixty";
    if(number == 50) return "fifty";
    if(number == 40) return "fourty";
    if(number == 30) return "thirty";
    if(number == 20) return "twenty";

    if(number > 90) return "ninety-" + last;
    else if(number > 80) return "eighty-" + last;
    else if(number > 70) return "seventy-" + last;
    else if(number > 60) return "sixty-" + last;
    else if(number > 50) return "fifty-" + last;
    else if(number > 40) return "fourty-" + last;
    else if(number > 30) return "thirty-" + last;
    else if(number > 20) return "twenty-" + last;

    else if(number > 9 && number < 20) return teens(number); //control for callback from hundreds function
    else return ones(number%10); //control for 0 in tens place

    return "";
}

string hundreds(int number){
    int first = number/100; //get first digit
    string h;

    if(number < 100){ //control for 0's in hundreds place
        return "and " + tens(number); }
    if(number%100 == 0){ //control for flat numbers (ie. 500)
        return ones(first) + " hundred"; }
    if(number%100 >= 20){ //control for 20-99 in last 2 digits
        h = tens(number%100);
        return tens(first) + " hundred and " + h; }
    if(number%100 > 9 && number%100 < 20){ //control for teens
        h = teens(number%100);
        return tens(first) + " hundred and " + h; }
    if(number%100 > 0){ //control for 1-9 in last digit
        h = ones(number%100);
        return tens(first) + " hundred and " + h; }

    return "";
}

string thousands(int number){
    int first = number/1000; //get first digit of number
    string th;
    string hun = hundreds(number%1000); //number%1000 to get hundreds place

    if(number >= 20000){//control for tens
        th = tens(first); }
    else if(number >= 10000 && number < 20000){ //control for teens
        th = teens(first); }
    else if(number >= 1000){
        th = ones(first); } //control for ones

    if(number%1000 == 0){ //control for flat numbers (ie. 30000)
        return th + " thousand"; }
    else if(number%1000 < 100){ //no commas when 0 in hundreds
        return th + " thousand " + hun; }
    else{
        return th + " thousand, " + hun; }
}

int main(){
    int num;
    cout << "Enter a value between 0 and 99999: ";
    cin >> num;

    cout << num << " - " << intToString(num) << endl;
    //main(); //infinite repitition for testing purposes

    //printIntStrings(25050,25025,5);

    return 0;
}

