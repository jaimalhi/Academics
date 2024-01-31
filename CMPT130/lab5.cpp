//Lab5 - Calculate and print compund Interest on Loan
#include <iostream>
#include <ios>
#include <cmath>
using namespace std;

double compoundInterest(double loan, double rate, int term);
void displayLoan(double loan, double rate, int term);

int main()
{
    double loan;
    double rate;
    int term;

    cout << "Enter the amount of the loan: ";
    cin >> loan;
    cout << "Enter the intereste rate as a value between 0 and 1: ";
    cin >> rate;
    cout << "Enter the term of the loan in years: ";
    cin >> term;
    cout << endl;

    displayLoan(loan, rate, term);

    return 0;
}

double compoundInterest(double loan, double rate, int term){

    double interest = loan;

    for(int i = 1;i <= term;i++){
        interest = interest + interest * rate;
    }

    //Can also just do:
    //interest = loan * pow((1 + rate),term) - loan;

    return interest - loan;
}

void displayLoan(double loan, double rate, int term){

    cout << fixed;

    cout.precision(2); //applies to loan and term (they're double)
    cout << "Loan Principal: " << loan << endl;
    cout << "Loan Rate: " << rate << endl;
    cout << "Loan Term: " << term << " years" << endl;
    cout << "Compound Interest: " << compoundInterest(loan, rate, term) << endl;

}
