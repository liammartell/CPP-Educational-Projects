/*This code simulates a text based adventure game. It was written by Liam Martell, Reanna Laurel, Yu Matsuzawa
Zach Krempasky, Isaac Long, Sydney Eggleton, and Kyle Koontz*/

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>

using namespace std;

//class room denotes each room of the game.
class Room
{
public:
	Room();
	//returns a random integer value to a designated item (food, weapon, etc)
	int hasItem(int difficulty);
	//allows us to access the private bool variable outside the class
	bool hasKeyItem();
	//changes the private bool variable
	void changeHasKeyItem(bool hasKeyItem);
private:
	//the bool value for whether the room has a key or not
	bool m_hasKeyItem = false;
};

Room::Room() {};

/**
chageHasKeyItem function changes the private variable for the current room
@param hasKeyItem -- the bool value we want to change to
*/
void Room::changeHasKeyItem(bool hasKeyItem)
{
	//sets the private bool to the bool passed into the function
	m_hasKeyItem = hasKeyItem;
}

/**
hasKeyItem function returns the private bool variable to use elsewhere
*/
bool Room::hasKeyItem()
{
	return m_hasKeyItem;
}

/**
hasItem function generates a random number for there being food in the current room
@param difficulty -- the increasing difficulty of the chance to get food
@return -- returns an int to evalueate whether or not there is food
*/
int Room::hasItem(int difficulty)
{
	//random number
	int itemNum = rand() % difficulty;
	return itemNum;
}

//the Player class contains hunger functions for the players hunger
class Player {
public:
	Player();
	// keeps track of hunger 
	void hungerStats();
	// Warns user if hunger gets too low
	void hungerWarning();
	// Adds food to hunger bar depending on item value
	void hungerEat(int i);
	// Will see if the player has starved to death and if so will end the game.
	bool hungerStarve();

private:
	//This is the number of health points the player has
	int hunger = 13;
	int itemNum;
};

Player::Player() {};

void Player::hungerStats() {

	//tests to see if the current health status is greater than zero
	if (hunger > 0) {
		//if it is greater than zero then subtract one
		hunger = hunger - 1;
		//ouputs message to let player know their current health
		cout << "\n	Hunger: " << hunger << endl;
	}
}

void Player::hungerWarning() {
	//warns user for varying levels of hunger
	if (hunger < 5 && hunger > 3) { cout << "\n	You should probably eat something soon" << endl; }
	if (hunger < 3 && hunger >= 1) { cout << "\n	You should eat something" << endl; }
	if (hunger < 1) { cout << "\n	Next move you make is game over :)" << endl; }

}

void Player::hungerEat(int i) {
	//for small food
	if (i == 1) {
		hunger++;
		if (hunger > 12) { hunger = 12; }
		cout << "	You found a little bit of food! Your hunger is now: " << hunger << endl << endl;
	}
	//for medium food
	if (i == 2) {
		hunger += 2;
		if (hunger > 12) { hunger = 12; }
		cout << "	You found a decent amount of food! Your hunger is now: " << hunger << endl << endl;
	}
	//for large food
	if (i == 3) {
		hunger += 3;
		if (hunger > 12) { hunger = 12; }
		cout << "	You found a lot of food! Your hunger is now: " << hunger << endl << endl;
	}

}

bool Player::hungerStarve() {
	if (hunger < 1) {
		return true;
	}
	return false;
}

//FUNCTION PROTOTYPES
void setUpMap(Room map[3][3]);
void displayDescription(int row, int column);
void placeKeys(Room map[3][3]);
int riddles(vector<int> inventory);

int main()
{
	cout << "===============================================================================\n";
	cout << "			Welcome to the forest advencture game!						\n";
	cout << " You are to navigate the landscape and find keys  while learning how to survive\n";
	cout << "		Use the key words, Up, Down, Left, and Right to move\n";
	cout << "Keys are hidden behind riddles. You might need to revisit rooms to find keys as\n";
	cout << "			more keys reveal themselves after you find one.\n";
	cout << "				    Have Fun!\n";
	cout << "===============================================================================\n\n\n";




	//INITIAL VARIABLES
	//time seed
	srand(time(0));
	//class objects
	Room location;
	Room map[3][3];
	Player main;

	//the action the player inputs
	string action;
	//the number of food and the number for the key
	int itemNum, keyNum;
	//starting difficulty
	int difficulty = 6;
	//inventory vector. Only contains keys
	vector<int> inventory;

	//initializes the map
	setUpMap(map);

	//the array row
	int row = 2;
	//the array column
	int column = 0;
	//copies room to a new object
	location = map[row][column];
	//cout << location << endl;
	displayDescription(row, column);

	//places keys in random rooms
	placeKeys(map);

	//while an action is being inputted
	while (cin >> action)
	{
		int turns = 0;
		//for the direction inputs
		if (action == "up")
		{
			row--;
		}
		else if (action == "down")
		{
			row++;
		}
		else if (action == "left")
		{
			column--;
		}
		else if (action == "right")
		{
			column++;
		}
		else
		{
			cout << "\nUnknown Direction\n";
		}
		//for going out of bounds
		if (row < 0)
		{
			cout << "\nYou Cannot go there" << endl;
			row++;
		}
		else if (column < 0)
		{
			cout << "\nYou cannot go there" << endl;
			column++;
		}
		else if (row > 2)
		{
			cout << "\nYou Cannot go there" << endl;
			row--;
		}
		else if (column > 2)
		{
			cout << "\nYou Cannot go there" << endl;
			column--;
		}
		else
		{
			//if the player starves
			if (main.hungerStarve())
			{
				cout << "\nYou starved to death. Game Over \n" << endl;
				return 0;
			}
			else
			{
				//win condition (make it to the tower with 3 keys)
				if ((row == 0 && column == 2) && inventory.size() == 3)
				{
					cout << "\nYou made it to the cell tower with all three keys! You unlock the devices and are able to send \n";
					cout << "out your message. You are going to survive!\n";
					cout << "YOU WIN" << endl;
					return 0;
				}

				//displays the current hunger level
				main.hungerStats();

				//gives a warning if close to death
				main.hungerWarning();

				//sets the current room to a location room to copy information
				location = map[row][column];

				//does the current room have a key?
				bool hasKey = location.hasKeyItem();

				//returns the type of food in the room, if any
				itemNum = location.hasItem(difficulty);

				//eats the food
				main.hungerEat(itemNum);

				//couts the room description
				displayDescription(row, column);

				//if the current room has a key
				if (hasKey == true)
				{
					//do the riddles and return a number 
					keyNum = riddles(inventory);
					//length of the vector = number of keys
					inventory.push_back(keyNum);
				}
				//increases the difficulty for finding food
				difficulty += 1;

			}
		}

		//if they want to stop the game
		if (action == "stop")
		{
			return 0;
		}
	}

}

/**
setUpMap function declares all the objects and initializes the map with them
@param map -- the array of rooms AKA the map of the game
*/
void setUpMap(Room map[3][3])
{
	Room start;
	Room eastForest;
	Room northForest;
	Room house;
	Room store;
	Room theater;
	Room gasStation;
	Room forestExit;
	Room tower;

	map[0][0] = gasStation;
	map[0][1] = forestExit;
	map[0][2] = tower;
	map[1][0] = northForest;
	map[1][1] = house;
	map[1][2] = theater;
	map[2][0] = start;
	map[2][1] = eastForest;
	map[2][2] = store;
}


/**
displayDescription function reads the current room and displays the description for that room from a file
*THERE IS A BUG IN THE FILE READING. ONLY TWO FILES WORK. THE REST ARE COUTS
@param row -- the current row index
@param column -- the current column index
*/
void displayDescription(int row, int column)
{
	//string for putting the file text into
	string line;
	//vector containing all file text
	vector<string> description;

	//code is the same for each room
	if (row == 0 && column == 0)
	{
		//stream set for reading the specified file
		ifstream text("gasSation.txt");
		text.open("gasStation.txt");
		if (text.fail())
		{
			cout << "ERROR" << endl;
		}
		else
		{
			//puts the text in a line until a delimiter is read
			while (getline(text, line))
			{
				//puts the string into the vector
				description.push_back(line);
			}


			for (int i = 0; i < description.size(); i++)
			{
				//reads out the entire vector of strings
				cout << description[i];
			}
			cout << endl;
		}
		text.close();
	}
	else if (row == 0 && column == 1)
	{
		ifstream text("forestExit.txt");
		text.open("forestExit.txt");
		if (text.fail())
		{
			cout << "\nThe trees finally start to thin. You exit the forest and are at the base of a very large hill. Of which, at the top sits the signal\n tower that you hope can send an S.O.S.message.There is nothing above you, below you is the abandoned house, \nto your left is the gas station, and to your right is the tower." << endl;
		}
		else
		{
			while (getline(text, line))
			{
				description.push_back(line);
			}

			for (int i = 0; i < description.size(); i++)
			{
				cout << description[i];
			}
			cout << endl;
		}
		text.close();
	}
	else if (row == 0 && column == 2)
	{
		ifstream text("tower.txt");
		text.open("tower.txt");
		if (text.fail())
		{
			cout << "You finally arrive at the signal tower. It seems to still have power as you can see light through the windows. You enter the tower and  make your way to a room that seems like it \nwould be able to send your message.However, there is a three lock system in place! You must find all three keys before you can broadcast an S.O.S.message!" << endl;
		}
		else
		{
			while (getline(text, line))
			{
				description.push_back(line);
			}


			for (int i = 0; i < description.size(); i++)
			{
				cout << description[i];
			}
			cout << endl;
		}
		text.close();

	}
	else if (row == 1 && column == 0)
	{
		ifstream text("northForest.txt");
		text.open("northForest.txt");
		if (text.fail())
		{
			cout << "You are now in the Northern entrance to the forest. There is an air of whimsy about the trees and plant life here. The \ntrees smell of cedar and some of the fungus is giving off a faint glow. \nBelow you is the cliff you awoke on, to the left is nothing but endless forest, to the right is a house, and above you \nis a gas station." << endl;
		}
		else
		{
			while (getline(text, line))
			{
				description.push_back(line);
			}


			for (int i = 0; i < description.size(); i++)
			{
				cout << description[i];
			}
			cout << endl;
		}
		text.close();
	}
	else if (row == 1 && column == 1)
	{
		ifstream text("house.txt");
		//text.open("house.txt");
		if (text.fail())
		{
			cout << "ERROR" << endl;
		}
		else
		{
			while (getline(text, line))
			{
				description.push_back(line);
			}


			for (int i = 0; i < description.size(); i++)
			{
				cout << description[i];
			}
			cout << endl;
		}
		text.close();

	}
	else if (row == 1 && column == 2)
	{
		ifstream text("theater.txt");
		text.open("theater.txt");
		if (text.fail())
		{
			cout << "You enter an abandoned theater. The seats are dusty and the screen is in shreds. Above you is the tower, to your left is an abandoned house, and below you is the abandoned store." << endl;
		}
		else
		{
			while (getline(text, line))
			{
				description.push_back(line);
			}


			for (int i = 0; i < description.size(); i++)
			{
				cout << description[i];
			}
			cout << endl;
		}
		text.close();

	}
	else if (row == 2 && column == 0)
	{
		ifstream text("start.txt");
		text.open("start.txt");
		if (text.fail())
		{
			cout << "You wake. Behind you is at least a 100 foot drop into a rocky, choppy ocean. In front of you seems a vast forest. \nThe forest seems to go on forever.You see some areas where the trees thin, and far off in the distance is a signal \ntower. \nYour only options seem to be to go 'up' into the forest to the North, or 'right' to the forest to the East." << endl;
		}
		else
		{
			while (getline(text, line))
			{
				description.push_back(line);
			}


			for (int i = 0; i < description.size(); i++)
			{
				cout << description[i];
			}
			cout << endl;
		}
		text.close();
	}
	else if (row == 2 && column == 1)
	{
		ifstream text("eastForest.txt");
		text.open("eastForest.txt");
		if (text.fail())
		{
			cout << "You enter the east side of the forest. Dark and dingy, this side of the forest seems a little haunted. To \nthe left is the cliff you awoke on, to the right is what appears to be a store, and above you looks like a house." << endl;
		}
		else
		{
			while (getline(text, line))
			{
				description.push_back(line);
			}


			for (int i = 0; i < description.size(); i++)
			{
				cout << description[i];
			}
			cout << endl;
		}
		text.close();
	}
	else if (row == 2 && column == 2)
	{
		ifstream text("store.txt");
		text.open("store.txt");
		if (text.fail())
		{
			cout << "Within the abandoned buildings you find a store. Glass shattered and goods thrown about everywhere. Above you is what looks like an old theater, to the left is the East entrance to the forest.There is nothing of interest to the right or below you." << endl;
		}
		else
		{
			while (getline(text, line))
			{
				description.push_back(line);
			}


			for (int i = 0; i < description.size(); i++)
			{
				cout << description[i];
			}
			cout << endl;
		}
		text.close();

	}

}


/**
placeKeys function generates 3 random sets of indexes and calls teh class function to change the bool value
for those particular cells
@param map -- the array of rooms
*/
void placeKeys(Room map[3][3])
{
	int row1 = (rand() % 2);
	int column1 = (rand() % 2);
	int row2 = (rand() % 2);
	int column2 = (rand() % 2);
	int row3 = (rand() % 2);
	int column3 = (rand() % 2);

	map[row1][column1].changeHasKeyItem(true);

	map[row2][column2].changeHasKeyItem(true);

	map[row3][column3].changeHasKeyItem(true);
}

/**
riddles function will lock player movement until they solve a riddle, and then give them a key
@param inventory -- the integer vector for evaluating how many keys there are
@return -- returns an integer so that the vector is populated
*/
int riddles(vector<int> inventory)
{
	//variables for the answer inputs
	string answer1, answer2, answer3;

	//while the player has no keys
	while (inventory.size() == 0)
	{
		//following code is the same for all 3 riddles, just different answers
		//riddle prompts
		cout << "\nYou see a faint glimmer out of the corner of your eye. You see a key locked behind glass, and etched above it are the \nwords:\n";
		cout << "**What is so fragile that saying its name breaks it.... What is it?**\n";
		cin >> answer1;
		//if the correct answer is put in
		if (answer1 == "silence" || answer1 == "Silence")
		{
			cout << "You utter the word under your breath and the glass shatters into a fine powder. You have " << inventory.size() + 1 << " key!\n Enter a movement: ";
			//bumps out of the function and returns a number
			return 1;
		}
		else
		{
			cout << "Try again.\n";
		}
	}
	//while they have 1 key
	while (inventory.size() == 1)
	{
		cout << "\nA familiar shimmer comes from the corner of your vision. Again you see a key with these words etched above it:\n";
		cout << "**If you drop me, I'm sure to crack, but give me a smile and I'll always smile back.... What am I?**\n";
		cin >> answer2;
		if (answer2 == "a mirror" || answer2 == "mirror" || answer2 == "A mirror" || answer2 == "A Mirror" || answer2 == "a Mirror" || answer2 == "Mirror")
		{
			cout << "Knowing what to do you speak your answer and the key appears in your hand. You now have " << inventory.size() + 1 << " keys!\n Enter a movement: ";
			return 1;
		}
		else
		{
			cout << "Try again.\n";
		}
	}
	//while they have 2 keys
	while (inventory.size() == 2)
	{
		cout << "\nJust what you were looking for, another key!. The riddle to unlock this one is as follows: \n";
		cout << "**I have cities, but no houses. I have mountains, but no trees. I have water, but no fish.... What am I?**\n";
		cin >> answer3;
		if (answer3 == "A map" || answer3 == "A Map" || answer3 == "Map" || answer3 == "map" || answer3 == "a map" || answer3 == "a Map")
		{
			cout << "You speak your answer and the glass dissipates! You now have " << inventory.size() + 1 << " keys\n Enter a movement: ";
			return 1;
		}
		else
		{
			cout << "Try again.\n";
		}

	}
}