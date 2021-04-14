/* 9/19/2020 Created by Liam Martell. 
This program is designed to simulate a dice rolling game. The goal is to get to 100 points before the computer player. You gain points by adding together the roll of two dice.
If you roll a 1 on one of the dice, you lose the score for that roll and your turn ends. If you roll snake eyes, you lose all your points and your turn ends. The player goes first.*/



/*
Steps of this program:
1. while human score or robot score < 100
2. Read human input r or s
	1. Set char variable to return
	2. Ask for input; s or r
	3. cin char variable
	4. loop asking if char isn't s, S, r, or R
	5. return char
3. if r simulate dice roll
4. create dice roll function
	1. set integer equal to randomly generated number
	2. return random integer
5. check if one 1 rolled
	1. check if die1 rolled a 1 or die2 rolled a one and die1 can't equal die2
	2. set boolean value equal to true
	3. return boolean value
6. check if snake eyes rolled
	1. check if die1 rolled a 1 and die 2 rolled a 1
	2. set boolean value equal to true
	3. return boolean value
6. check for round score lost
	1. check if boolean value for 1 die is true
	2. set diceSum = 0
	3. return diceSum
7. if both 1, lose entire score
	1. check if boolean value for both is true
	2. set respective total = 0
	3. return total
8. if neither 1 cout the sum of the two dice
9. repeat step 2. 
10. have robot roll two dice
11. if 1 or both dice 1, do task 6 or 7 respectively and have robot end turn
*/



#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

//Function Callouts
char getUserInput(void); //ln. 140
int rollDie(void); //ln. 161
bool isTurnScoreLost(int die1value, int die2value); //ln. 174
bool isGameScoreLost(int die1value, int die2value); //ln. 192
int roundScore(bool gameScoreLost, int diceSum); //ln. 211
int playerScore(bool gameScoreLost, int humanTotal); //ln. 230
double playerScore(bool gameScoreLost, double computerTotal); //ln. 249


int main()
{
	srand(time(0)); //Seed for random number generator
	char a = ' ';   //char to continue or stop
	int humanTotal = 0; //Humans score for the game
	int diceSum = 0; //total of dice per roll
	double computerTotal = 0; //computer total for the game


	while (humanTotal < 100 && computerTotal < 100) //Condition checks if the game has been won
	{
		cout << endl << "SCORE RECAP: Player - " << humanTotal << ", Computer - " << computerTotal << endl << endl;
		cout << "Player Turn" << endl << endl;
		do
		{
			a = getUserInput();

			if (a == 'r' || a == 'R') //If player elects to roll
			{
				
				int die1value = rollDie(); //roll dice1
				int die2value = rollDie(); //roll dice2
				diceSum = die1value + die2value; //calculate diceSum

				//Check for 1's and erase value if 1 rolled
				bool turnScoreLost = isTurnScoreLost(die1value, die2value); //True if one 1 is rolled
				bool gameScoreLost = isGameScoreLost(die1value, die2value); //True if snake eyes rolled
				diceSum = roundScore(turnScoreLost, diceSum); //sets diceSum to 0 if one 1 rolled

				humanTotal = humanTotal + diceSum; //calculate player's total

				humanTotal = playerScore(gameScoreLost, humanTotal); //sets total score to 0 if snake eyes rolled

				//formatting scores
				cout << endl << "Your total is: " << humanTotal << endl << "Dice 1: " << die1value << ", Dice 2: " << die2value << endl << "Round Score: " << diceSum << endl << endl;

			}
			if (a == 's' || a == 'S') //if player elects to stop rolling
			{
				diceSum = 0;
			}
		} while (diceSum != 0 && humanTotal != 0 && humanTotal < 100); //ends turn if game is won, the player stopped rolling, or if any 1's are rolled

		if (humanTotal < 100) //If human has won
		{
			cout <<  endl << "Turn Over" << endl << "Computer's Turn" << endl;
			int pointsGained = 0;
			//Computers Turn
			do
			{
				int die1value = rollDie(); //roll dice1
				int die2value = rollDie(); //roll dice2
				diceSum = die1value + die2value; //calculate diceSum
				pointsGained = pointsGained + diceSum; //keeps track of points gained per turn

				//Checks for 1's and erase values if 1's rolled
				bool turnScoreLost = isTurnScoreLost(die1value, die2value); //true if one 1 rolled
				bool gameScoreLost = isGameScoreLost(die1value, die2value); //true if snake eyes rolled
				diceSum = roundScore(turnScoreLost, diceSum); //sets diceSum to 0 if one 1 rolled

				computerTotal = computerTotal + diceSum; //calculates the computer's total

				computerTotal = playerScore(gameScoreLost, computerTotal); //sets computers total to 0 if snake eyes rolled

				//score formatting
				cout << endl << "COMPUTER total is: " << computerTotal << endl << "Dice 1: " << die1value << ", Dice 2: " << die2value << endl << "Round Score: " << diceSum << endl;

			} while (diceSum != 0 && computerTotal != 0 && computerTotal < 100 && pointsGained < 25 ); //ends computer's turn if it wins or any 1's are rolled or if it gains 25 points
		}
		else { cout << "Game Over, You Win!" << endl; } //victory message if player wins
	}
		if (computerTotal >= 100) { cout << "Game Over, Computer Wins!" << endl; } //victory message if computer wins
}


/**
getUserInput function asks user to input R or S, and doesn't let any other value be entered
@return a -- the character (r or s) being returned
*/
char getUserInput(void)
{
	//1. Set char variable to return
	char a = ' ';
	do
	{
		//2. Ask for input; s or r
		cout << "Enter R to roll or S to Stop" << endl;
		//3. cin char variable
		cin >> a;
		//4. loop asking if char isn't s, S, r, or R
	} while (a != 'r' && a != 'R' && a != 's' && a != 'S');

	//5. return char
	return a;
}

/**
rollDie function generates a random number between 1 and 6
@return roll -- returns the value of a single dice rolled
*/
int rollDie(void)
{
	//1. set integer equal to randomly generated number
	int roll = int(1 + rand() % 6); 
	//2. return random integer
	return roll;
}

/**
isTurnScoreLost function sets a boolean value true if exactly 1 dice rolls a 1
@param die1value, die2value -- the value of each dice rolled
@return turnScoreLost -- Boolean value of whether the turn score will be lost
*/
bool isTurnScoreLost(int die1value, int die2value)
{
	//1. check if die1 rolled a 1 or die2 rolled a one and die1 can't equal die2
	if (die1value == 1 || die2value == 1 && die1value != die2value)
	{
		//2. set boolean value equal to true
		bool turnScoreLost = true;

		//3. return boolean value
		return turnScoreLost;
	}
}

/**
isGameScoreLost function sets a boolean value true if snake eyes are rolled
@param die1value, die2value -- the value of each die rolled
@return gameScoreLost -- Boolean value of whether the game score is lost
*/
bool isGameScoreLost(int die1value, int die2value)
{
	//1. check if die1 rolled a 1 and die 2 rolled a 1
	if (die1value == 1 && die2value == 1)
	{
		//2. set boolean value equal to true
		bool gameScoreLost = true;

		//3. return boolean value
		return gameScoreLost;
	}
}

/**
roundScore function sets the dice sum for 1 turn = 0
@param turnScoreLost -- boolean value if the turn score needs to be lost
@param diceSum -- int value of the turn for a round
@return diceSum -- int value of the turn for a round
*/
int roundScore(bool turnScoreLost, int diceSum)
{
	//1. check if boolean value for 1 die is true
	if (turnScoreLost == true)
	{
		//2. set diceSum = 0
		diceSum = 0;
	}

	//3. return diceSum
	return diceSum;
}

/**
playerScore function checks if boolean value for snake eyes is true and erases the respective total score
@param gameScoreLost -- boolean value if the gamescore actually need to be erased
@param humanTotal -- the total score of the player for the game
@return humanTotal -- the total score of the player for the game
*/
int playerScore(bool gameScoreLost, int humanTotal)
{
	//1. check if boolean value for both is true
	if (gameScoreLost == true)
	{
		//2. set respective total = 0
		humanTotal = 0;
	}

	//3. return total
	return humanTotal;
}

/**
OVERLOADED playerScore function for the score of the computer
@param -- gameScoreLost -- same as previous
@param -- computerTotal -- total score of the computer
return computerTotal -- made a double to be able to overload
*/
double playerScore(bool gameScoreLost, double computerTotal)
{

	//1. check if boolean value for both is true
	if (gameScoreLost == true)
	{
		//2. set respective total = 0
		computerTotal = 0;
	}

	//3. return total
	return computerTotal;
}