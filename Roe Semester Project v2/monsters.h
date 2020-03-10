#ifndef monsters_h
#define monsters_h

#include <iostream>
using namespace std;

struct monster
{
	string name;
	int namelength;
	int maxhealth;
	int health;
	int mana;
	int defense;
	int damage;
	int level;
};

struct creatures
{
	monster slime;
	monster bat;
	monster skeleton;
};

#endif
