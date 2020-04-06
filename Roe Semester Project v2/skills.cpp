#include "skills.h"

void skillstats(skill skills[20])
{
	skills[0].name = "Attack";
	skills[0].power = 0;
	skills[0].multiplier = 1;
	skills[0].healthcost = 0;
	skills[0].manacost = 0;
	skills[0].available = true;

	skills[1].name = "Focus";
	skills[1].power = 0;
	skills[1].multiplier = 0;
	skills[1].healthcost = 0;
	skills[1].manacost = -2;
	skills[1].available = true;

	skills[2].name = "Firebolt";
	skills[2].power = 2;
	skills[2].multiplier = 1;
	skills[2].healthcost = 0;
	skills[2].manacost = 3;
	skills[2].available = true;

}