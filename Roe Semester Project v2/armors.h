#ifndef armors_h
#define armors_h
#include "items.h"

class armor : public item
{
public:
	armor();
	~armor();

	void SetDefense(int defense_) { defense = defense_; };
	int GetDefense() { return defense; };

private:
	int defense;
};

#endif

