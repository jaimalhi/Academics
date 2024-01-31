//Lab1
#include <iostream>
using namespace std;

int main()
{
	int dividend = 0;
	int divisor = 1;

	//Get user input
	cout << "Enter a dividend: ";
	cin >> dividend;
	cout << "Enter a divisor: ";
	cin >> divisor;
	
	int quotient = dividend/divisor;
	int remainder = dividend%divisor;

	cout << dividend << " divided by " << divisor << " = " << quotient << " remainder " << remainder << endl;  

	return 0;
}
