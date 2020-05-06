#ifndef player_h
#define player_h

#include <iostream>
using namespace std;

class player
{
public:
	player();
	~player();

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

	void SetExp(int exp_) { exp = exp_; };
	int GetExp() { return exp; };

	void SetGold(int gold_) { gold = gold_; };
	int GetGold() { return gold; };

	void SetWeapon(int weapon_) { weapon = weapon_; };
	int GetWeapon() { return weapon; };

	void SetArmor(int armor_) { armor = armor_; };
	int GetArmor() { return armor; };

private:
	int maxhealth;
	int health;
	int maxmana;
	int mana;

	int defense;
	int damage;
	int level;
	int exp;
	int gold;

	int weapon;
	int armor;
};
#endif
