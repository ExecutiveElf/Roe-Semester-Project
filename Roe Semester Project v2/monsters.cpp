#include "monsters.h"

void monsterstats(monster mon[100])
{
	mon[0].name = "Slime";
	mon[0].namelength = 5;
	mon[0].maxhealth = 4;
	mon[0].health = 4;
	mon[0].mana = 0;
	mon[0].defense = 0;
	mon[0].damage = 1;
	mon[0].level = 1;

	mon[1].name = "Bat";
	mon[1].namelength = 3;
	mon[1].maxhealth = 6;
	mon[1].health = 6;
	mon[1].mana = 0;
	mon[1].defense = 0;
	mon[1].damage = 2;
	mon[1].level = 2;

	mon[2].name = "Skeleton";
	mon[2].namelength = 8;
	mon[2].maxhealth = 10;
	mon[2].health = 10;
	mon[2].mana = 0;
	mon[2].defense = 0;
	mon[2].damage = 3;
	mon[2].level = 3;
}
