#ifndef BOARD_H
#define BOARD_H

#include <string>
using namespace std;

class Board
{
	private:
		string gameBoard[10][10];
		string fakeBoard[10][10];
		int currentRow;
		int currentCol;
		int Fcount;
		int Scount;
		int Dcount;
		int Bcount;
		int Acount;
		int rowStartF, colStartF, rowEndF, colEndF;
		int rowStartS, colStartS, rowEndS, colEndS;
		int rowStartD, colStartD, rowEndD, colEndD;
		int rowStartB, colStartB, rowEndB, colEndB;
		int rowStartA, colStartA, rowEndA, colEndA;
		int directionF, directionS, directionD, directionB, directionA;// 1 - down; 2 - right

	public:
		Board();
		int getShipFcount();
		void setShipFCount(int);
		int getShipScount();
		void setShipSCount(int);
		int getShipDcount();
		void setShipDCount(int);
		int getShipBcount();
		void setShipBCount(int);
		int getShipAcount();
		void setShipACount(int);

		string getBoardcell(int, int);
		void createBoard();
		void createFakeBoard();
		void showBoard();
		void showFakeBoard();
		void placeShipsOnBoard(string, int, int);
		bool hit(int, int, int);
		bool compHit(int);
		void detectShips();
};

#endif