// (c) Oleksandra Kasatkina, 2019

#include "Player.h"
#include <string>
using namespace std;

Player::Player()
{
	name = "CPU";
	hits = 0;
	misses = 0;
}
void Player::setName()
{
	cout << "\n\n\tEnter your name: ";
	cin >> name;
}

string Player::getName()
{
	return name;
}

void Player::setHits(int num)
{
	hits = num;
}

int Player::getHits()
{
	return hits;
}

void Player::setMisses(int num)
{
	misses = num;
}

int Player::getMisses()
{
	return misses;
}

void Player::incrementMisses()
{
	misses++;
}

void Player::incrementHits()
{
	hits++;
}
