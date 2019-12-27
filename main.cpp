#include<iostream>
#include<string>
#include <algorithm>
#include<ctime>
using namespace std;


int main() {

	srand(time(NULL));


	//game variables
	string input;
	bool MatchFound = false;
	int PHandSize = 5;
	int CHandSize = 5;
	int NextDeckCard = 10;
	bool HasCard = false;
	int PlayerScore = 0;
	int ComputerScore = 0;
	int turnNumber = 1;
	int computerPick;
	enum TURNS { player, computer };
	int turn = player;
	int quads = 0;
	char match;
	bool isEmpty = false;

	//create a deck of cards stored in an array
	string deck[] = {
		"1 hearts", "2 hearts","3 hearts","4 hearts","5 hearts","6 hearts","7 hearts","8 hearts","9 hearts","J hearts","Q hearts","K hearts", "A hearts",
		"1 Dias", "2 Dias","3 Dias","4 Dias","5 Dias","6 Dias","7 Dias","8 Dias","9 Dias","J Dias","Q Dias","K Dias", "A Dias",
		"1 Spades", "2 Spades","3 Spades","4 Spades","5 Spades","6 Spades","7 Spades","8 Spades","9 Spades","J Spades","Q Spades","K Spades", "A Spades",
		"1 Clubs", "2 Clubs","3 Clubs","4 Clubs","5 Clubs","6 Clubs","7 Clubs","8 Clubs","9 Clubs","J Clubs","Q Clubs","K Clubs", "A Clubs"
	};

	////print it out for testing
	for (int i = 0; i < 52; i++)
		cout << deck[i]<<", ";

	//cout << endl << endl;//just to space it out

	random_shuffle(&deck[0], &deck[52]); //call the random shuffle function, found in the algorithm library

	cout << endl << endl << endl;
	for (int i = 0; i < 52; i++) //print it out again to see the shuffle
		cout << deck[i] << ", ";

	//create two arrays to represent the cards the player and computer have in their hands, 
	//initialize each slot in each array to the word "empty"
	string PlayerHand[52];
	string ComputerHand[52];
	for (int i = 0; i < 52; i++) {
		PlayerHand[i] = "empty";
		ComputerHand[i] = "empty";
	}

	//swap out the first five of the deck into player hand
	//and the second five into the computer hand
	for (int i = 0; i < 5; i++) {
		PlayerHand[i] = deck[i];
		deck[i] = "empty";
	}
	for (int i = 5; i < 10; i++) {
		ComputerHand[i] = deck[i];
		deck[i] = "empty";
	}






	cout << "Welcome to Go Fish!" << endl << endl;
	while (PlayerScore + ComputerScore < 13) {

		//Game Turn Start: print important information
		cout << endl << endl << endl << "************************************************************************" << endl;
		cout << "it is turn number " << turnNumber << endl;
		if (turn == player) cout << "It is currently the human's turn." << endl;
		else cout << "It is currently the comptuer's turn" << endl;
		cout << "you have " << PHandSize << " cards in your hand, and your robot opponent has " << CHandSize << endl;
		cout << "The scores are Player: " << PlayerScore << ", Computer: " << ComputerScore << endl << endl;
		system("pause");
		cout << endl << endl;


		switch (turn) {

		case player:

			////////////////////////////////////////////////////////////////////////////////////////////
			//PLAYER TURN//////////////////////////////////////////////////////////////////////////////
		
			//sort cards for easy reading
			sort(PlayerHand, PlayerHand+51);
			sort(ComputerHand, ComputerHand+51);

			//PRINT OUT PLAYER HAND////////////////////////////////////////////////////////////////
			cout << endl << "Your current hand: " << endl;
			for (int i = 0; i < 52; i++) {
				if (PlayerHand[i].at(0) != 'e') //let's not print out all the "empty" slots!
					cout << PlayerHand[i] << endl;
			}

			//just for testing purposes (otherwise it's cheating!)
			cout << endl << "The comptuer's current hand: " << endl;
			for (int i = 0; i < 52; i++) {
				if (PlayerHand[i].at(0) != 'e') //let's not print out all the "empty" slots!
					cout << ComputerHand[i] << endl;
			}

			//////////////////////////////////////////////////////////////////////////////////////
			//cull any sets of 4 that exist in  player's hand
			for (int i = 0; i < 52; i++) {
				quads = 0; //this is a counter, we're resetting it here

			//look at slot 0, and search slots 1-52 for that value, then look at slot 1 and search slots 2-52 for that value...
				for (int j = i + 1; j < 51; j++) {
					if (PlayerHand[i].at(0)!='e') { //don't count empty slots as matches!
						if (PlayerHand[i].at(0) == PlayerHand[j].at(0)) {
							quads++;
							if (quads == 3) { //check if we have all 4 (remember, we started counting at 0)
								match = PlayerHand[i].at(0); //hold onto the card type we got a match for
								PlayerScore++;
								cout << "you got all 4! Culling cards and giving you a point" << endl;
								for (int m = 0; m < 52; m++) {
									if (PlayerHand[m].at(0) == match) //erase all the cards that are the same as the match
										PlayerHand[m] = "empty";
								}
								cout << endl << "Your new hand: " << endl; //reprint your hand
								for (int i = 0; i < 52; i++) {
									if (PlayerHand[i].at(0) != 'e') 
										cout << PlayerHand[i] << endl;
								}
							}
						}
					}
				}
			}


			//Player makes choice

			cout << endl << endl << "It's your turn. What card would you like to ask the computer for?" << endl;
			cin >> input;
			cout << "you are looking for a " << input.at(0) << endl;

			//make sure the player actually HAS that card
			for (int i = 0; i < 52; i++)
				if (PlayerHand[i].at(0) == input.at(0)) {
					HasCard = true;
				}


			//if they don't have the card they're looking for, skip this whole section!
			if (HasCard == false) {
				cout << "you don't have that card, dummy" << endl;
				turn = computer;
			}

			else {
				//check first character of user input with first character of each card in computer's hand
				for (int i = 0; i < 52; i++) {
					if (input.at(0) == ComputerHand[i].at(0)) {
						cout << "found a match!" << endl;

						MatchFound = true; //this is so we don't trigger go fish at end of turn
						CHandSize--;
						PHandSize++;
						//PlayerScore++;
						//add card to player hand!
						for (int j = 0; j < 52; j++)
							if (PlayerHand[j].at(0) == 'e') {
								cout << "(you take their card)" << endl;
								PlayerHand[j] = ComputerHand[i];
								ComputerHand[i] = "empty"; //remove card from computer hand
								break;
							}

					}
				}

				if (MatchFound == false) {
					cout << "No match found. GO FISH!" << endl;
					system("pause");
					cout << "You grabbed a " << deck[NextDeckCard] << endl;
					PlayerHand[PHandSize] = deck[NextDeckCard];
					if (deck[NextDeckCard].at(0) != input.at(0)) //give computer turn if you don't fish out what you asked for
						turn = computer;
					deck[NextDeckCard] = "empty";
					PHandSize++;
					NextDeckCard++;
					turnNumber++;
				}
				else
					MatchFound = false;
			}
			HasCard = false; //reset this variable so we can use it for computer's turn

			break;



			///////////////////////////////////////////////////////////////////////////////////
			//computer turn!
		case computer:
			HasCard = false;
			cout << endl << endl << "computer turn!" << endl;

			//////////////////////////////////////////////////////////////////////////////////////
			//cull any sets of 4 that exist in  player's hand

			for (int i = 0; i < 52; i++) {
				quads = 0;
				//cout << "quads is " << quads<<endl;
				for (int j = i + 1; j < 51; j++) {
					if (ComputerHand[i].compare("empty") != 0) {

						//look at slot 0, and search slots 1-52 for that value, then look at slot 1 and search slots 2-52 for that value...
						if (ComputerHand[i].at(0) == ComputerHand[j].at(0)) {
							quads++;
							if (quads == 3) {
								match = ComputerHand[i].at(0);
								ComputerScore++;
								cout << "The computer got all 4! Culling cards and giving your opponent a point" << endl;
								for (int m = 0; m < 52; m++) {
									if (ComputerHand[m].at(0) == match)
										ComputerHand[m] = "empty";
								}


								cout << endl << "Computer's new hand: " << endl;
								for (int i = 0; i < 52; i++) {
									if (ComputerHand[i].compare("empty") != 0) //let's not print out all the "empty" slots!
										cout << ComputerHand[i] << endl;
								}
							}
						}
					}
				}
			}


			//generate card to ask for
			//first check if hand is empty
			isEmpty = true;
			for (int i = 0; i < 52; i++) {
				if (ComputerHand[i].at(0) != 'e')
					isEmpty = false;
			}

			if (isEmpty == true)
				cout << "I have an empty hand, so I'm going to GO FISH." << endl << endl;
			else {

				do {
					computerPick = rand() % 52;
					//cout << "generating.";
				} while (ComputerHand[computerPick].at(0) == 'e');

				cout << endl << endl << "Computer asks: do you have a " << ComputerHand[computerPick].at(0) << " ?" << endl;
				system("pause");

				for (int i = 0; i < 52; i++)
					if (PlayerHand[i].at(0) == ComputerHand[computerPick].at(0)) { //check if player has that card type
						cout << endl << endl << "computer says: whoo hoo! I see you have it! (takes your card)" << endl;
						//ComputerHand[computerPick] = "empty";
						//add card to player hand!
						for (int j = 0; j < 52; j++)
							if (ComputerHand[j].at(0) == 'e') {
								ComputerHand[j] = PlayerHand[i];
								PlayerHand[i] = "empty";
								break;
							}

						CHandSize++;
						PHandSize--;
						//ComputerScore++;
						HasCard = true;
						//break; //quit for loop
					}
			}
			//if they didn't have it, grab a new card from the deck (go fish)
			if (HasCard == false) {
				cout << endl << endl << "computer says: beans. you don't have it. I'll go fish." << endl;
				cout << "computer picks up a " << deck[NextDeckCard] << endl;
				for (int i = 0; i < 52; i++) {
					if (ComputerHand[i].at(0) == 'e') {
						ComputerHand[i] = deck[NextDeckCard];

						if (ComputerHand[i].at(0) != ComputerHand[computerPick].at(0)) //give human turn back if they don't pick what they asked for
							turn = player;
						deck[NextDeckCard] = "empty"; //take that card out of deck
						CHandSize++;
						NextDeckCard++;
						turnNumber++;
						break;
					}
				}


			}
			break;
		}//end switch


	}//end game loop

	cout << "Game Over!" << endl;
	if (PlayerScore>ComputerScore)
		cout << "Human wins with score of " << PlayerScore << " - " << ComputerScore << endl;
	else if (ComputerScore>PlayerScore)
		cout << "Computer wins with score of " << ComputerScore << " - " << PlayerScore << endl;
	else
		cout << "Game was tied!" << endl;

	cout << endl << endl << "thanks for playing!" << endl;

	system("pause");

}//end main
