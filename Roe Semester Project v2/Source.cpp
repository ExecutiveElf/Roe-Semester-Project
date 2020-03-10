#include "monsters.h"
#include "player.h"
#include "skills.h"
#include <iomanip>
#include <time.h>

void monsterstats(monster mon[100]);
void skillstats(skill skills[20]);
void playerstats(player you[1]);

int main()
{
	monster mon[100];
	skill skills[20];
	player you[1];
	monsterstats(mon);
	skillstats(skills);
	playerstats(you);


	srand((unsigned int)time(NULL));
	int i = rand() % 100 + 1; //Selects random monster.
	if (i <= 45)
		i = 0;
	else if (i <= 80)
		i = 1;
	else
		i = 2;


	int cursor;
	//Beginning of Combat
	mon[i].health = mon[i].maxhealth;
	cout << "An enemy " << mon[i].name << " has appeared!" << endl;
	do {
		cout << "______________________________________________" << endl;
		cout << "Player" << setw(9) << "HP: " << you[0].health << "    MP: " << you[0].mana;
		if (you[0].health < 10)
			cout << " ";
		if (you[0].mana < 10)
			cout << " ";
		cout << "   Lvl: " << you[0].level << endl;
		cout << mon[i].name << setw(15 - mon[i].namelength) << "HP: " << mon[i].health;
		if (mon[i].health < 10)
			cout << " ";
		cout << "    MP: " << mon[i].mana << endl;
		cout << "______________________________________________" << endl;
		cout << "1. Fight      2. Items\n3. Summary    4. Flee\n";
		cout << "______________________________________________" << endl;
		cin >> cursor;
		cout << "______________________________________________" << endl;

		if (cursor == 1)
		{

			for (int j = 0; j < 20; j++)
			{
				if (skills[j].available == true)
				{
					cout << j + 1 << ". " << skills[j].manacost << " MP    " << skills[j].name << endl;
				}
			}
			cout << "______________________________________________" << endl;
			do {
				cin >> cursor;
				if (you[0].mana < skills[cursor - 1].manacost)
					cout << "Not enough mana!\n";
			} while (you[0].mana < skills[cursor - 1].manacost);
			cout << "______________________________________________" << endl;
			cout << "You hit the enemy " << mon[i].name << " for ";
			cout << ((you[0].damage + skills[cursor - 1].power) * skills[cursor - 1].multiplier) << " damage!\n";
			mon[i].health = mon[i].health - ((you[0].damage + skills[cursor - 1].power) * skills[cursor - 1].multiplier);
			you[0].mana = you[0].mana - skills[cursor - 1].manacost;
			if (mon[i].health > 0)
			{
				cout << "Enemy " << mon[i].name << " attacks you for " << mon[i].damage << " damage!\n";
				you[0].health = you[0].health - mon[i].damage;
			}
		}
	} while (mon[i].health > 0 && you[0].health > 0);
	if (you[0].health <= 0)
		cout << "Game Over\n";
	if (mon[i].health <= 0)
	{
		cout << "You defeated the enemy " << mon[i].name << " and gained ";
		cout << 15 * (mon[i].level - (you[0].level - 1)) << " experience points!\n";
	}
	//End of Combat
	return 0;
}