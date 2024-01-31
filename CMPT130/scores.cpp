#include <iostream>
#include <string>
using namespace std;

int main()
{
	//Variables
	string player1, player2, player3;
	double score1, score2, score3;
	score1 = score2 = score3 = 0;
	char next = 'y';

	while (next != 'n' && next != 'N') {
		//Get input
		//Player1
		cout << "Enter the name of player 1: ";
		cin >> player1;
		cout << "\tEnter " << player1 << "'s score: ";
		cin >> score1;
		//Player2
		cout << "Enter the name of player 2: ";
	        cin >> player2;
	        cout << "\tEnter " << player2 << "'s score: ";     
	        cin >> score2;
		//Player3
		cout << "Enter the name of player 3: ";
	        cin >> player3;
                cout << "\tEnter " << player3 << "'s score: ";
                cin >> score3;

		//Score calculations with one winner
		if (score1 > score2 && score1 > score3) {
			cout << player1 << " is the winner with a score of " << score1 << endl;
		}
		if (score2 > score1 && score2 > score3) {
			cout << player2 << " is the winner with a score of " << score2 << endl;
		}
		if (score3 > score1 && score3 > score2) {
			cout << player3 << " is the winner with a score of " << score3 << endl;
		}
		// Score Calculations with ties	
		if (score1 == score2 && score1 > score3) {
			cout << player1 << " and " << player2 << " are tied with a winning score of " << score1 << endl;
		}	
		if (score1 == score3 && score1 > score2) {
	                cout << player1 << " and " << player3 << " are tied with a winning score of " << score1 << endl;
		}			
		if (score2 == score3 && score2 > score1) {
			cout << player2 << " and " << player3 << " are tied with a winning score of " << score2 << endl;
		}			
		if (score1 == score2 && score1 == score3) {
			cout << player1 << ", " << player2 << ", and " << player3 << " are tied with a score of " << score1 << endl;
		}
		
		//Repeat if user desires
		cout << endl;
		cout << "Do you want to continue? Enter n to stop, any other key to continue: ";

		cin >> next;
		cout << endl;
	}
	cout << "Goodbye!" << endl;

	return 0;
}

