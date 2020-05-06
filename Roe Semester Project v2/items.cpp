#include "items.h"
#include <vector>

item::item()
{
	name = "None";
	namelength = 4;
	buyvalue = 0;
	sellvalue = 0;
	playerhas = false;
}

item::~item()
{
}