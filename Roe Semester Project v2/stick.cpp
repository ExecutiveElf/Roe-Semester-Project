#include "stick.h"

stick::stick()
{
	SetName("Stick");
	SetNamelength(5);
	SetBuyvalue(0);
	SetSellvalue(0);
	SetAttack(1);

	SetPlayerhas(true);
}

stick::~stick()
{
}
