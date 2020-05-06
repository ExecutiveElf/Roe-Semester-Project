#include "ghoul.h"

ghoul::ghoul()
{
	SetName("Ghoul");
	SetNamelength(5);
	SetMaxhealth(15);
	SetHealth(10);
	SetMaxmana(0);
	SetMana(0);
	SetDefense(1);
	SetDamage(3);
	SetLevel(5);
}

ghoul::~ghoul()
{
}
