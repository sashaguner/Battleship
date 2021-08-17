// Battleship.cpp : This file contains the 'main' function. Program execution begins and ends there.
// (c) Oleksandra Kasatkina, 2019

#include <Windows.h>	// for cursor position
#include "Player.h"		// Player class
#include "Board.h"      // game board
#include "Ship.h"		// ships 
#include <iostream>		// cout, cin
#include <string>		// string
#include <stdio.h>      // printf, scanf, puts, NULL
#include <stdlib.h>     // srand, rand
#include <time.h>       // time
#include <thread>		// for slowPrint function
#include <chrono>		// for slowPrint function


// Name space resolutions
using std::cout;
using std::flush;
using std::string;
using std::this_thread::sleep_for;
using std::chrono::milliseconds;

void setCursorPosiotion(short, short);
void clearScreen(int, int);
void slowPrint(const string&, unsigned int);
void welcomeMsg();
void gameDescriptionMsg();
void missedMsg();
void hitMsg();

int main()
{		
	//create player objects
	Player user;//user
	Player comp;//computer

	//create players' board objects
	Board userBoard;//user's board
	Board compBoard;//computer's board

	//create ship objects
	Ship frigate1(" F ", 2);
	Ship sub2(" S ", 3);
	Ship destroyer3(" D ", 3);
	Ship battleship4(" B ", 4);
	Ship aircraftCarrier5(" A ", 5);

	//Intro message
	welcomeMsg();
	gameDescriptionMsg();

	//to use getline()
	string str;
	getline(cin, str);

	clearScreen(110, 45);
	setCursorPosiotion(0, 0);

	//ask user for their name
	user.setName();
	
	//hold difficulty level 1 for easy 2 for hard
	int difficulty;
	//ask user to choose version of the game (easy or hard)
	//if user chooses difficulty, when they sink the ship computer will show empty spaces around it
	cout << "\n\tEasy mode: once you sink a ship you will see a confirmation message!\n\tHard mode: You will have to guess if you sinked the ship or not\n\n\tChoose the difficulty level (2 for Hard or 1 for Easy): ";
	cin >> difficulty;

	//validate user's input
	while (difficulty != 1 && difficulty != 2)
	{
		cin.clear();
		cin.ignore(256, '\n');
		//ask user to choose version of the game (easy or hard)
		cout << "\n\tInvalid input. Please answer '1' or '2'. \n\tChoose the difficulty level (2 for Hard or 1 for Easy): ";
		cin >> difficulty;
	}

	string choice;

	do
	{
		clearScreen(80, 20);
		setCursorPosiotion(0, 0);
		//create empty user's board and show it on the screen
		userBoard.createBoard();
		//populate user's board with ships
		userBoard.placeShipsOnBoard(frigate1.getShipPiece(), frigate1.getNumOfShipPieces(), 0);
		userBoard.placeShipsOnBoard(sub2.getShipPiece(), sub2.getNumOfShipPieces(), 0);
		userBoard.placeShipsOnBoard(destroyer3.getShipPiece(), destroyer3.getNumOfShipPieces(), 0);
		userBoard.placeShipsOnBoard(battleship4.getShipPiece(), battleship4.getNumOfShipPieces(), 0);
		userBoard.placeShipsOnBoard(aircraftCarrier5.getShipPiece(), aircraftCarrier5.getNumOfShipPieces(), 0);
		cout << "\n\n\tChoose your battle field " << user.getName() << "\n\n";
		userBoard.showBoard();

		cout << "\n\tDo you like this battle field? (Y or N): ";
		cin >> choice;

		while (choice != "Y" && choice != "y" && choice != "N" && choice != "n")
		{
			cout << "\n\tInvalid input. Please answer (Y or N): ";
			cin >> choice;
		}

	} while (choice == "n" || choice == "N");

	cout << "\n\tGood choice! You are ready to start the game!\n\tPress enter to continue...";

	cin.ignore();
	getline(cin, str);

	clearScreen(55, 30);
	setCursorPosiotion(0, 0);

	//do{ //test
	//create empty computer's board and show it on the screen
	compBoard.createBoard();
	compBoard.createFakeBoard();

	//populate computer's board with ships
	compBoard.placeShipsOnBoard(frigate1.getShipPiece(), frigate1.getNumOfShipPieces(), 1);
	compBoard.placeShipsOnBoard(sub2.getShipPiece(), sub2.getNumOfShipPieces(), 1);
	compBoard.placeShipsOnBoard(destroyer3.getShipPiece(), destroyer3.getNumOfShipPieces(), 1);
	compBoard.placeShipsOnBoard(battleship4.getShipPiece(), battleship4.getNumOfShipPieces(), 1);
	compBoard.placeShipsOnBoard(aircraftCarrier5.getShipPiece(), aircraftCarrier5.getNumOfShipPieces(), 1);
	compBoard.detectShips();//detect CPU ships
	cout << "\n\n\tHere is your oponent's board\n\n";
	compBoard.showFakeBoard();
	//compBoard.showBoard(); //test
	
	/*
	cout << "\n\tDo you like this battle field? (Y or N): ";
	cin >> choice;

	while (choice != "Y" && choice != "y" && choice != "N" && choice != "n")
	{
		cout << "\n\tInvalid input. Please answer (Y or N): ";
		cin >> choice;
	}

	} while (choice == "n" || choice == "N");*/ //test

	//to hold results of hit function for user and his opponent
	bool userHit, cpuHit;

	//to hold user's input for row
	int row;
	//to hold user's input for column 
	char c;
	//to store column letter as a number
	int col;

	//hit and miss system
	//repeat until one of the players wins

	cout << "\n\n\tIt's time to fire cannons at your opponet's ship!\n";

	do
	{
		//get user's input for row number
		cout << "\n\t" << user.getName() << " enter row number: ";
		cin >> row;

		//if row = -1 end the game, if not continue
		if (row != -1)
		{
			//validate user's input
			while (row < 1 || row > 10)
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout << "\tPlease choose a number from 1 to 10 only: ";
				cin >> row;
			}

			//substract 1 from user's input, because array starts from 0 but row count is displayed from 1 
			row -= 1;

			//get letter from user for a column
			cout << "\n\t" << user.getName() << " enter column letter: ";
			cin >> c;

			//if input for column = -1 end the game, if not continue
			if (c != -1)
			{
				//validate user's input
				while (c < 'a' || c > 'j')
				{
					cout << "\tPlease choose a letter from 'a' to 'j' only: ";
					cin >> c;
				}

				//switch letter to array column index
				switch (c)
				{
				case 'a': col = 0;
					break;
				case 'b': col = 1;
					break;
				case 'c': col = 2;
					break;
				case 'd': col = 3;
					break;
				case 'e': col = 4;
					break;
				case 'f': col = 5;
					break;
				case 'g': col = 6;
					break;
				case 'h': col = 7;
					break;
				case 'i': col = 8;
					break;
				case 'j': col = 9;
					break;
				case 'k': col = 10;
				}

				clearScreen(67, 40);
				setCursorPosiotion(0, 0);

				//check if user hit the ship
				userHit = compBoard.hit(row, col, difficulty);

				//if user misses
				if (userHit == false)
				{
					user.incrementMisses();//count consecutive misses
					missedMsg();
					cout << "\n\tYour opponet's board:\n" << endl;
					//compBoard.showBoard(); //test
					compBoard.showFakeBoard();//show user progress on opponent's board
				}
				//if user hits opponent's ship
				else if (userHit == true)
				{
					user.setMisses(0);//if user hits, delete the count of all previous misses and start over
					user.incrementHits();//count hits

					if (compBoard.getShipFcount() == 2)
					{
						if (difficulty == 1)
							cout << "\n\tYou sunk the Frigate!\n\n";
						else 
						{
							hitMsg();
							cout << "\n\tYour opponet's board:\n" << endl;
						}
						compBoard.setShipFCount(0);
					}
					else if (compBoard.getShipScount() == 3)
					{
						if (difficulty == 1)
							cout << "\n\tYou sunk the Submarine!\n\n";
						else
						{
							hitMsg();
							cout << "\n\tYour opponet's board:\n" << endl;
						}

						compBoard.setShipSCount(0);
					}
					else if (compBoard.getShipDcount() == 3)
					{
						if (difficulty == 1)
							cout << "\n\tYou sunk the Destroyer!\n\n";
						{
							hitMsg();
							cout << "\n\tYour opponet's board:\n" << endl;
						}
						compBoard.setShipDCount(0);
					}
					else if (compBoard.getShipBcount() == 4)
					{
						if (difficulty == 1)
							cout << "\n\tYou sunk the Battleship!\n\n";
						else
						{
							hitMsg();
							cout << "\n\tYour opponet's board:\n" << endl;
						}
						compBoard.setShipBCount(0);
					}
					else if (compBoard.getShipAcount() == 5)
					{
						if (difficulty == 1)
							cout << "\n\tYou sunk the Aircraft Carrier!\n\n";
						else
						{
							hitMsg();
							cout << "\n\tYour opponet's board:\n" << endl;
						}
						compBoard.setShipACount(0);
					}
					else
					{
						hitMsg();
						cout << "\n\tYour opponet's board:\n" << endl;
					}

					//compBoard.showBoard(); //test
					compBoard.showFakeBoard();//show user progress on opponent's board
				}
			}
		}

		cpuHit = userBoard.compHit(1);

		//if opponent hits user's ship
		if (cpuHit == true)
		{
			comp.incrementHits();
		}

		//show the progress of opponent to the user
		cout << "\n\tYour board:\n\n";
		userBoard.showBoard();

		if (user.getHits() == 17 || comp.getHits() == 17)
		{
			cout << "\n\t It seems like we have a winner!\n\n\tPress enter to see the results...";
			cin.ignore();
			getline(cin, str);
		}

	} while (user.getMisses() < 15 && user.getHits() < 17 && comp.getHits() < 17 && row != -1 && c != -1);

	if (row == -1 || c == -1)
	{
		cout << "\n\tYou exited the game!";
	}
	else
	{
		clearScreen(67, 40);
		setCursorPosiotion(0, 0);

		cout << "\n\tComputer's board\n\n";
		compBoard.showBoard();

		cout << "\n\tUser's board\n\n";
		userBoard.showBoard();

		if (user.getHits() == 17 && comp.getHits() == 17)
		{
			cout << "\n\tThere is no winner, you both sank each other's ships";
		}
		else if (user.getMisses() == 15)
		{
			cout << "\n\tGame over, you missed 15 times in a row.";
		}
		else if (user.getHits() == 17)
			cout << "\n\t" << user.getName() << " is the winner!";
		else
			cout << "\n\t" << comp.getName() << " is the winner!";
	}
	

	return 0;
}

void setCursorPosiotion(short x, short y)
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { x, y };
	SetConsoleCursorPosition(output, position);
}
void clearScreen(int length, int height)
{
	for (int x = 0; x < length; x++)
	{
		for (int y = 0; y < height; y++)
		{
			setCursorPosiotion(x, y);
			cout << " ";

		}
	}
}

void slowPrint(const string& message, unsigned int millis_per_char)
{
	// Range loops are "for each" constructs; here: for each character in the string
	for (const char c : message)
	{
		// flush is used to make sure the buffer is emptied to the terminal immediately
		cout << c << flush;

		// Ask the thread to sleep for at least n millis.
		sleep_for(milliseconds(millis_per_char));
	}
}

void welcomeMsg()
{
	cout << endl
		 << "\t                                      # #  ( )" << endl
		 << "\t                                   ___#_#___|__" << endl
		 << "\t                               _  |____________|  _" << endl
		 << "\t                       _=====| | |     1944     | | |==== _" << endl
		 << "\t                =====| | .---------------------------. | |====" << endl
		 << "\t  <<--------------------'   *  *  *  *  *  *  *  *    '---------- ---/" << endl
		 << "\t     \\___________________  WELCOME TO BATTLESHIP GAME ______________/" << endl
		 << "\t      \\____________________________________________________________/" << endl
		 << "\t  wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww" << endl
		 << "\twwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww" << endl
		 << "\t   wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww" << endl;
}

void gameDescriptionMsg()
{
	string msg1 = "\n\tRules:\n\n\tEach Player has 5 ships: \n\n\tFrigate (length 2)\n\tSub (length 3)\n\tDestroyer (length 3)\n\tBattleship (length 4)\n\tAircraft Carrier (length 5)";
	string msg2 = "\n\n\tYour task is to sink the ships of your opponent.";
	string msg3 = "\n\tTo shoot at the ship you have to choose a row number and a column letter on your oppoent's board.";
	string msg4 = "\n\tIf you hit the ship it will be marked 'X' on your opponent's board.";
	string msg5 = "\n\tIf you miss it will be marked 'O' on your opponent's board.";
	string msg6 = "\n\n\tGame ends when:\n\t1)One of the players sink their opponent's ships\n\t2)You miss 15 times in a row\n\t3)You enter -1";
	string msg7 = "\n\n\tLet the battle start!\n\n\tPress enter to continue...";
	slowPrint(msg1, 30);
	slowPrint(msg2, 30);
	slowPrint(msg3, 30);
	slowPrint(msg4, 30);
	slowPrint(msg5, 30);
	slowPrint(msg6, 30);
	slowPrint(msg7, 30);
}

void missedMsg()
{
	string msg1 = "\n\tOh no, you missed!\n";
	string msg2 = "\n\tMaybe try a different row next time!\n";
	string msg3 = "\n\tSeems like you had a bad luck this time :(\n";
	string msg4 = "\n\tDon't be sad you can always try again!\n";
	string msg5 = "\n\tI hope you will have better luck next time!\n";

	//initialize random seed:
	srand(static_cast<unsigned int>(time(NULL)));
	int a = rand() % 5;

	switch (a)
	{
	case 0: cout << msg1;
		break;
	case 1: cout << msg2;
		break;
	case 2: cout << msg3;
		break;
	case 3: cout << msg4;
		break;
	case 4: cout << msg5;
	}
}

void hitMsg()
{
	string msg1 = "\n\tKeep it up!\n";
	string msg2 = "\n\tThat's a hit!\n";
	string msg3 = "\n\tYou're almost there!\n";
	string msg4 = "\n\tYour enemy has no chance!\n";
	string msg5 = "\n\tGood job!\n";

	//initialize random seed:
	srand(static_cast<unsigned int>(time(NULL)));
	int a = rand() % 5;

	switch (a)
	{
	case 0: cout << msg1;
		break;
	case 1: cout << msg2;
		break;
	case 2: cout << msg3;
		break;
	case 3: cout << msg4;
		break;
	case 4: cout << msg5;
	}
}
/*

*/
