#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string getName();
int countAlpha(string s);

int main()
{
    string name = getName();
    cout << name << endl;

    cout << "Your name has " << countAlpha(name) << " letters in it" << endl;

    return 0;
}

string getName(){
    string first;
    string last;

    cout << "enter your first name: ";
    cin >> first;
    cout << "enter your last name: ";
    cin >> last;

    return first + " " + last;
}

int countAlpha(string s){
    int count1 = 0;

    for(int i = 0;i <= s.size();i++){
        if(isalpha(s[i])){
            count1++;
        }
    }

    return count1;
}
