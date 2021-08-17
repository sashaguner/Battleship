// (c) Oleksandra Kasatkina, 2019

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
using namespace std;
class Player
{
private:
	string name;
	int hits;
	int misses;

public:
	Player();
	void setName();
	string getName();
	void setHits(int);
	int getHits();
	void setMisses(int);
	int getMisses();
	void incrementMisses();
	void incrementHits();
};

#endif
