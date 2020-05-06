#include "monsters.h"

monster::monster()
{
	name = "Debug";
	namelength = 5;
	maxhealth = 1;
	health = 1;
	maxmana = 1;
	mana = 1;
	defense = 1;
	damage = 1;
	level = 1;
	magiccost = 0;
	magicpower = 0;
}

monster::~monster()
{
}
