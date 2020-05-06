#ifndef items_h
#define items_h

#include <iostream>
#include <vector>
using namespace std;

class item
{
public:
	item();
	~item();

	void SetName(string name_) { name = name_; };
	string GetName() { return name; };

	void SetNamelength(int namelength_) { namelength = namelength_; };
	int GetNamelength() { return namelength; };

	void SetBuyvalue(int buyvalue_) { buyvalue = buyvalue_; };
	int GetBuyvalue() { return buyvalue; };

	void SetSellvalue(int sellvalue_) { sellvalue = sellvalue_; };
	int GetSellvalue() { return sellvalue; };

	void SetPlayerhas(bool playerhas_) { playerhas = playerhas_; };
	int GetPlayerhas() { return playerhas; };

	void SetVectorsize(int vectorsize_) { vectorsize = vectorsize_; };
	int GetVectorsize() { return vectorsize; };

private:
	string name;
	int namelength;
	int buyvalue;
	int sellvalue;
	bool playerhas;
	int vectorsize;
};

#endif