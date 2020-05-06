#ifndef potions_h
#define potions_h
#include "items.h"

class potion : public item
{
public:
	potion();
	~potion();

	void SetHPheal(int hpheal_) { hpheal = hpheal_; };
	int GetHPheal() { return hpheal; };

	void SetMPheal(int mpheal_) { mpheal = mpheal_; };
	int GetMPheal() { return mpheal; };

private:
	int hpheal;
	int mpheal;
};

#endif

