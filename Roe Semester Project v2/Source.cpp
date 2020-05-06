/* Benjamin Roe
 C++ Fall 2019
 Due (May 6, 2020)
 Semester Project
*/

#include <time.h>
#include <iomanip>
#include <vector>
#include <stdlib.h>

#include "player.h"
#include "skills.h"
#include "items.h"

#include "monsters.h"
#include "slime.h"
#include "goldslime.h"
#include "bat.h"
#include "skeleton.h"
#include "cadet.h"
#include "zombie.h"
#include "ghoul.h"
#include "octomical.h"

#include "weapons.h"
#include "stick.h"
#include "club.h"

#include "armors.h"
#include "stinkyleather.h"
#include "leather.h"

#include "potions.h"
#include "healthpotion.h"
#include "manapotion.h"
#include "mixedpotion.h"

/*
We start out strong with a crap ton of included files for the sake of cleanliness.
Each Monster and Item has its own header and cpp.
I will not be commenting in any other files as they would all say the same things basically because they are just 
classes with get and set functions for their variables. Rather simple don't you think?
*/

using namespace std;

void menu(player& player, bool& game, int& sequence); /*This functionis at the core of the project.
													  It contains the main menu as well as the calls
													  for basically every other function.*/
void shop(player& player, int& input); //Opens the shop.
void battle(player& player, bool& game, int& input, int& sequence); //Starts a battle.
void heal(player& player, int& input); //Opens the heal menu.
void status(player& player); //Gives a bunch of information about the player.
void inventory(player& player, int& input); //Shows the player's inventory.

void levelup(player& player); //Runs after the battle function when certain requirements are met.
void itemset(); //Initializes all items when the program begins.

vector<weapon> weapons; //Orders all of the weapons and assigns them IDs. Could have been an array but I think its fine.
vector<armor> armors; //Same as the weapon vector except with armor.
vector<potion> potions; //3 for 3. Same as the other vectors, except with potions.
skill skills[20]; //Frankly, skills as a whole are underdeveloped admittedly.
void skillstats(skill skills[20]);

int main()
{
	player player;
	int sequence = 1; //SEQUENCE POSITION VALUE --- CHANGE TO "2" TO PUT GAME IN A POST-BOSS 1 STATE
	itemset(); //Initializes all of the items.
	bool game = true; //An absolutly classic line of code. Stays true until the player dies or beats the 2nd boss. 
	while (game == true)
	{
		menu(player, game, sequence); //The menu function is called here and is returned to after anything else concludes.
		if (sequence == 3) //Moves on if the game is beaten.
		{
			game = false;
			cout << "_______________________________________\n";
			cout << "Congrats! You beat the game!\nThe End";
			cout << "\n_______________________________________\n";
		}
	}
	return 0;
}

void itemset()
{
	//Weapons ---------------------------------------------------------------------------------------------
	weapon* tempWeapon; //None - Weapon ID: 0
	tempWeapon = new weapon;
	weapons.push_back(*tempWeapon);

	stick* tempStick; //Stick - Weapon ID: 1
	tempStick = new stick;
	weapons.push_back(*tempStick);

	club* tempClub; //Club - Weapon ID: 2
	tempClub = new club;
	weapons.push_back(*tempClub);



	//Armors ---------------------------------------------------------------------------------------------
	armor* tempArmor; //None - Armor ID: 0
	tempArmor = new armor;
	armors.push_back(*tempArmor);

	armor* tempStinkyleather; //Stinky Leather - Armor ID: 1
	tempStinkyleather = new stinkyleather;
	armors.push_back(*tempStinkyleather);

	armor* tempLeather; //Leather - Armor ID: 2
	tempLeather = new leather;
	armors.push_back(*tempLeather);



	//Potions ---------------------------------------------------------------------------------------------
	potion* tempPotion; //None - Potion ID: 0
	tempPotion = new potion;
	potions.push_back(*tempPotion);

	//Each Potion is created 3 times for the sake of ease on my part. Admittedly it is very clunky.

	potion* tempHealthpotionA; //Health Potion A - Potion ID: 1
	tempHealthpotionA = new healthpotion;
	potions.push_back(*tempHealthpotionA);

	potion* tempHealthpotionB; //Health Potion B - Potion ID: 2
	tempHealthpotionB = new healthpotion;
	potions.push_back(*tempHealthpotionB);

	potion* tempHealthpotionC; //Health Potion C - Potion ID: 3
	tempHealthpotionC = new healthpotion;
	potions.push_back(*tempHealthpotionC);


	potion* tempManapotionA; //Mana Potion A - Potion ID: 4
	tempManapotionA = new manapotion;
	potions.push_back(*tempManapotionA);

	potion* tempManapotionB; //Mana Potion B - Potion ID: 5
	tempManapotionB = new manapotion;
	potions.push_back(*tempManapotionB);

	potion* tempManapotionC; //Mana Potion C - Potion ID: 6
	tempManapotionC = new manapotion;
	potions.push_back(*tempManapotionC);


	potion* tempMixedpotionA; //Mixed Potion A - Potion ID: 4
	tempMixedpotionA = new mixedpotion;
	potions.push_back(*tempMixedpotionA);

	potion* tempMixedpotionB; //Mixed Potion B - Potion ID: 5
	tempMixedpotionB = new mixedpotion;
	potions.push_back(*tempMixedpotionB);

	potion* tempMixedpotionC; //Mixed Potion C - Potion ID: 6
	tempMixedpotionC = new mixedpotion;
	potions.push_back(*tempMixedpotionC);
}

void menu(player& player, bool& game, int& sequence) //Ahhh menu, home sweet home. Has a switch that calls the other functions.
{
	int input;
	cout << "_______________________________________\n";
	cout << "1: Shop     2: Heal\n3: Battle   4: Status\n5: Boss     6: Inventory";
	cout << "\n_______________________________________\n";
	cin >> input;
	system("CLS");
	switch (input)
	{
	case 1: //Runs the shop function.
		shop(player, input);
		break;
	case 2: //Runs the heal function.
		heal(player, input);
		break;
	case 3: //Runs the battle function followed by checking the player's XP and then deciding if a level up should occur..
		battle(player, game, input, sequence);
		if (player.GetExp() >= 100)
			levelup(player);
		break;
	case 4: //Runs the check function.
		status(player);
		break;
	case 5: /*Runs the battle function with the special case of "input = 5" which alters it in order to make a
			a boss encounter occur instead of a normal battle.*/
		battle(player, game, input, sequence);
		if (player.GetExp() >= 100)
			levelup(player);
		break;
	case 6: //Runs the inventory function.
		inventory(player, input);
		break;
	}
}



//Empty space helpesme distinguish were functions start and end.


void battle(player& player, bool& game, int& input, int& sequence)
{
	bool run = false; //Initializes run to false so that it can be altered later when the player flees.
	bool bossencounter = false; //Initializes to false but is changed if battle is called via input 5 rather than 3.
	skillstats(skills);
	vector<monster> mons; //Monster vector initialized here so that it is cleared out after each battle.
	int i;
	int j;

	//Pointers for each monster made so that they are there if needed.

	slime* tempSlime;
	goldslime* tempGoldSlime;
	bat* tempBat;
	skeleton* tempSkeleton;
	cadet* tempCadet;

	zombie* tempZombie;
	ghoul* tempGhoul;
	octomical* tempOctomical;

	if (input == 5) /*Detects if the battle function was called via an input of 5 rather than 3.
					If it is then the battle function is altered at this point so that a boss monster
					will appear.*/
	{
		switch (sequence)
		{
		case 1: //Calls the first boss if Sequenced to 1.
			tempCadet = new cadet;
			mons.push_back(*tempCadet);
		case 2: //Calls the second boss if Sequenced to 2.
			tempOctomical = new octomical;
			mons.push_back(*tempOctomical);
		}
		bossencounter = true; /*This is so that the fact that this is a boss encounter is remembered after
							  input is overwritten.*/
		i = 0; //This makes sure the monster vector does overflow due to only a single monster existing in it.
		cout << "Boss monster, " << mons[i].GetName() << " has appeared!\n_______________________________________\n";
	}
	else //Encounter table loaded as normal when not in a boss encounter.
	{
		srand((unsigned int)time(NULL));
		i = rand() % 3; //Selects random monster.

		switch (sequence) //Picks between two different encounter tables depending on the value of Sequence.
		{
		case 1: //After the appropriate case is chosen, monsters are placed into the vector.
			j = rand() % 5; //1 in 5 slimes will be a gold slime instead.
			if (j == 4)
			{
				tempGoldSlime = new goldslime;
				mons.push_back(*tempGoldSlime);
			}
			else
			{
				tempSlime = new slime;
				mons.push_back(*tempSlime);
			}
			tempBat = new bat;
			mons.push_back(*tempBat);
			tempSkeleton = new skeleton;
			mons.push_back(*tempSkeleton);
		case 2:
			tempSkeleton = new skeleton;
			mons.push_back(*tempSkeleton);

			tempZombie = new zombie;
			mons.push_back(*tempZombie);

			tempGhoul = new ghoul;
			mons.push_back(*tempGhoul);

		}
		//The random number (or 0 in the case of bosses) from earlier is used to select a monster from the vector.
		cout << "An enemy " << mons[i].GetName() << " has appeared!\n_______________________________________\n";
	}

	do { //The battle begins as all the apropriate data is displayed.
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
		cin >> input; //Player selects what action they would like to take.
		cout << "_______________________________________\n";
		int damage; //Makes damage calculation WAY easier by making it only need to happen once.
		switch (input)
		{
		case 1: //Shows the list of skill from which the player may choose to atack.
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
			do { //Ensures the player has enough mana to use their chosen skill.
				cin >> input;
				if (player.GetMana() < skills[input - 1].manacost)
					cout << "Not enough mana!\n";
			} while (player.GetMana() < skills[input - 1].manacost);

			//Uses several different factors to calculate the player's damage output.
			damage = ((player.GetDamage() + weapons[player.GetWeapon()].GetAttack()) * skills[input - 1].multiplier) + skills[input - 1].power - mons[i].GetDefense();
			player.SetMana(player.GetMana() - skills[input - 1].manacost); //Decreases mana by appropriate value.
			if (player.GetMana() > player.GetMaxmana())
				player.SetMana(player.GetMaxmana());
			system("CLS");
			if (skills[input - 1].multiplier != 0) //Displays results of attack to the screen.
				cout << "You attacked the enemy " << mons[i].GetName() << " for " << damage << " damage.";
			if (skills[input - 1].manacost < 0)
				cout << "You restored " << skills[input - 1].manacost * -1 << " mana.";
			mons[i].SetHealth(mons[i].GetHealth() - damage);
			break;
		case 2: //Lists the player's potions.
			cout << "0: Do nothing.\n"; /*Unfortunatly I didn't implement a way to back up within a battle and
										the need for a do nothing button within the items menu is a
										consiquence of that.*/
			for (int i = 1; i <= potions[0].GetVectorsize(); i++)
			{
				if (potions[i].GetPlayerhas() == true)
					cout << i << ": " << potions[i].GetName() << endl;
			}
			cin >> input;
			system("CLS");
			if (input != 0) //Displays results of potion drunk.
			{
				cout << "You drank the " << potions[input].GetName() << ".\n";
				if (potions[input].GetHPheal() > 0)
				{
					cout << "You recovered " << potions[input].GetHPheal() << " health.\n";
					player.SetHealth(player.GetMaxhealth() + potions[input].GetHPheal());
					if (player.GetHealth() > player.GetMaxhealth())
						player.SetHealth(player.GetMaxhealth());
				}
				if (potions[input].GetMPheal() > 0)
				{
					cout << "You recovered " << potions[input].GetMPheal() << " mana.\n";
					player.SetMana(player.GetMaxmana() + potions[input].GetMPheal());
					if (player.GetMana() > player.GetMaxmana())
						player.SetMana(player.GetMaxmana());
				}
				potions[input].SetPlayerhas(false); //Removes the consumed potion from the player's inventory.
			}
			break;
		case 3: //Displays some information about the current enemy monster.
			system("CLS");
			cout << mons[i].GetName() << "s have " << mons[i].GetMaxhealth() << " health, " << mons[i].GetDamage() << " attack, and " << mons[i].GetDefense() << " defense.";
			break;
		case 4: //Flees from battle.
			system("CLS");
			run = true;
		}
		int magic = 0; //Simplifies keeping track of the monster's magical attacks.
		if (mons[i].GetHealth() > 0 && run != true)
		{ //Only does the monster's attack if they are alive and you haven't fled.
			if (mons[i].GetMagicpower() != 0 && mons[i].GetMagiccost() <= mons[i].GetMana())
			{//Only does magic calculation if monster is actually capable of magic.
				srand((unsigned int)time(NULL));
				int k = rand() % 3; //All monsters have a 1 in 3 chance of using magic when possible.
				switch (k)
				{
				default:
					magic = 0; 
					break;
				case 2: 
					magic = mons[i].GetMagicpower(); //Lowers monster's mana when magic is used.
					mons[i].SetMana(mons[i].GetMana() - mons[i].GetMagiccost()); 
				}
			}
			//Damage calculation for the monster's attack based on various values.
			damage = mons[i].GetDamage() + magic - (player.GetDefense() + armors[player.GetArmor()].GetDefense());
			if (damage < 0) //Ensures negative damage does not occur.
				damage = 0;
			player.SetHealth(player.GetHealth() - damage); //Lowers player's HP appropriatly.
			cout << "\nEnemy " << mons[i].GetName() << " attacked you for " << damage << " damage.";
			//Displays result to the screen.
		}
		cout << "\n_______________________________________\n";
	} while (player.GetHealth() > 0 && mons[i].GetHealth() > 0 && run != true);
	if (player.GetHealth() <= 0) //Checks if player is dead.
	{
		cout << "Game Over";
		game = false;
	}
	if (mons[i].GetHealth() <= 0) //Checks if monster is dead.
	{//Grants EXP and gold dependent on the monster's level.
		int expgain = (mons[i].GetLevel() + 1 - player.GetLevel()) * 15;
		if (expgain > 100)
			expgain = 100;
		if (expgain < 1)
		{
			if (mons[i].GetLevel() + 1 == player.GetLevel())
				expgain = 5;
			else
				expgain = 1;
		}
		int goldgain = mons[i].GetLevel() * 3;
		cout << "You defeted the " << mons[i].GetName() << "!\nYou gained " << expgain << " EXP";
		cout << " and " << goldgain << " gold!";
		player.SetExp(player.GetExp() + expgain);
		player.SetGold(player.GetGold() + goldgain);
		if (bossencounter == true)
			sequence++;
	}
	if (run == true) //Checks if the player chose to flee.
		cout << "You ran away!";
	cout << "\n_______________________________________\n";
}






void levelup(player& player) //Runs when player gets to 100 exp.
{
	cout << "_______________________________________\nYou leveled up!\n";
	player.SetExp(player.GetExp() - 100); //Decreases exp by 100.
	player.SetLevel(player.GetLevel() + 1); //Increases level.
	switch (player.GetLevel() % 3) //Increases different stats depending on the player's new level.
	{
	case 0: 
		player.SetMaxmana(player.GetMaxmana() + 5);
		cout << "Your mana has increased by 5!\n";
		break;
	case 1: 
		player.SetDefense(player.GetDefense() + 1);
		cout << "Your defense has increased by 1!\n";
		break;
	case 2: 
		cout << "Your health has increased by 5!\n";
		player.SetMaxhealth(player.GetMaxhealth() + 5);
	}
	if ((player.GetLevel() - 1) % 2 == 0)
	{
		cout << "Your attack has increased by 1!\n";
		player.SetDamage(player.GetDamage() + 1);
	}
	player.SetHealth(player.GetMaxhealth());
	player.SetMana(player.GetMaxmana());
	cout << "_______________________________________\n";
}





void shop(player& player, int& input) //Please excuse my language.... but fuck this function lol.
{ //Contains both the buying and selling aspects of the shop.
	int j = false;
	int input2;
	int input3;
	//Opening menu of the shop.
	cout << "_______________________________________\n";
	cout << "1: Buy      2: Sell\n3: Back";
	cout << "\n_______________________________________\n";
	cin >> input;
	cout << "_______________________________________\n";
	switch (input) /*Takes you to either buy or sell menus. Screen is cleared less often 
				   here to avoid confusion for the player about what menu they are in.*/
	{
	case 1: /*Section that manages purchasing from the shop. Frankly, aa a whole the shop is rather clunky.
			I'm proud of the result that appears on the screen when run but not of the code itself here.*/
		cout << "1: Weapons   2: Armor\n3: Potions\n_______________________________________\n";
		cin >> input3;
		cout << "_______________________________________\n0: Go Back\n";
		switch (input3)
		{




			// BUYING ITEMS ----------------------------------------------------------------------------
		case 1: // WEAPONS
			for (int i = 1; i <= weapons[0].GetVectorsize(); i++)
			{
				if (weapons[i].GetPlayerhas() != true) //Displays all weapons the player doesn't have.
					cout << i << ": " << weapons[i].GetName() << setw(15 - weapons[i].GetNamelength()) << weapons[i].GetBuyvalue() << " gold\n";
			}
			break;
		case 2: //ARMORS
			for (int i = 1; i <= armors[0].GetVectorsize(); i++)
			{
				if (armors[i].GetPlayerhas() != true) //Displays all armors the player doesn't have.
					cout << i << ": " << armors[i].GetName() << setw(15 - armors[i].GetNamelength()) << armors[i].GetBuyvalue() << " gold\n";
			}
			break;
		case 3: //POTIONS
			for (int i = 1; i <= potions[0].GetVectorsize(); i++)
			{
				if (potions[i].GetPlayerhas() != true) //Displays all potions the player doesn't have.
					cout << i << ": " << potions[i].GetName() << setw(16 - potions[i].GetNamelength()) << potions[i].GetBuyvalue() << " gold\n";
			}
			break;
		}
		cout << "\n_______________________________________\n";
		cin >> input;
		system("CLS");
		cout << "_______________________________________\n";
		if (input == 0)
		{
			break;
		}
		switch (input3) /*This switch statement exists for the sake of error handling. It prevents vector
						overflows or purchasing of items already owned.*/
		{
		case 1:
			if (input > 2 || input < 0 || weapons[input].GetPlayerhas() != false)
			{
				system("CLS");
				cout << "Invalid Input\n";
				j = true;
			}
			break;
		case 2:
			if (input > 2 || input < 0 || armors[input].GetPlayerhas() != false)
			{
				system("CLS");
				cout << "Invalid Input\n";
				j = true;
			}
			break;
		case 3:
			if (input > 9 || input < 0 || potions[input].GetPlayerhas() != false)
			{
				system("CLS");
				cout << "Invalid Input\n";
				j = true;
			}
			break;
		}
		if (j == true)
			break;
		switch (input3) /*Basically what happens here is that the player confirms their purchase and their gold
						is deducted and they recieve the item. There are 3 cases, one for each type of item.*/
		{
		case 1: //WEAPONS
			cout << "Are you sure you want to buy the\n" << weapons[input].GetName() << " for " << weapons[input].GetBuyvalue() << " gold?\n";
			cout << "1: Yes     2: No\n_______________________________________\n";
			cin >> input2;
			if (input2 == 1)
			{
				if (player.GetGold() < weapons[input].GetBuyvalue())
				{
					system("CLS");
					cout << "You don't have enough gold!\n";
					break;
				}
				player.SetGold(player.GetGold() - weapons[input].GetBuyvalue());
				weapons[input].SetPlayerhas(true);
				system("CLS");
				cout << "You spent " << weapons[input].GetBuyvalue() << " gold to obtain the " << weapons[input].GetName() << ".\n_______________________________________\n";
			}
			else
				system("CLS");
			break;
		case 2: //ARMORS
			cout << "Are you sure you want to buy the\n" << armors[input].GetName() << " for " << armors[input].GetBuyvalue() << " gold?\n";
			cout << "1: Yes     2: No\n_______________________________________\n";
			cin >> input2;
			if (input2 == 1)
			{
				if (player.GetGold() < armors[input].GetBuyvalue())
				{
					system("CLS");
					cout << "You don't have enough gold!\n";
					break;
				}
				player.SetGold(player.GetGold() - armors[input].GetBuyvalue());
				armors[input].SetPlayerhas(true);
				system("CLS");
				cout << "You spent " << armors[input].GetBuyvalue() << " gold to obtain the " << armors[input].GetName() << ".\n";
			}
			else
				system("CLS");
		case 3: //POTIONS
			cout << "Are you sure you want to buy the\n" << potions[input].GetName() << " for " << potions[input].GetBuyvalue() << " gold?\n";
			cout << "1: Yes     2: No\n_______________________________________\n";
			cin >> input2;
			if (input2 == 1)
			{
				if (player.GetGold() < potions[input].GetBuyvalue())
				{
					system("CLS");
					cout << "You don't have enough gold!\n";
					break;
				}
				player.SetGold(player.GetGold() - potions[input].GetBuyvalue());
				potions[input].SetPlayerhas(true);
				system("CLS");
				cout << "You spent " << potions[input].GetBuyvalue() << " gold to obtain the " << potions[input].GetName() << ".\n";
			}
			else
				system("CLS");
		}
		break;






	case 2: // SELLING ITEMS ----------------------------------------------------------------------------
		/*There really isn't much to be said here not stated in the buy part of this function.
		It is largely the same except everywhere it says buy is now sell. Hence why I agreed while
		I was presenting that this would probably be a good class. Unfortunatly thats not how I did it
		and I'm not about ot redo it.*/
		cout << "1: Weapons   2: Armor\n3: Potions\n_______________________________________\n";
		cin >> input3;
		cout << "_______________________________________\n0: Go Back\n";
		switch (input3)
		{
		case 1: //WEAPONS
			for (int i = 1; i <= weapons[0].GetVectorsize(); i++)
			{
				if (weapons[i].GetPlayerhas() == true)
					cout << i << ": " << weapons[i].GetName() << setw(15 - weapons[i].GetNamelength()) << weapons[i].GetSellvalue() << " gold\n";
			}
			break;
		case 2: //ARMORS
			for (int i = 1; i <= armors[0].GetVectorsize(); i++)
			{
				if (armors[i].GetPlayerhas() == true)
					cout << i << ": " << armors[i].GetName() << setw(15 - armors[i].GetNamelength()) << armors[i].GetSellvalue() << " gold\n";
			}
			break;
		case 3: //POTIONS
			for (int i = 1; i <= potions[0].GetVectorsize(); i++)
			{
				if (potions[i].GetPlayerhas() == true)
					cout << i << ": " << potions[i].GetName() << setw(15 - potions[i].GetNamelength()) << potions[i].GetSellvalue() << " gold\n";
			}
			break;
		}
		cout << "\n_______________________________________\n";
		cin >> input;
		system("CLS");
		cout << "_______________________________________\n";
		if (input == 0)
		{
			break;
		}
		switch (input3) //Another error handler thats mostly to prevent overflowing of vectors.
		{
		case 1:
			if (input > 2 || input < 0 || weapons[input].GetPlayerhas() != true)
			{
				system("CLS");
				cout << "Invalid Input\n";
				j = true;
			}
			break;
		case 2:
			if (input > 2 || input < 0 || armors[input].GetPlayerhas() != true)
			{
				system("CLS");
				cout << "Invalid Input\n";
				j = true;
			}
			break;
		case 3:
			if (input > 9 || input < 0 || potions[input].GetPlayerhas() != true)
			{
				system("CLS");
				cout << "Invalid Input\n";
				j = true;
			}
			break;
		}
		if (j == true)
			break;
		switch (input3)
		{//Confirms a sale and adds gold to the player. The item in question is removed from the inventory.
			//Just like the buy function basically.
		case 1:
			cout << "Are you sure you want to sell your\n" << weapons[input].GetName() << " for " << weapons[input].GetSellvalue() << " gold?\n";
			cout << "1: Yes     2: No\n_______________________________________\n";
			cin >> input2;
			if (input2 == 1)
			{
				if (player.GetWeapon() == input)
				{
					player.SetWeapon(0);
				}
				player.SetGold(player.GetGold() + weapons[input].GetSellvalue());
				weapons[input].SetPlayerhas(false);
				system("CLS");
				cout << "You gained " << weapons[input].GetSellvalue() << " gold.\n";
			}
			else
				system("CLS");
			break;
		case 2:
			cout << "Are you sure you want to sell your\n" << armors[input].GetName() << " for " << armors[input].GetSellvalue() << " gold?\n";
			cout << "1: Yes     2: No\n_______________________________________\n";
			cin >> input2;
			if (input2 == 1)
			{
				if (player.GetArmor() == input)
				{
					player.SetArmor(0);
				}
				player.SetGold(player.GetGold() + armors[input].GetSellvalue());
				armors[input].SetPlayerhas(false);
				system("CLS");
				cout << "You gained " << armors[input].GetSellvalue() << " gold.\n";
			}
			else
				system("CLS");
		case 3:
			cout << "Are you sure you want to sell your\n" << potions[input].GetName() << " for " << potions[input].GetSellvalue() << " gold?\n";
			cout << "1: Yes     2: No\n_______________________________________\n";
			cin >> input2;
			if (input2 == 1)
			{
				if (player.GetArmor() == input)
				{
					player.SetArmor(0);
				}
				player.SetGold(player.GetGold() + potions[input].GetSellvalue());
				potions[input].SetPlayerhas(false);
				system("CLS");
				cout << "You gained " << potions[input].GetSellvalue() << " gold.\n";
			}
			else
				system("CLS");
		}
		break;
	default:
		system("CLS");
		break;
	}
} //Oh thank god the function is over. I hate this one so much.



void heal(player& player, int& input)
{//Now for a nice easy function.
	int cost;
	cost = (player.GetMaxhealth() - player.GetHealth()) + (player.GetMaxmana() - player.GetMana());
	//Finds how much HP and MP the player is missing and sums them. The sum is the price of the heal.
	cout << "_______________________________________\n";
	cout << "This will cost " << cost; //Displays and requests confirmation.
	cout << " Gold.\nAre you sure?\n1: Yes      2: No";
	cout << "\n_______________________________________\n";
	cin >> input;
	system("CLS");
	if (input == 1)
	{//Checks if the player has enough gold.
		if (player.GetGold() < cost)
		{
			cout << "You don't have enough gold.\n";
		}
		else
		{
			player.SetGold(player.GetGold() - cost); //Deducts the gold from the player.
			player.SetHealth(player.GetMaxhealth()); //Sets health and mana to their maximum values.
			player.SetMana(player.GetMaxmana());
			cout << "You have been fully healed.\n";
		}
	}
}


void status(player& player)
{//Very simple. Just displays all of the values stored in player.cpp for the sake of the player's knowledge.
	cout << "Lvl: " << player.GetLevel() << endl;
	cout << "Exp: " << player.GetExp() << " / 100" << endl;
	cout << "Gold: " << player.GetGold() << endl;
	cout << "HP: " << player.GetHealth() << " / " << player.GetMaxhealth() << endl;
	cout << "MP: " << player.GetMana() << " / " << player.GetMaxmana() << endl;
	cout << "Atk: " << player.GetDamage() + weapons[player.GetWeapon()].GetAttack() << endl;
	cout << "Def: " << player.GetDefense() + armors[player.GetArmor()].GetDefense() << endl;
	cout << "Wep: " << weapons[player.GetWeapon()].GetName() << " (+" << weapons[player.GetWeapon()].GetAttack() << ")" << endl;
	cout << "Arm: " << armors[player.GetArmor()].GetName() << " (+" << armors[player.GetArmor()].GetDefense() << ")" << endl;
}

void inventory(player& player, int& input)
{//This function was actually super fun to make and was a nice change of pace as I made it right after finishing shop.
	//Allows the player to view and manage their items.
	int input2;
	cout << "_______________________________________\n"; //Displays curent equipment.
	cout << "Current Weapon: " << weapons[player.GetWeapon()].GetName() << setw(15 - weapons[player.GetWeapon()].GetNamelength()) << " (+ " << weapons[player.GetWeapon()].GetAttack() << " Atk)\n";
	cout << "Current Armor:  " << armors[player.GetArmor()].GetName() << setw(15 - armors[player.GetArmor()].GetNamelength()) << " (+ " << armors[player.GetArmor()].GetDefense() << " Def)";
	cout << "\n_______________________________________\n";
	cout << "0: Back          1: Equip Weapon\n2: Equip Armor   3: List Potions";
	cout << "\n_______________________________________\n"; //Displays the inventory menu.
	cin >> input;
	cout << "_______________________________________\n";
	switch (input) //3 cases like in shop except more pleasent. 
	{
	case 0: //Goes back to menu.
		system("CLS");
		break;
	case 1: //WEAPONS - Displays weapons owned.
		cout << "0: Cancel\n";
		for (int i = 1; i <= weapons[0].GetVectorsize(); i++)
		{
			if (weapons[i].GetPlayerhas() == true)
				cout << i << ": " << weapons[i].GetName() << setw(15 - weapons[i].GetNamelength()) << " (+ " << weapons[i].GetAttack() << " Atk)\n";
		}
		break;
	case 2: //ARMORS - Displays armors owned.
		cout << "0: Cancel\n";
		for (int i = 1; i <= armors[0].GetVectorsize(); i++)
		{
			if (armors[i].GetPlayerhas() == true)
				cout << i << ": " << armors[i].GetName() << setw(15 - armors[i].GetNamelength()) << " (+ " << armors[i].GetDefense() << " Def)\n";
			break;
		}
	case 3: //POTIONS - Displays potions owned.
		cout << "0: Back\n";
		for (int i = 1; i <= potions[0].GetVectorsize(); i++)
		{
			if (potions[i].GetPlayerhas() == true)
				cout << potions[i].GetName() << endl;
		}
	}
	if (input != 0) //Skipped if the user input 0 so that they can return to menu.
	{
		cout << "_______________________________________\n";
		cin >> input2; //Allows player to select which item they would like to equip
		system("CLS");
		if (input2 != 0) /*Allows the player to back out without needing to select an item
						 and when potions are displayed.*/
		{
			switch (input)
			{
			case 1: //Equips selected weapon
				if (input2 <= 2 && input2 > -1 && weapons[input2].GetPlayerhas() == true)
				{
					player.SetWeapon(input2);
					cout << "You equipped the " << weapons[input2].GetName() << ".\n";
				}
				else
					cout << "Invalid Input\n";
				break;
			case 2: //Equips selected armor.
				if (input2 <= 2 && input2 > -1 && armors[input2].GetPlayerhas() == true)
				{
					player.SetArmor(input2);
					cout << "You equipped the " << armors[input2].GetName() << ".\n";
				}
				else
					cout << "Invalid Input\n";
			}
		}
	}

}