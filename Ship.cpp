// (c) Oleksandra Kasatkina, 2019

#include "Ship.h"

#include <string>
using namespace std;

//constructor assigns empty space to the variable
Ship::Ship(string letter, int num)
{
	shipPiece = letter;
	numOfShipPieces = num;
}

//assigns first letter of the name of the ship to the ship piece 
void Ship::createShipPiece(string letter, int num)
{
	shipPiece = letter;
	numOfShipPieces = num;
}

//get value of shipPiece
string Ship::getShipPiece() const
{
	return shipPiece;
}

//get value of numOfShipPieces
int Ship::getNumOfShipPieces() const
{
	return numOfShipPieces;
}

//destroys ship piece by assigning empty space to the variable
void Ship::destroyShipPiece()
{
	shipPiece = "[]";
}
