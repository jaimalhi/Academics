//Project Blackjack - CMPT 130
//Jaivir Malhi (301457742)
//The advice in the program follows the "Basic Strategy" portion of "https://bicyclecards.com/how-to-play/blackjack/" excluding doubling down and splitting
//Academic honesty statement: I hereby confirm that this is my own work and I have not violated any of SFU’s Code of Academic Integrity and Good Conduct (S10.01)
#include <iostream>
#include <string>
#include <cstdlib> 
#include <ctime>
#include <istream>
using namespace std;

/*
Note: Following Blackjack rules as per "https://bicyclecards.com/how-to-play/blackjack/" if dealer busts, the player 
wins regardless of a bust (player busting) or not 
*/

struct Card {
	string suit; //card suit
	string type; //card type (ace, king, three, etc)
	int rank; //card rank (1-13)
	int value; //card value -> 11 for aces (rank 1)
};

struct CardArray {
	Card* cards; //pointer to an array of cards
	int maxCard; //stores max # of elements of card array (used & unused)
	int currentCard; //stores current # of (used) elements of card array

	CardArray() {
		cards = nullptr;
		maxCard = 0;
		currentCard = 0;
	}
};

//Function Prototypes
void getNewDeck(CardArray& deck);
void printDeck(const CardArray& deck);
void shuffleDeck(CardArray& deck);
int blackjack(CardArray& deck);
void dealCards(CardArray& deck, CardArray& hand);
void printCards(const CardArray& deck);
void initialDealing(CardArray& deck, CardArray& playerHand, CardArray& dealerHand);
void dealPlayer(CardArray& deck, CardArray& hand);
void dealDealer(CardArray& deck, CardArray& hand);
int handValue(CardArray& hand);
void checkValues(CardArray& pHand, CardArray& dHand, int& wins, int& loses, int& draws);
int hitOrStand(CardArray& deck, CardArray& pHand, CardArray& dHand, int& wins, int& losses, int& draws);
void showGameResults(int wins, int losses, int draws, int gameCount);
void playAgain(CardArray& deck, int& gameCount, int& wins, int& losses, int& draws, int& gameResult);
void playBlackjack(CardArray& deck);
void aceValues(CardArray& deck, CardArray& hand);
void advice(CardArray& pHand, CardArray& dHand);

int main()
{
	CardArray deck; //declare CardArray

	getNewDeck(deck); //Populate w/ deck of cards
	printDeck(deck); //Print deck (shuffled or unshuffled)
	cout << endl;

	shuffleDeck(deck); //shuffle the deck
	printDeck(deck); //Print deck (shuffled or unshuffled)
	cout << endl << endl;

	playBlackjack(deck);

	cout << endl;
	delete[] deck.cards; //delete allocated dynamic memory for CardArray
	return 0;
}

//Populating a CardArray with the standard deck of cards
void getNewDeck(CardArray& deck) {
	const int DECKSIZE = 52;

	deck.maxCard = DECKSIZE;
	deck.cards = new Card[deck.maxCard];

	string suit = "ERROR";
	string type = "ERROR";
	int rank = 0;
	int value = 0;
	int increments = 0;

	//Nested for loops to create all cards
	for (int j = 0; j < 4; j++) {
		if (j == 0) { suit = "S"; }
		if (j == 1) { suit = "H"; }
		if (j == 2) { suit = "D"; }
		if (j == 3) { suit = "C"; }

		for (int i = 1; i <= 13; i++) {
			rank = i;
			if (i == 1) {
				type = "A";
				value = 11;
			}
			else if (i == 11) {
				type = "J";
				value = 10;
			}
			else if (i == 12) {
				type = "Q";
				value = 10;
			}
			else if (i == 13) {
				type = "K";
				value = 10;
			}
			else {
				type = to_string(i);
				value = i;
			}
			Card newCard = { suit, type, rank, value };
			deck.cards[(i + increments) - 1] = newCard;
			deck.currentCard = i + increments;
		}
		increments += 13;
	}
}

//Printing entire deck
void printDeck(const CardArray& deck) {
	for (int i = 0; i < deck.currentCard; i++) {
		if (i % 13 == 0) {
			cout << endl;
		}
		cout << deck.cards[i].type;
		cout << deck.cards[i].suit << " ";
	}
}

//Shuffling entire deck
void shuffleDeck(CardArray& deck) {
	srand(time(0));

	int rIndex = 0;
	Card card;

	for (int i = 0; i < deck.maxCard; i++) {
		rIndex = rand() % deck.currentCard;

		card = deck.cards[i];
		deck.cards[i] = deck.cards[rIndex];
		deck.cards[rIndex] = card;
	}
}

//Play multiple games
void playBlackjack(CardArray& deck) {
	char playGame;
	int gameResult;
	int gameCount = 0;
	int wins = 0;
	int losses = 0;
	int draws = 0;

	//First play 
	cout << "BLACKJACK\n----------\n";
	cout << "Do you want to play a hand of blackjack?" << endl;
	cout << "Y for yes, any other key for no: ";
	cin >> playGame;
	cout << endl;

	if (playGame == 'y' || playGame == 'Y') {
		gameCount++;
		gameResult = blackjack(deck);

		if (gameResult == 1) {
			wins += 1;
		}
		else if (gameResult == -1) {
			losses += 1;
		}
		else {
			draws += 1;
		}
		//2nd+ play throughs
		playAgain(deck, gameCount, wins, losses, draws, gameResult);
	}
	else {
		showGameResults(wins, losses, draws, gameCount);
		cout << "\nSee you later!\n";
		exit(0);
	}
}

//Main Blackjack function
//Player wins return 1, losses return -1, draw return 0.
int blackjack(CardArray& deck) { //TO DO
	CardArray playerHand;
	CardArray dealerHand;

	int wins = 0;
	int losses = 0;
	int draws = 0;

	//dealing 1st and 2nd cards
	initialDealing(deck, playerHand, dealerHand); 

	//Main Messages + play through
	cout << "\n\nDealing to player\n------------------";
	hitOrStand(deck, playerHand, dealerHand, wins, losses, draws);

	//Delete allocated memory for respective hands
	delete[] playerHand.cards;
	delete[] dealerHand.cards;

	//Return values for win, loss, or draw
	if (wins >= 1) {
		return 1;
	}
	else if (losses >= 1) {
		return -1;
	}
	else { //draws
		return 0;
	}
}

//Dealing cards for Player & Dealer
void dealCards(CardArray& deck, CardArray& hand) {
	int lastElement = deck.currentCard - 1;
	int nextElement = hand.currentCard;

	const int MAXHANDSIZE = 12;
	hand.maxCard = MAXHANDSIZE;

	//Creating new array for hands if needed
	if (hand.currentCard == 0) {
		hand.cards = new Card[hand.maxCard];
	}

	//Setting last element of the deck to first element of hand
	Card newHand = { deck.cards[lastElement].suit, deck.cards[lastElement].type, deck.cards[lastElement].rank, deck.cards[lastElement].value };
	hand.cards[nextElement] = newHand;

	hand.currentCard += 1; //add one card to hand count			
	deck.currentCard -= 1; //remove one card from deck count	
}

//Printing Cards from the hands of Player & Dealer
void printCards(const CardArray& hand) {
	for (int i = 0; i < hand.currentCard; i++) {
		cout << hand.cards[i].type;
		cout << hand.cards[i].suit << " ";
	}
}

//Dealing First & Second cards to Player and Dealer
void initialDealing(CardArray& deck, CardArray& playerHand, CardArray& dealerHand) {

	cout << "Deal first card\n------------------" << endl;
	//Show Players card
	cout << "Player: ";
	dealCards(deck, playerHand);
	printCards(playerHand);

	//Show Dealers card
	cout << "\nDealer: ";
	dealCards(deck, dealerHand);
	printCards(dealerHand);

	cout << "\n\nDeal second card\n------------------" << endl;
	//Show Players card
	cout << "Player: ";
	dealCards(deck, playerHand);
	printCards(playerHand);

	//Show Dealers card
	cout << "\nDealer: "; 
	cout << dealerHand.cards[0].type << dealerHand.cards[0].suit << " ?? "; //Shows dealer first card only
	dealCards(deck, dealerHand);
	//printCards(dealerHand); //Show dealers first + second card
}

//Deal the player another card
void dealPlayer(CardArray& deck, CardArray& hand) {
	cout << "Player: ";
	dealCards(deck, hand);
	printCards(hand);
}

//Show dealers hand & deal dealer another card if below 17
void dealDealer(CardArray& deck, CardArray& hand) {
	//Potentially change ace values
	aceValues(deck, hand);

	//While dealer below 17, add another card to their hand
	while (handValue(hand) < 17) {
		cout << "Dealer: ";
		printCards(hand);
		dealCards(deck, hand);
		cout << endl;

		//Potentially change ace values
		aceValues(deck, hand);
	}

	cout << "Dealer: ";
	printCards(hand);
	cout << endl;
}

//Total value of player or dealers hand(s)
int handValue(CardArray& hand) {
	int totalValue = 0;

	//Iterate through each card and add values
	for (int i = 0; i < hand.currentCard; i++) {
		totalValue += hand.cards[i].value;
	}

	return totalValue;
}

//To check & show if player wins, loses, or draws
void checkValues(CardArray& pHand, CardArray& dHand, int& wins, int& losses, int& draws) {
	int player = handValue(pHand);
	int dealer = handValue(dHand);

	//Above 21 cases
	if (dealer > 21) {
		cout << "Dealer is bust! You win " << endl;
		wins += 1;
	}
	else if (player > 21) {
		cout << "Bust! You lose " << endl;
		losses += 1;
	}
	//Blackjack + Draw cases
	else if (player == 21 && dealer == 21) {
		cout << "Game is tied " << endl;
		draws += 1;
	}
	else if (player == 21 && dealer != 21) {
		cout << "Blackjack! You win " << endl;
		wins += 1;
	}
	else if (dealer == 21 && player != 21) {
		cout << "Dealer got Blackjack! You lose " << endl;
		losses += 1;
	}
	//Other Cases
	else if (player > dealer) {
		cout << "Congrats! You win " << endl;
		wins += 1;
	}
	else if (dealer > player) {
		cout << "Dealer wins! You lose" << endl;
		losses += 1;
	}
	else if (player == dealer) {
		cout << "Game is tied " << endl;
		draws += 1;
	}
}

//Player Hitting or Standing
int hitOrStand(CardArray& deck, CardArray& pHand, CardArray& dHand, int& wins, int& losses, int& draws) {
	char pChoice;

	//Giving player advice
	advice(pHand, dHand);

	while (true) {
		cout << "Enter 'h' to hit or 's' to stand: ";
		//Input checking
		if (!(cin >> pChoice)) {
			cout << "Invalid input! ";
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else if (pChoice == 'h') {
			cin.clear();
			cin.ignore(1000, '\n');
			//Deal card to player
			dealPlayer(deck, pHand);
			//Potentially change ace values
			aceValues(deck, pHand);

			//Hit control, at 21 or above
			if (handValue(pHand) >= 21) {
				cout << "\n\nDealing to dealer\n------------------\n";
				dealDealer(deck, dHand);

				cout << "\nPlayer score = " << handValue(pHand) << ", ";
				cout << "Dealer score = " << handValue(dHand) << endl;

				checkValues(pHand, dHand, wins, losses, draws);
				return 0;
			}
			//Call itself to allow Hit or Stand again
			hitOrStand(deck, pHand, dHand, wins, losses, draws);
			return 0;
		}
		else if (pChoice == 's') {
			cin.clear();
			cin.ignore(1000, '\n');

			cout << "\nDealing to dealer\n------------------\n";
			dealDealer(deck, dHand);

			cout << "\nPlayer score = " << handValue(pHand) << ", ";
			cout << "Dealer score = " << handValue(dHand) << endl;

			checkValues(pHand, dHand, wins, losses, draws);
			return 0;
		}
		else {
			cout << "Invalid input! ";
			cin.clear();
			cin.ignore(1000, '\n');
		}
	}
	return 0;
}

//Show the wins, losses, and draws of the games played
void showGameResults(int wins, int losses, int draws, int gameCount) { 
	cout << "Thanks for playing, you played " << gameCount << " game(s) and your record was: " << endl;
	cout << "  wins: " << wins << endl;
	cout << "losses: " << losses << endl;
	cout << " draws: " << draws << endl;
}

//Let the player play again or stop
void playAgain(CardArray& deck, int& gameCount, int& wins, int& losses, int& draws, int& gameResult) {
	char playGame;

	//If deck lacking cards, get new deck
	if (deck.currentCard < 4) {
		getNewDeck(deck);
		shuffleDeck(deck);
	}

	cout << "\n__________________________________\n";
	cout << "Do you want to play another hand?" << endl;
	cout << "Y for yes, any other key for no: ";
	cin >> playGame;
	cout << endl;

	if (playGame == 'y' || playGame == 'Y') {
		gameCount++;
		gameResult = blackjack(deck);

		if (gameResult == 1) {
			wins += 1;
		}
		else if (gameResult == -1) {
			losses += 1;
		}
		else {
			draws += 1;
		}

		//cout << endl << "Cards left in deck: " << deck.currentCard; // for testing

		playAgain(deck, gameCount, wins, losses, draws, gameResult);
	}
	else {
		showGameResults(wins, losses, draws, gameCount);
		cout << "\nSee you later!\n";
		exit(0);
	}
}

//Change ace values from 11 to 1 if needed
void aceValues(CardArray& deck, CardArray& hand) { 
	//Checks for Ace in hand, if Value > 21, Ace goes from 11 to 1
	for(int i = 0; i < hand.currentCard; i++) {
		if (hand.cards[i].type == "A") {
			if (handValue(hand) > 21) {
				hand.cards[i].value = 1;
			}
		} 
	}
}	

//Gives player advice on next move
void advice(CardArray& pHand, CardArray& dHand) {
	int player = handValue(pHand);
	int dealer = handValue(dHand);
	cout << endl;

	if (player == 21) {
		cout << "[ You should stand, you got Blackjack! ]" << endl;
	}
	else if (dealer == 21) {
		cout << "[ You should stand, dealer likely has Blackjack! ]" << endl;
	}
	else if (dealer < 16 && dealer > 12) {
		cout << "[ You should stand, dealer will likely bust! ]" << endl;
	}
	else if (player < 17 && player > 12) {
		cout << "[ You could hit, you're below 17! ]" << endl;
	}
	else if (player < 17) { 
		cout << "[ You should hit, your scores pretty low! ]" << endl;
	}
	else if (player == 17) {
		cout << "[ Hit or Stand, this one is on you! ] " << endl;
	}
	else if (player >= 18) {
		cout << "[ You should stand, a hit would likely be a bust! ]" << endl;
	}
}
