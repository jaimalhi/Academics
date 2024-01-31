// Program using global variables.
// TASK: Convert all global variables into local variables.
// You may change the parameters to functions as needed.
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Global Constants (these are fine!).
const double MAX_HEIGHT = 3.0;
const double MIN_HEIGHT = 1.0;

// Function Prototypes
double readHeight();
void printCustomerInfo(double cHeight, string cName);
bool askToDoAnother();

// Asks for a customer's information, and display it to the screen.
int main(){
    bool keepReading = 1;
    string customerName;
    double customerHeight;

	while(keepReading){
		// Read in the customer info:
		// Read Height
	        customerHeight = readHeight();
		// Read Name
		cout << "Enter customer name: ";
		getline(cin, customerName);
		// Display a summary:
		printCustomerInfo(customerHeight,customerName);
		// Do another?
		keepReading = askToDoAnother();
	}
	return 0;
}

// Reads in the user's height
double readHeight(){
    double cHeight;
	cout << "Enter customer height (metres): ";
	cin >> cHeight;

	while (cHeight > MAX_HEIGHT || cHeight < MIN_HEIGHT){
        if(cin.fail()){
            cin.clear();
            cin.ignore(10000, '\n');
        }
		cout << fixed << setprecision(1);
		cout << "ERROR: Height must be between " << MIN_HEIGHT << " and " << MAX_HEIGHT << " metres." << endl;
		cin.ignore(10000, '\n');
		cout << "Enter customer height (metres): ";
		cin >> cHeight;
	}
	// Empty input stream (removes endline)
	cin.ignore(10000,'\n');
	return cHeight;
}

// Prints the customer's information to the screen.
void printCustomerInfo(double cHeight, string cName){
	cout << fixed << setprecision(1);
	cout << "\n";
	cout << "Customer summary: " << endl;
	cout << "\tHeight: " << cHeight << " metres" << endl;
	cout << "\tName: " << cName << endl;
	cout << endl;
}

// Asks the user if they want to enter more data.
bool askToDoAnother(){
    char choice = ' ';
	// Read in the user's selection
	cout << "Enter another customer? (Y/N) ";
	cin >> choice;

	return (choice == 'Y' || choice == 'y');
}
