#include "bat.h"

bat::bat()
{
	SetName("Bat");
	SetNamelength(3);
	SetMaxhealth(6);
	SetHealth(6);
	SetMaxmana(0);
	SetMana(0);
	SetDefense(0);
	SetDamage(2);
	SetLevel(2);
}

bat::~bat()
{
}
