#ifndef skills_h
#define skills_h

using namespace std;
#include <iostream>

struct skill
{
	string name;
	int power;
	int multiplier;
	int healthcost;
	int manacost;
	bool available;
};

struct abilities
{
	skill attack;
	skill firebolt;
	skill heal;
};


#endif
