// (c) Oleksandra Kasatkina, 2019

#include "Board.h"		// board class
#include <iostream>		// cout, cin
#include <iomanip>		// setw()
#include <stdio.h>      // printf, scanf, NULL
#include <stdlib.h>     // srand, rand
#include <time.h>       // time

using namespace std;

const int ROWS = 10;
const int COLS = 10;

//constructor sets all variables to 0
Board::Board()
{
	currentRow = 0;
	currentCol = 0;
	Fcount = 0;
	Scount = 0;
	Dcount = 0;
	Bcount = 0;
	Acount = 0;
	rowStartF = 0; colStartF = 0; rowEndF = 0; colEndF = 0;
	rowStartS = 0; colStartS = 0; rowEndS = 0; colEndS = 0;
	rowStartD = 0; colStartD = 0; rowEndD = 0; colEndD = 0;
	rowStartB = 0; colStartB = 0; rowEndB = 0; colEndB = 0;
	rowStartA = 0; colStartA = 0; rowEndA = 0; colEndA = 0;
	directionF = 0; directionS = 0; directionD = 0; directionB = 0; directionA = 0;
}

//returns count of Frigate ship pieces
int Board::getShipFcount()
{
	return Fcount;
}

void Board::setShipFCount(int num)
{
	Fcount = num;
}

//returns count of Submarine ship pieces
int Board::getShipScount()
{
	return Scount;
}

void Board::setShipSCount(int num)
{
	Scount = num;
}

//returns count of Destroyer ship pieces
int Board::getShipDcount()
{
	return Dcount;
}

void Board::setShipDCount(int num)
{
	Dcount = num;
}

//returns count of Battleship ship pieces
int Board::getShipBcount()
{
	return Bcount;
}

void Board::setShipBCount(int num)
{
	Bcount = num;
}

//returns count of Aircraft Carrier ship pieces
int Board::getShipAcount()
{
	return Acount;
}

void Board::setShipACount(int num)
{
	Acount = num;
}

//accepts row and column numbers and returns content of that cell
string Board::getBoardcell(int row, int col)
{
	return gameBoard[row][col];
}

//initializes player board with dots
void Board::createBoard()
{
	//Initialize game board with dots
	for (currentRow = 0; currentRow < ROWS; currentRow++)
	{
		for (currentCol = 0; currentCol < COLS; currentCol++)
		{
			gameBoard[currentRow][currentCol] = " . ";
		}
	}

	//test function
	//cout << "\n\tBoard is created.\n\n";
}

//initializes fake board (used as opponet's board with hidden ships) with dots
void Board::createFakeBoard()
{
	//Initialize fake board with dots
	for (currentRow = 0; currentRow < ROWS; currentRow++)
	{
		for (currentCol = 0; currentCol < COLS; currentCol++)
		{
			fakeBoard[currentRow][currentCol] = " . ";
		}
	}
}

//prints player's board on the screen
void Board::showBoard()
{
	//Show the board
	cout << "\t    a  b  c  d  e  f  g  h  i  j\n";
	for (currentRow = 0; currentRow < ROWS; currentRow++)
	{
		//print number of the raw in the begining of each raw
		cout << "\t" << setw(2) << right << (currentRow + 1) << " ";

		//print the board
		for (currentCol = 0; currentCol < COLS; currentCol++)
		{
			cout << gameBoard[currentRow][currentCol];
		}

		cout << endl;
	}

	//create a new line
	cout << endl;
}

//prints fake board on the screen
void Board::showFakeBoard()
{
	//Show the board
	cout << "\t    a  b  c  d  e  f  g  h  i  j\n";
	for (currentRow = 0; currentRow < ROWS; currentRow++)
	{
		//print number of the raw in the begining of each raw
		cout << "\t" << setw(2) << right << (currentRow + 1) << " ";

		//print the board
		for (currentCol = 0; currentCol < COLS; currentCol++)
		{
			cout << fakeBoard[currentRow][currentCol];
		}

		cout << endl;
	}

	//create a new line
	cout << endl;
}

//accepts a letter to indicate type of ship, number of ship pieces this type of ship can hold and an integer to modify srand 
void Board::placeShipsOnBoard(string letter, int num, int seed)
{
	
	//initialize random seed:
	srand(static_cast<unsigned int>(time(NULL))+seed);
	bool placed = true;
	int loopCounter = 0;

	do
	{
		//keep generating random numbers unitll random space on the board is available
		do
		{
			currentRow = rand() % 10;
			currentCol = rand() % 10;
		} while (gameBoard[currentRow][currentCol] != " . ");

		int direction = rand() % 4;

		//down
		if (direction == 0 || direction == 2)
		{
			//CASE 1
			//if ship starts from the last row
			if (currentRow == 9)
			{
				placed = false;
			}
			//CASE 2
			//if ship is longer than the number of rows down
			else if ((currentRow + (num - 1)) > 9)
			{
				placed = false;
			}
			//CASE 3
			//if ship starts at the left upper corner [0][0]
			else if (currentRow == 0 && currentCol == 0)
			{
				int counter = 0;//to count false values

				//check if cells are empty down and +1 column right
				for (int r = currentRow; r <= (currentRow + num); r++) 
				{
					for (int c = currentCol; c <= (currentCol + 1); c++)
					{
						if (gameBoard[r][c] != " . ")
						{
							//counts number of ccupied spots
							counter++;
						} 
					}
				}
				if (counter == 0)//if empty place the ship
				{
					for (int r = currentRow; r < (currentRow + num); r++)
					{
						gameBoard[r][currentCol] = letter;
					}
					placed = true;
				}
				else//if not empty return false
				{
					placed = false;
				}
			}
			//CASE 4
			//if ship starts at right upper corner
			else if (currentRow == 0 && currentCol == 9)
			{
				int counter = 0;//to count false values

				//check if cells are empty down and 1 cell to the left
				for (int r = currentRow; r <= (currentRow + num); r++)
				{
					for (int c = (currentCol - 1); c <= currentCol; c++)
					{
						if (gameBoard[r][c] != " . ")
						{
							counter++;
						} 
					}
				}
				if (counter == 0)//if empty place the ship
				{
					for (int r = currentRow; r < (currentRow + num); r++)
					{
						gameBoard[r][currentCol] = letter;
					}
					placed = true;
				}
				else//if not empty return false
				{
					placed = false;
				}
			}
			//CASE 5
			//if ship starts anywhere from first row
			else if (currentRow == 0)
			{
				int counter = 0;//to count false values

				//check if cells are empty down and around the ship
				for (int r = currentRow; r <= (currentRow + num); r++)
				{
					for (int c = (currentCol - 1); c <= (currentCol + 1); c++)
					{
						if (gameBoard[r][c] != " . ")
						{
							counter++;
						} 
					}
				}
				if (counter == 0)//if empty place the ship
				{
					for (int r = currentRow; r < (currentRow + num); r++)
					{
						gameBoard[r][currentCol] = letter;
					}
					placed = true;
				}
				else//if not empty return false
				{
					placed = false;
				}
			}
			//CASE 6
			//if ship starts anywhere in first column
			else if (currentCol == 0)
			{
				int counter = 0;//to count false values

				//if ship will end at the 9th row
				if ((currentRow + (num - 1)) == 9)
				{
					//check if cells are emtpy for the ship and around the ship
					for (int r = (currentRow - 1); r <= (currentRow + (num - 1)); r++)
					{
						for (int c = currentCol; c <= (currentCol + 1); c++)
						{
							if (gameBoard[r][c] != " . ")
							{
								counter++;
							}
						}
					}
				}
				else
				{
					//check if cells are empty down, 1 cell up and 1 cell to the right
					for (int r = (currentRow - 1); r <= (currentRow + num); r++)
					{
						for (int c = currentCol; c <= (currentCol + 1); c++)
						{
							if (gameBoard[r][c] != " . ")
							{
								counter++;
							}
						}
					}
				}

				if (counter == 0)//if empty place the ship
				{
					for (int r = currentRow; r < (currentRow + num); r++)
					{
						gameBoard[r][currentCol] = letter;
					}
					placed = true;
				}
				else//if not empty return false
				{
					placed = false;
				}
			}
			//CASE 7
			//if ship starts anywhere in last column
			else if (currentCol == 9)
			{
				int counter = 0;//to count false values

				//if ship will end at the 9th row
				if ((currentRow + (num - 1)) == 9)
				{
					//check if cells are emtpy for the ship and around the ship
					for (int r = (currentRow - 1); r <= (currentRow + (num - 1)); r++)
					{
						for (int c = (currentCol - 1); c <= currentCol; c++)
						{
							if (gameBoard[r][c] != " . ")
							{
								counter++;
							}
						}
					}
				}
				else
				{
					//check if cells are empty down, 1 cell up and 1 cell to the left
					for (int r = (currentRow - 1); r <= (currentRow + num); r++)
					{
						for (int c = (currentCol - 1); c <= currentCol; c++)
						{
							if (gameBoard[r][c] != " . ")
							{
								counter++;
							}
						}
					}
				}
	
				if (counter == 0)//if empty place the ship
				{
					for (int r = currentRow; r < (currentRow + num); r++)
					{
						gameBoard[r][currentCol] = letter;
					}
					placed = true;
				}
				else//if not empty return false
				{
					placed = false;
				}
			}
			//CASE 8
			//if ship starts anywhere else on the board 
			else
			{
				int counter = 0;//to count false values

				//if ship ends at the 9th row
				if ((currentRow + (num - 1)) == 9)
				{
					//check if cells are emtpy for the ship and around the ship
					for (int r = (currentRow - 1); r <= (currentRow + (num - 1)); r++)
					{
						for (int c = (currentCol - 1); c <= (currentCol + 1); c++)
						{
							if (gameBoard[r][c] != " . ")
							{
								counter++;
							}
						}
					}
				}
				else
				{
					for (int r = (currentRow - 1); r <= (currentRow + num); r++)
					{
						for (int c = (currentCol - 1); c <= (currentCol + 1); c++)
						{
							if (gameBoard[r][c] != " . ")
							{
								counter++;
							}
						}
					}
				}
				
				if (counter == 0)//if empty place the ship
				{
					for (int r = currentRow; r < (currentRow + num); r++)
					{
						gameBoard[r][currentCol] = letter;
					}
					placed = true;
				}
				else//if not empty return false
				{
					placed = false;
				}
			}
		}//end if direction = 0

		//right
		if (direction == 1 || direction == 3)
		{
			//CASE 1
			//when ship starts at column 9
			if (currentCol == 9)
			{
				placed = false;
			}
			//CASE 2 
			//when ship is longer than the board
			else if ((currentCol + (num - 1)) > 9)
			{
				placed = false;
			}
			
			//CASE 3
			//when ship starts at left upper corner [0][0]
			else if (currentRow == 0 && currentCol == 0)
			{
				int counter = 0;//to count false values

				for (int r = currentRow; r <= (currentRow + 1); r++)
				{
					for (int c = currentCol; c <= (currentCol + num); c++)
					{
						if (gameBoard[r][c] != " . ")
						{
							counter++;
						}
					}
				}
				if (counter == 0)//if empty place the ship
				{
					for (int c = currentCol; c < (currentCol + num); c++)
					{
						gameBoard[currentRow][c] = letter;
					}
					placed = true;
				}
				else//if not empty return false
				{
					placed = false;
				}
			}
			//CASE 4
			//when ship starts at right lower corner
			else if (currentRow == 9 && currentCol == 0)
			{
				int counter = 0;//to count false values

				for (int r = (currentRow - 1); r <= currentRow; r++)
				{
					for (int c = currentCol; c <= (currentCol + num); c++)
					{
						if (gameBoard[r][c] != " . ")
						{
							counter++;
						}
					}
				}
				if (counter == 0)//if empty place the ship
				{
					for (int c = currentCol; c < (currentCol + num); c++)
					{
						gameBoard[currentRow][c] = letter;
					}
					placed = true;
				}
				else//if not empty return false
				{
					placed = false;
				}
			}
			//CASE 5
			//when ship starts anywhere from the first column
			else if (currentCol == 0)
			{
				int counter = 0;//to count false values

				for (int r = (currentRow - 1); r <= (currentRow + 1); r++)
				{
					for (int c = currentCol; c <= (currentCol + num); c++)
					{
						if (gameBoard[r][c] != " . ")
						{
							counter++;
						}
					}
				}
				if (counter == 0)//if empty place the ship
				{
					for (int c = currentCol; c < (currentCol + num); c++)
					{
						gameBoard[currentRow][c] = letter;
					}
					placed = true;
				}
				else//if not empty return false
				{
					placed = false;
				}
			}
			//CASE 6
			//when ship starts anywhere in first row
			else if (currentRow == 0)
			{
				int counter = 0;//to count false values

				//when ship ends at column 9
				if ((currentCol + (num - 1)) == 9)
				{
					for (int r = currentRow; r <= (currentRow + 1); r++)
					{
						for (int c = (currentCol - 1); c <= (currentCol + (num - 1)); c++)
						{
							if (gameBoard[r][c] != " . ")
							{
								counter++;
							}
						}
					}
				}
				else
				{
					//check if cells are empty from 1 cell before the ship begins and 1 cell after ship ends and below the ship
					for (int r = currentRow; r <= (currentRow + 1); r++)
					{
						for (int c = (currentCol - 1); c <= (currentCol + num); c++)
						{
							if (gameBoard[r][c] != " . ")
							{
								counter++;
							}
						}
					}
				}
				
				if (counter == 0)//if empty place the ship
				{
					for (int c = currentCol; c < (currentCol + num); c++)
					{
						gameBoard[currentRow][c] = letter;
					}
					placed = true;
				}
				else//if not empty return false
				{
					placed = false;
				}
			}
			//CASE 7
			//when ship starts anywhere in last row
			else if (currentRow == 9)
			{
				int counter = 0;//to count false values

				//when ship ends at column 9
				if ((currentCol + (num - 1)) == 9)
				{
					for (int r = currentRow - 1; r <= currentRow; r++)
					{
						for (int c = (currentCol - 1); c <= (currentCol + (num - 1)); c++)
						{
							if (gameBoard[r][c] != " . ")
							{
								counter++;
							}
						}
					}
				}
				else
				{
					//check if cells are empty 1 cell before ship starts and 1 cell after ship ends and on top
					for (int r = (currentRow - 1); r <= currentRow; r++)
					{
						for (int c = (currentCol - 1); c <= (currentCol + num); c++)
						{
							if (gameBoard[r][c] != " . ")
							{
								counter++;
							}
						}
					}
				}
				
				if (counter == 0)//if empty place the ship
				{
					for (int c = currentCol; c < (currentCol + num); c++)
					{
						gameBoard[currentRow][c] = letter;
					}
					placed = true;
				}
				else//if not empty return false
				{
					placed = false;
				}
			}
			//CASE 8
			//when ship starts anywhere on the board
			else
			{
				int counter = 0;//to count false values

				//when ship ends at column 9
				if ((currentCol + (num - 1)) == 9)
				{
					for (int r = currentRow - 1; r <= (currentRow + 1); r++)
					{
						for (int c = (currentCol - 1); c <= (currentCol + (num - 1)); c++)
						{
							if (gameBoard[r][c] != " . ")
							{
								counter++;
							}
						}
					}
				}
				else
				{
					//check if cells are empty around the ship
					for (int r = (currentRow - 1); r <= (currentRow + 1); r++)
					{
						for (int c = (currentCol - 1); c <= (currentCol + num); c++)
						{
							if (gameBoard[r][c] != " . ")
							{
								counter++;
							}
						}
					}
				}
				
				if (counter == 0)//if empty place the ship
				{
					for (int c = currentCol; c < (currentCol + num); c++)
					{
						gameBoard[currentRow][c] = letter;
					}
					placed = true;
				}
				else//if not empty return false
				{
					placed = false;
				}
			}
		}//end if

		loopCounter++;

	}while (placed == false);//end do while loop

	//cout << "Placed: " << placed << endl << "Counter: " << loopCounter << endl;
}//end method

/*
Accepts a row and a column numbers from user's input and checks if that cell contains a ship piece.
If yes than ship is hit, if no, than player missed.
Tracks number of ship pieces hit in each ship.
If all ship pieces are hit ship is sunk. Puts Os around each sunk ship to indicate that the ship is sunk
*/
bool Board::hit(int row, int col, int difLevel)
{
	//cout << directionS << " " << directionD << " " << directionB << " " << directionA;
	//if spot is empty player missed
	if (gameBoard[row][col] == " X ")
	{
		return false;
	}
	else if (gameBoard[row][col] == " . ")
	{
		gameBoard[row][col] = " O ";
		fakeBoard[row][col] = " O ";

		return false;
	}//if spot has a letter inside player hit the ship
	else if (gameBoard[row][col] != " . " && (gameBoard[row][col] != " O "))
	{
		if (gameBoard[row][col] == " F ")//if player hit Frigate
		{
			//count Frigate ship pieces to indicate if player sank the ship
			Fcount++;
			//mark spaces around ship with "O" to indicate that ship is sunk, so that user doesn't shoot aimlessly those spots
			if (difLevel == 1)
			{
				if (Fcount == 2)
				{
					//if ship goes down
					if (directionF == 1)
					{
						//mark spaces around ship with "O" to indicate that ship is sunk, so that user doesn't shoot aimlessly those spots
						for (int r = (rowStartF - 1); r <= (rowStartF + 2); r++)
						{
							for (int c = (colStartF - 1); c <= (colStartF + 1); c++)
							{
								if (c == -1)
									fakeBoard[r][0] = " O ";
								else if (r < 0 || r > 9 || c < 0 || c > 9)
									break;
								else
									fakeBoard[r][c] = " O ";
							}
						}
						//reassign Xs to ship spots
						for (int i = 0; i < 2; i++)
						{
							gameBoard[rowStartF + i][colStartF] = " X ";
							fakeBoard[rowStartF + i][colStartF] = " X ";
						}
					}
					//if ship goes right
					else if (directionF == 2)
					{
						//mark spaces around ship with "O" to indicate that ship is sunk, so that user doesn't shoot aimlessly those spots
						for (int r = (rowStartF - 1); r <= (rowStartF + 1); r++)
						{
							for (int c = (colStartF - 1); c <= (colStartF + 2); c++)
							{
								if (c == -1)
									fakeBoard[r][0] = " O ";
								else if (r < 0 || r > 9 || c < 0 || c > 9)
									break;
								else
									fakeBoard[r][c] = " O ";
							}
						}

						//reassign Xs to ship spots
						for (int i = 0; i < 2; i++)
						{
							gameBoard[rowStartF][colStartF + i] = " X ";
							fakeBoard[rowStartF][colStartF + i] = " X ";
						}
					}
				}
			}
		}//if player hit Submarine
		else if (gameBoard[row][col] == " S ")
		{
			//count Submarine ship pieces to indicate if player sank the ship
			Scount++;
			if (difLevel == 1)
			{
				if (Scount == 3)
				{
					//cout << "Scount: " << Scount << endl << "rowStartS: " << rowStartS << "colStartS: " << colStartS << endl;
					//if ship goes down
					if (directionS == 1)
					{
						//mark spaces around ship with "O" to indicate that ship is sunk, so that user doesn't shoot aimlessly those spots
						for (int r = (rowStartS - 1); r <= (rowStartS + 3); r++)
						{
							for (int c = (colStartS - 1); c <= (colStartS + 1); c++)
							{
								if (c == -1)
									fakeBoard[r][0] = " O ";
								else if (r < 0 || r > 9 || c < 0 || c > 9)
									break;
								else
									fakeBoard[r][c] = " O ";
							}
						}
						//reassign Xs to ship spots
						for (int i = 0; i < 3; i++)
						{
							gameBoard[rowStartS + i][colStartS] = " X ";
							fakeBoard[rowStartS + i][colStartS] = " X ";
						}
					}
					//if ship goes right
					else if (directionS == 2)
					{
						//mark spaces around ship with "O" to indicate that ship is sunk, so that user doesn't shoot aimlessly those spots
						for (int r = (rowStartS - 1); r <= (rowStartS + 1); r++)
						{
							for (int c = (colStartS - 1); c <= (colStartS + 3); c++)
							{
								if (c == -1)
									fakeBoard[r][0] = " O ";
								else if (r < 0 || r > 9 || c < 0 || c > 9)
									break;
								else
									fakeBoard[r][c] = " O ";
							}
						}

						//reassign Xs to ship spots
						for (int i = 0; i < 3; i++)
						{
							gameBoard[rowStartS][colStartS + i] = " X ";
							fakeBoard[rowStartS][colStartS + i] = " X ";
						}
					}
				}
			}
		}//if player hit Destroyer
		else if (gameBoard[row][col] == " D ")
		{
			//count Destroyer ship pieces to indicate if player sank the ship
			Dcount++;
			if (difLevel == 1)
			{
				//if count equals to number of ship pieces the ship is sunk
				if (Dcount == 3)
				{
					//cout << "Dcount: " << Dcount << endl << "rowStartD" << rowStartD << "colStartD: " << colStartD << endl;
					//if ship goes down
					if (directionD == 1)
					{
						//mark spaces around ship with "O" to indicate that ship is sunk, so that user doesn't shoot aimlessly those spots
						for (int r = (rowStartD - 1); r <= (rowStartD + 3); r++)
						{
							for (int c = (colStartD - 1); c <= (colStartD + 1); c++)
							{
								if (c == -1)
									fakeBoard[r][0] = " O ";
								else if (r < 0 || r > 9 || c < 0 || c > 9)
									break;
								else
									fakeBoard[r][c] = " O ";
							}
						}

						//reassign Xs to ship spots
						for (int i = 0; i < 3; i++)
						{
							gameBoard[rowStartD + i][colStartD] = " X ";
							fakeBoard[rowStartD + i][colStartD] = " X ";
						}
					}
					//if ship goes right
					else if (directionD == 2)
					{
						//mark spaces around ship with "O" to indicate that ship is sunk, so that user doesn't shoot aimlessly those spots
						for (int r = (rowStartD - 1); r <= (rowStartD + 1); r++)
						{
							for (int c = (colStartD - 1); c <= (colStartD + 3); c++)
							{
								if (c == -1)
									fakeBoard[r][0] = " O ";
								else if (r < 0 || r > 9 || c < 0 || c > 9)
									break;
								else
									fakeBoard[r][c] = " O ";
							}
						}

						//reassign Xs to ship spots
						for (int i = 0; i < 3; i++)
						{
							gameBoard[rowStartD][colStartD + i] = " X ";
							fakeBoard[rowStartD][colStartD + i] = " X ";
						}
					}
				}
			}
		}//if player hit Battleship
		else if (gameBoard[row][col] == " B ")
		{
			//count Battleship ship pieces to indicate if player sank the ship
			Bcount++;
			if (difLevel == 1)
			{
				if (Bcount == 4)
				{
					//cout << "Bcount: " << Bcount << endl << "rowStartB" << rowStartB << "colStartB: " << colStartB << endl;
					//if ship goes down
					if (directionB == 1)
					{
						//mark spaces around ship with "O" to indicate that ship is sunk, so that user doesn't shoot aimlessly those spots
						for (int r = (rowStartB - 1); r <= (rowStartB + 4); r++)
						{
							for (int c = (colStartB - 1); c <= (colStartB + 1); c++)
							{
								if (c == -1)
									fakeBoard[r][0] = " O ";
								else if (r < 0 || r > 9 || c < 0 || c > 9)
									break;
								else
									fakeBoard[r][c] = " O ";
							}
						}

						//reassign Xs to ship spots
						for (int i = 0; i < 4; i++)
						{
							gameBoard[rowStartB + i][colStartB] = " X ";
							fakeBoard[rowStartB + i][colStartB] = " X ";
						}

					}
					//if ship goes right
					else if (directionB == 2)
					{
						//mark spaces around ship with "O" to indicate that ship is sunk, so that user doesn't shoot aimlessly those spots
						for (int r = (rowStartB - 1); r <= (rowStartB + 1); r++)
						{
							for (int c = (colStartB - 1); c <= (colStartB + 4); c++)
							{
								if (c == -1)
									fakeBoard[r][0] = " O ";
								else if (r < 0 || r > 9 || c < 0 || c > 9)
									break;
								else
									fakeBoard[r][c] = " O ";
							}
						}

						//reassign Xs to ship spots
						for (int i = 0; i < 4; i++)
						{
							gameBoard[rowStartB][colStartB + i] = " X ";
							fakeBoard[rowStartB][colStartB + i] = " X ";
						}
					}
				}
			}
		}//if player hit Aircraft Carrier
		else if (gameBoard[row][col] == " A ")
		{
			//count Aircraft Carrier ship pieces to indicate if player sank the ship
			Acount++;
			if (difLevel == 1)
			{
				if (Acount == 5)
				{
					//cout << "Acount: " << Acount << endl << "rowStartA" << rowStartA << "colStartA: " << colStartA << endl;
					//if ship goes down
					if (directionA == 1)
					{
						//mark spaces around ship with "O" to indicate that ship is sunk, so that user doesn't shoot aimlessly those spots
						for (int r = (rowStartA - 1); r <= (rowStartA + 5); r++)
						{
							for (int c = (colStartA - 1); c <= (colStartA + 1); c++)
							{
								if (c == -1)
									fakeBoard[r][0] = " O ";
								else if (r < 0 || r > 9 || c < 0 || c > 9)
									break;
								else
									fakeBoard[r][c] = " O ";
							}
						}

						//reassign Xs to ship spots
						for (int i = 0; i < 5; i++)
						{
							gameBoard[rowStartA + i][colStartA] = " X ";
							fakeBoard[rowStartA + i][colStartA] = " X ";
						}

					}
					//if ship goes right
					else if (directionA == 2)
					{
						//mark spaces around ship with "O" to indicate that ship is sunk, so that user doesn't shoot aimlessly those spots
						for (int r = (rowStartA - 1); r <= (rowStartA + 1); r++)
						{
							for (int c = (colStartA - 1); c <= (colStartA + 5); c++)
							{
								if (c == -1)
									fakeBoard[r][0] = " O ";
								else if (r < 0 || r > 9 || c < 0 || c > 9)
									break;
								else
									fakeBoard[r][c] = " O ";
							}
						}

						//reassign Xs to ship spots
						for (int i = 0; i < 5; i++)
						{
							gameBoard[rowStartA][colStartA + i] = " X ";
							fakeBoard[rowStartA][colStartA + i] = " X ";
						}
					}
				}
			}
		}

		//assign X to hit ship cell
		gameBoard[row][col] = " X ";
		fakeBoard[row][col] = " X ";

		return true;
	}

}

//hit function for CPU
//if CPU is playing against itself than an integer argument more than 0 is required
bool Board::compHit(int seed)
{
	int row, col;

	//initialize random seed:
	srand(static_cast<unsigned int>(time(NULL) + seed));

	do
	{
		row = rand() % 10;
		col = rand() % 10;
	} while (gameBoard[row][col] == " O " || gameBoard[row][col] == " X ");

	if (gameBoard[row][col] == " . ")
	{
		gameBoard[row][col] = " O ";
		return false;
	}
	else if (gameBoard[row][col] != " . " && (gameBoard[row][col] != " O "))
	{
		gameBoard[row][col] = " X ";
		return true;
	}
}

//to get direction of each ship
void Board::detectShips()
{
	int countF = 0, countS = 0, countD = 0, countB = 0, countA = 0;
	for (int r = 0; r < 10; r++)
	{
		for (int c = 0; c < 10; c++)
		{
			if (gameBoard[r][c] == " F ")
			{
				countF++;
				if (countF == 1)
				{
					rowStartF = r;
					colStartF = c;
				}
				else if (countF == 2)
				{
					rowEndF = r;
					colEndF = c;
				}

				if (rowStartF < rowEndF)
					directionF = 1;//down
				else if (colStartF < colEndF)
					directionF = 2;//right
			}
			else if (gameBoard[r][c] == " S ")
			{
				countS++;
				if (countS == 1)
				{
					rowStartS = r;
					colStartS = c;
				}
				else if (countS == 3)
				{
					rowEndS = r;
					colEndS = c;
				}

				if (rowStartS < rowEndS)
					directionS = 1;//down
				else if (colStartS < colEndS)
					directionS = 2;//right
			}
			else if (gameBoard[r][c] == " D ")
			{
				countD++;
				if (countD == 1)
				{
					rowStartD = r;
					colStartD = c;
				}
				else if (countD == 3)
				{
					rowEndD = r;
					colEndD = c;
				}

				if (rowStartD < rowEndD)
					directionD = 1;//down
				else if (colStartD < colEndD)
					directionD = 2;//right
			}
			else if (gameBoard[r][c] == " B ")
			{
				countB++;
				if (countB == 1)
				{
					rowStartB = r;
					colStartB = c;
				}
				else if (countB == 4)
				{
					rowEndB = r;
					colEndB = c;
				}

				if (rowStartB < rowEndB)
					directionB = 1;//down
				else if (colStartB < colEndB)
					directionB = 2;//right
			}
			else if (gameBoard[r][c] == " A ")
			{
				countA++;
				if (countA == 1)
				{
					rowStartA = r;
					colStartA = c;
				}
				else if (countA == 4)
				{
					rowEndA = r;
					colEndA = c;
				}

				if (rowStartA < rowEndA)
					directionA = 1;//down
				else if (colStartA < colEndA)
					directionA = 2;//right
			}
		}
	}
}
