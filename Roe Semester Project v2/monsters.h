#ifndef monsters_h
#define monsters_h

#include <iostream>
using namespace std;

class monster
{
public:
	monster();
	~monster();

	void SetName(string name_) { name = name_; };
	string GetName() { return name; };

	void SetNamelength(int namelength_) { namelength = namelength_; };
	int GetNamelength() { return namelength; };

	void SetMaxhealth(int maxhealth_) { maxhealth = maxhealth_; };
	int GetMaxhealth() { return maxhealth; };

	void SetHealth(int health_) { health = health_; };
	int GetHealth() { return health; };

	void SetMaxmana(int maxmana_) { maxmana = maxmana_; };
	int GetMaxmana() { return maxmana; };

	void SetMana(int mana_) { mana = mana_; };
	int GetMana() { return mana; };

	void SetDefense(int defense_) { defense = defense_; };
	int GetDefense() { return defense; };

	void SetDamage(int damage_) { damage = damage_; };
	int GetDamage() { return damage; };

	void SetLevel(int level_) { level = level_; };
	int GetLevel() { return level; };	

	void SetMagiccost(int magiccost_) {magiccost = magiccost_; };
	int GetMagiccost() { return magiccost; };

	void SetMagicpower(int magicpower_) { magicpower = magicpower_; };
	int GetMagicpower() { return magicpower; };
private:
	string name;
	int namelength;
	int maxhealth;
	int health;
	int maxmana;
	int mana;
	int defense;
	int damage;
	int level;
	int magiccost;
	int magicpower;
};
#endif
