#include "zombie.h"

zombie::zombie()
{
	SetName("Zombie");
	SetNamelength(5);
	SetMaxhealth(12);
	SetHealth(12);
	SetMaxmana(1);
	SetMana(1);
	SetDefense(1);
	SetDamage(3);
	SetLevel(4);
	SetMagiccost(1);
	SetMagicpower(3);
}

zombie::~zombie()
{
}
