#ifndef weapons_h
#define weapons_h
#include "items.h"

class weapon : public item
{
public:
	weapon();
	~weapon();

	void SetAttack(int attack_) { attack = attack_; };
	int GetAttack() { return attack; };

	

private:
	int attack;
};

#endif
