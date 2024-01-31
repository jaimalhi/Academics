#include <iomanip>
#include <iostream>
using namespace std;

void factors(int first, int second){
    //control variables
    int input1 = first;
    int input2 = second;
    int input01 = first;
    int input02 = second;

    //If first < second
    for(;first < second; first++){

        int aFirst = first;
        int iCount = 0; 
        cout << aFirst << ":" << setw(4);

        //Getting factors, prime #s, and perfect squares
        for(int j = 1;j <= aFirst;j++){
            if(aFirst % j == 0){ //getting factors
                cout << j << setw(4);
                iCount++;
            }
        }
        cout << "(" << iCount << ")"; 
        if(iCount == 2){ //checks if input is prime
            cout << "  **prime**  ";
        }
        if(iCount % 2 != 0){ //checks if input has a perfect square
            cout << "  **perfect square**  ";
        }
        cout << endl;
    }

    //If If first > second
    for(;second <= first; second++){

        int aSecond = second;
        int iCount = 0; 
        cout << aSecond << ":" << setw(4); 

        //Getting factors, prime #s, and perfect squares
        for(int j = 1;j <= aSecond;j++){
            if(aSecond % j == 0){ //getting factors
                cout << j << setw(4);
                iCount++;
            }
        }
        cout << "(" << iCount << ")";
        if(iCount == 2){ //checks if input is prime
            cout << "  **prime**  ";
        }
        if(iCount % 2 != 0){ //checks if input has a perfect square
            cout << "  **perfect square**  ";
        }
        cout << endl;
    }

    cout << endl;
    //getting sum of digits for 1st input
    int temp1, r1, sum1 = 0;
    temp1 = input1;
    while(input1 > 0){
        r1 = input1 % 10; //get last digit
        input1 = input1 / 10; //remove last digit
        sum1 = sum1 + r1; //get sum
    } cout << temp1 << ": Sum of digits = " << sum1;

    //checking if # if 'interesting' for input1
    int digit1 = input01%10; 
    int num1 = input01/10; 
    int digit2 = num1%10; 

    if((digit1+digit2)+(digit1*digit2) == temp1){
        cout << " -- interesting -- ";
    }

    cout << endl;
    //getting sum of digits for 2nd input
    int temp2, r2, sum2 = 0;
    temp2 = input2;
    while(input2 > 0){
        r2 = input2 % 10;
        input2 = input2 / 10;
        sum2 = sum2 + r2;
    } cout << temp2 << ": Sum of digits = " << sum2;

    //checking if # if 'interesting' for input2
    int digit3 = input02%10;
    int num2 = input02/10;
    int digit4 = num2%10;

    if((digit3+digit4)+(digit3*digit4) == temp2){
        cout << " -- interesting -- ";
    }

}

int main()
{
    //First Input
    int first;
    cout << "Enter a value between 1 and 999: ";
    cin >> first;
    while(first < 1 || first > 999){ //handling input errors
        cout << "The value must be greater than 0 and less than 1000: ";
        cin >> first;
    }

    //Second input
    int second;
    cout << "Enter a second value between 1 and 999: ";
    cin >> second;
    while(second < 1 || second > 999){ //handling input errors
        cout << "The value must be greater than 0 and less than 1000: ";
        cin >> second;
    }
    
    cout << endl;

    factors(first,second);

    cout << endl;
    return 0;
}

