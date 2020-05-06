#include "player.h"

player::player()
{
	maxhealth = 10;
	health = 10;
	maxmana = 5;
	mana = 5;
	defense = 0;
	damage = 1;
	level = 1;
	exp = 0;
	gold = 100;
	weapon = 1;
	armor = 0;
}

player::~player()
{
}
