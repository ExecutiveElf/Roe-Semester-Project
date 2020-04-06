#include <time.h>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include "player.h"
#include "skills.h"
#include "slime.h"
#include "bat.h"
#include "skeleton.h"
#include "monsters.h"

using namespace std;

void battle(player player);
skill skills[20];
void skillstats(skill skills[20]);

int main()
{
	player player;
	battle(player);
	return 0;
}

void battle(player player)
{
	bool run = false;
	skillstats(skills);
	srand((unsigned int)time(NULL));
	int i = rand() % 3; //Selects random monster.

	vector<monster> mons;

	slime* tempSlime;
	bat* tempBat;
	skeleton* tempSkeleton;

tempSlime = new slime;
mons.push_back(*tempSlime);

tempBat = new bat;
mons.push_back(*tempBat);

tempSkeleton = new skeleton;
mons.push_back(*tempSkeleton);

	cout << "An enemy " << mons[i].GetName() << " has appeared!\n_______________________________________\n";
	do {


		cout << "Player " << setw(8) << "HP: ";
		if (player.GetHealth() < 10)
			cout << " ";
		cout << player.GetHealth() << " / " << player.GetMaxhealth();
		cout << setw(10) << "MP: ";
		if (player.GetMana() < 10)
			cout << " ";
		cout << player.GetMana() << " / ";
		if (player.GetMaxmana() < 10)
			cout << " ";
		cout << player.GetMaxmana() << endl;


		cout << mons[i].GetName() << setw(15 - mons[i].GetNamelength()) << "HP: ";
		if (mons[i].GetHealth() < 10)
			cout << " ";
		cout << mons[i].GetHealth() << " / ";
		if (mons[i].GetMaxhealth() < 10)
			cout << " ";
		cout << mons[i].GetMaxhealth() << setw(10) << "MP: ";
		if (mons[i].GetMana() < 10)
			cout << " ";
			cout << mons[i].GetMana() << " / ";
		if (mons[i].GetMaxmana() < 10)
			cout << " ";
		cout << mons[i].GetMaxmana() << endl;


		cout << "_______________________________________\n1. Fight     2. Items\n3. Check     4. Run\n_______________________________________\n";
		int input;
		cin >> input;
		cout << "_______________________________________\n";
		int damage;
		switch (input)
		{
		case 1:
			for (int j = 0; j < 20; j++)
			{
				if (skills[j].available == true)
				{
					cout << j + 1 << ". ";
					if (skills[j].manacost < 10 && skills[j].manacost >= 0)
						cout << " ";
					cout << skills[j].manacost << " MP    " << skills[j].name << endl;
				}
			}
			cout << "______________________________________________" << endl;
			do {
				cin >> input;
				if (player.GetMana() < skills[input - 1].manacost)
					cout << "Not enough mana!\n";
			} while (player.GetMana() < skills[input - 1].manacost);

			damage = (player.GetDamage() * skills[input - 1].multiplier) + skills[input - 1].power - mons[i].GetDefense();
			player.SetMana(player.GetMana() - skills[input - 1].manacost);
			if (player.GetMana() > player.GetMaxmana())
				player.SetMana(player.GetMaxmana());
			system("CLS");
			if (skills[input - 1].multiplier != 0)
				cout << "You attacked the enemy " << mons[i].GetName() << " for " << damage << " damage.";
			if (skills[input - 1].manacost < 0)
				cout << "You restored " << skills[input - 1].manacost * -1 << " mana.";
			mons[i].SetHealth(mons[i].GetHealth() - damage);
			break;
		case 2:
			system("CLS");
			cout << "This feature is not yet implemented.";
			break;
		case 3:
			system("CLS");
			cout << mons[i].GetName() << "s have " << mons[i].GetMaxhealth() << " health, " << mons[i].GetMaxmana() << " mana, and " << mons[i].GetDefense() << " defense.";
			break;
		case 4:
			system("CLS");
			run = true;
		}
		if (mons[i].GetHealth() > 0 && run != true)
		{
			damage = mons[i].GetDamage() - player.GetDefense();
			player.SetHealth(player.GetHealth() - damage);
			cout << "\nEnemy " << mons[i].GetName() << " attacked you for " << damage << " damage.";
		}
		cout << "\n_______________________________________\n";
	} while (player.GetHealth() > 0 && mons[i].GetHealth() > 0 && run != true);
	if (player.GetHealth() <= 0)
		cout << "Game Over";
	if (mons[i].GetHealth() <= 0)
		cout << "You defeted the " << mons[i].GetName() << "!\nYou gained " << (mons[i].GetLevel() + 1 - player.GetLevel()) * 15 << " EXP.";
	if (run == true)
		cout << "You ran away!";
	cout << "\n_______________________________________\n";
}