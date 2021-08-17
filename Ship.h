// (c) Oleksandra Kasatkina, 2019

#ifndef SHIP_H
#define SHIP_H

#include <string>
using namespace std;

class Ship
{
private:
	string shipPiece;
	int numOfShipPieces;

public:

	//constructor assigns first letter of the name of the ship to the ship piece 
	Ship(string, int);

	void createShipPiece(string, int);

	//create ship
	void destroyShipPiece();

	//give access to private variables
	string getShipPiece() const;
	int getNumOfShipPieces() const;
};

#endif
