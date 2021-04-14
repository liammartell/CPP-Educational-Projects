#include <iostream>
#include <string>

using namespace std;

											//GLOBAL VARIABLES
//======================================================================================================
//the size of the game board array
const int SIZE = 3;
//the row number of the array
int row;
//the column number of the array
int column;

											//STRUCTURES
//======================================================================================================
//data type names represents the names of players
struct names
{
	//the main player name. will be used to add points to everyones score
	string main;
	//the second players name. Only used to display second player's points, and to switch the main name when turns switch
	string two;
	//acts like a storage bin for the names. Only used when switching the main name when turns switch
	string storedName;
};

											//FUNCTIONS FROM INSTRUCTIONS
//======================================================================================================

/**
getPlayerInput function will ask the user for a value 1-9
@param playerNames - names of players from data structure names
@return location - returns the value 1-9 the user inputted
*/
int getPlayerInput(names playerNames)
{
	cout << endl;
	int location = 0;
	//1. loops while invalid number is entered
	while (location < 1 || location > 9) 
	{
		//2. prompts the user to enter a valid number
		cout << "Please Specify Box Number 1 - 9" << endl;
		//3. reads in the entered number
		cin >> location;
	}
	//4. returns a valid number
	return location;
}

/**
locationToBoardLocation function assigns an int value 1 - 9 to a cell in the 2D board array
@param location - the location the user previously entered
@param &row - the row location inside the array for the specific location value
@param &column - the column location inside the array for the specific location value
*/
void locationToBoardLocation(int location, int &row, int &column)
{
	//switch statement for every location on the tic-tac-toe board
	switch (location) {
	case 1: row = 0; column = 0; break;
	case 2: row = 0; column = 1; break;
	case 3: row = 0; column = 2; break;
	case 4: row = 1; column = 0; break;
	case 5: row = 1; column = 1; break;
	case 6: row = 1; column = 2; break;
	case 7: row = 2; column = 0; break;
	case 8: row = 2; column = 1; break;
	case 9: row = 2; column = 2; break;
	}

}

/**
isLegalMove function will check whether the location the player selected is already taken or not. evaluates true if the location is already taken
@param board - the game board array
@param location - the location the player previously entered
@return - returns true if spot is taken and false if the move is legal
*/
bool isLegalMove(char board[SIZE][SIZE], int location) 
{
	//1. convert the inputted location to the actual location on the game board
	locationToBoardLocation(location, row, column);
	//2. if the board location has already been taken
	if (board[row][column] == 'X' || board[row][column] == 'O')
	{
		//3. return true
		return true;
	}
	//4. if the board location is playable
	else
	{
		//5. return false
		return false;
	}
}

/**
placeMarkOnBoard function will place the current playerMark(X or O) on the specified board location
@param board - the game board array
@param playerMark - the current mark (X or O) denoting a taken spot on the board
@param location - the board location previously specified by user
*/
void placeMarkOnBoard(char board[SIZE][SIZE], char playerMark, int location)
{
	//1. convert the inputted location to the actual location on game board
	locationToBoardLocation(location, row, column);
	//2. sets the board location for the specified numerical location equal to the current playerMark
	board[row][column] = playerMark;
}

/**
clearBoard function will set the board to its default display of 1-9
@param board - the game board array
*/
void clearBoard(char board[SIZE][SIZE])
{
	//1. start variable represents the 1st slot of the game board array
	char start = '1';
	//2. for loop for the rows
	for (int i = 0; i < 3; i++)
	{
		//3. for loop for the columns
		for (int j = 0; j < 3; j++)
		{
			//4. sets every board location equal to the start char
			board[i][j] = start;
			//5. increments the start char
			start++;
		}
	}
}

/**
hasThreeInARow function will check the game board for three identical adjacent values either vertical, horizontal, or diagonal
@param board - the game board array
@param playerMark - the current mark (X or O) for the player
@return bool - function will return false if there are three in a row. This is to bump out of a loop.
@return bool - function will return true if there are not three identical playermarks in a row. This is to stay in a loop
*/
bool hasThreeInARow(char board[SIZE][SIZE], char playerMark)
{
	//1. for loop checks every row and column
	for (int i = 0; i < 3; i++)
	{
		//2. if there are 3 identical entries for both rows (before ||) and columns (after ||)
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2] || board[0][i] == board[1][i] && board[1][i] == board[2][i]) 
		//3. returns false for 3 in a row
		{ return false; }
	}
	//4. if there are three identical rows for both diagonal directions
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2] || board[0][2] == board[1][1] && board[1][1] == board[2][0]) 
	//5. returns false for 3 in a row
	{ return false; }
	/*6. if function makes it to here, that means there are not 3 in a row
	so we return true to keep looping gameplay*/
	return true;
}

/**
displayGameStats function prints to the console the current wins and ties
@param gameStats - array including the values for player1wins, player2wins, and ties
@param playerNames - names data structure containing the main player name, and player 2's name
*/
void displayGameStats(int gameStats[3], names playerNames)
{
	//1. label
	cout << "GAME OVER!" << endl << endl;
	cout << "                       SCORE                        \n";
	//2. border
	cout << "====================================================\n";
	//3. prints out player 1's name and score
	cout << "Player 1 (" << playerNames.main << ") has won: " << gameStats[0] << " games!" << endl;
	//4. prints out player 2's name and score
	cout << "Player 2 (" << playerNames.two << ") has won: " << gameStats[1] << " games!" << endl;
	//5. prints out the number of ties
	cout << "There have been: " << gameStats[2] << " ties" << endl;
	//6. lower border
	cout << "====================================================\n";
}

/**
displayBoard function displays the current game board with numbers 1-9, X's, and O's
@param board - the game board array
*/
void displayBoard(char board[SIZE][SIZE]) 
{
	//1. free space on top
	cout << endl;
	//2. for the rows of the grid
	for (int i = 0; i < SIZE; i++)
	{
		//3. if the middle row is being constructed
		if (i == 1)
		{
			//4. adds a border between 1st and 2nd row
			cout << endl << "---+---+---" << endl;
			//5. for the columns of the grid
			for (int j = 0; j < SIZE; j++)
			{
				//6. if the middle column is being constructed place borders on the outsie of the middle column entry
				if (j == 1) { cout << "| " << board[i][j] << " |"; }
				//8. if the outside columns, space the entry in the middle of the cell
				else { cout << " " << board[i][j] << " "; }
			}
			//9. adds a border between the 2nd and 3rd row
			cout << endl << "---+---+---" << endl;
		}
		//10. if top or bottom row is being constructed
		else
		{
			//11. for the columns of the grid
			for (int j = 0; j < SIZE; j++)
			{
				//12. if the middle column, place borders on the outside of the entry
				if (j == 1) { cout << "| " << board[i][j] << " |"; }
				//13. if outside entries, properly space the entry in the middle of the cell
				else { cout << " " << board[i][j] << " "; }
			}
		}
	}
	//14. bottom space for clarity
	cout << endl;
}

											//MY OTHER FUNCTIONS
//======================================================================================================

/**
switchTurn function switches the playerMark from X to O and switches the main player name after each marker is placed
@param &playerMark - the current player mark (X or O) pass by reference to change the value
@param playerNames - names data structure containing the main player name, the second player name, and the stored player name
@return playerNames - returns the structure playernames containing the main player name, the second player name, and the stored player name
*/
names switchTurn(char &playerMark, names playerNames)
{
	//1. if the current player mark is X
	if (playerMark == 'X')
	{ 
		//2. switch it to O
		playerMark = 'O';
	}
	//3. If the current player mark is O, switch it to X
	else if (playerMark == 'O') { playerMark = 'X'; }
	//4. rotates player names, so player 2 knows to go.
	playerNames.storedName = playerNames.main; playerNames.main = playerNames.two; playerNames.two = playerNames.storedName;
	//5. returnes the values inside of playerNames
	return playerNames;
}

/**
whosTurn function prints to the console the player name whose turn it is, and their respective player mark
@param playerNames - the names data structure containing the main player name, the second player name, and the stored player name
@param playerMark - the current Marker (X or O)
*/
void whosTurn(names playerNames, char playerMark)
{
	//1. tells the player whose turn it is and what their marker is
	cout << endl << playerNames.main << "'s Turn!" << " You are " << playerMark << endl;
}

/**
tie function will check the board for 3 in a row and if there are any playable spots left
@param board - the current board array
@param playerMark - the current playerMark
@return bool - will return TRUE if there is not 3 in a row and NO tie IE the game can be continued
@return bool - will return false if there is either 3 in a row or there IS a tie IE the game can't continue
*/
bool tie(char board[SIZE][SIZE], char playerMark)
{
	//1. int value representing the number of Markers on the board
	int count = 0;
	//2. checks for 3 in a row (evaluates true if there is not 3 in a row)
	if (hasThreeInARow(board, playerMark))
	{
		//3. For the rows of the array
		for (int i = 0; i < 3; i++)
		{
			//4. for the columns of the array
			for (int j = 0; j < 3; j++)
			{
				//5. every time there is an X or O detected...
				if (board[i][j] == 'X' || board[i][j] == 'O' )
				{
					//6. increment the count variable
					count ++;
				}
			}
		}
		//7. if the 9 markers are detected
		if (count == 9)
		{
			//8. return false IE there are no more spots to play on the board
			return false;
		}
		//9. return true if the program makes it to here there is no tie and the game can continue
		return true;
	}
	//10. returns false if there are 3 in a row IE game cannot continue
	else { return false; }
}

/**
modifyGameScore function will increase player1's score, player2's score, or the number of ties based on the last main player name
@param playerMark - the current marker (X or O)
@param board - the current game board array
@param playerNames - names data structure containing the main player name, the second player name, and the stored player name
@param ORIGIN_NAMES - the original names for player1 and player2
@param gameStats[3] - the values for player1's score, player2's score, and the number of ties respectively
*/
void modifyGameScore(char playerMark, char board[SIZE][SIZE], names playerNames, const string ORIGIN_NAMES[2], int gameStats[3])
{
	//1. if the program detects a tie
	if (hasThreeInARow(board, playerMark))
	{
		//2. increase the number of ties
		gameStats[2]++;
	}
	//3. if the current main name is the same as player1's name
	else if (playerNames.main == ORIGIN_NAMES[0])
	{
		//4. increment player2's score because whenever the game ends, the current main player name is the opposite of the player that won
		gameStats[1]++;
	}
	//5. if the current main name is the same as player2's name
	else if (playerNames.main == ORIGIN_NAMES[1])
	{
		//6. increment player1's score because whenever the game ends, the current main player name is teh opposite of the player that won
		gameStats[0]++;
	}
}

/**
switchFirstTurn function will switch the main player name so that after every game, the person that goes first alternates
@param gameStats[3] - the current player1 score, player2 score, and number of ties respectively
@param playerNames - names data structure containing the main player name, the other players name, and the stored player name
@param ORIGIN_NAMES[2] - the original names of player1 and player2
@return playerNames - returns the main name, the other player name, and the stored player name
*/
names switchFirstTurn(int gameStats[3], names playerNames, const string ORIGIN_NAMES[2])
{
	//1. if the total score is odd (the number of games played is odd)
	if ((gameStats[0] + gameStats[1] + gameStats[2]) % 2 == 1)
	{
		//2. change the values inside playerName so that player2 goes first and switchTurn function will work properly
		playerNames.main = ORIGIN_NAMES[1];
		playerNames.two = ORIGIN_NAMES[0];
		playerNames.storedName = ORIGIN_NAMES[0];
	}
	//3. if the total score is even (the number of games played is even)
	else if ((gameStats[0] + gameStats[1] + gameStats[2] % 2 == 0))
	{
		//4. change the values inside playerName so that player1 goes first and switchTurn function will work properly
		playerNames.main = ORIGIN_NAMES[0];
		playerNames.two = ORIGIN_NAMES[1];
		playerNames.storedName = ORIGIN_NAMES[1];
	}

	//5. return the modified values inside playerNames
	return playerNames;
}

/**
whoWon function will display to the console a game over message, and the name of the player that won
@param board - the current game board array
@param playerMark - the current player mark (X or O)
@param playerName - names data structure containing the main player name, the other players name, and the stored player name
*/
void whoWon(char board[SIZE][SIZE], char playerMark, names playerName)
{
	//1. set up variables for number of x's and number of o's
	int x = 0;
	int o = 0;
	//2. checking every row
	for (int i = 0; i < 3; i++)
	{
		//3. checking every column
		for (int j = 0; j < 3; j++)
		{
			//4. if that cell contains an X
			if (board[i][j] == 'X')
			{
				//5. increase the number of X's
				x++;
			}
			//6. if that cell conatins an O
			else if (board[i][j] == 'O')
			{
				//7. increase the number of O's
				o++;
			}
		}
	}
	//8. if there are more o's than x's at the end of the game, then O has to have won, give appropriate win message
	if (o > x) { cout << endl << "Game over! " << playerName.two << " Wins!" << endl; }
	//9. if there are no ties and more x's than o's at the end of the game, then X has to have won, give appropriate win message
	else if (tie(board, playerMark) && x > o) { cout << endl << "Game over! " << playerName.two << " Wins!" << endl; }
}

											//MAIN FUNCTION
//======================================================================================================

int main()
{
	//character for continuing the game or not
	char cont = 'Y';
	//names structure called playerNames
	names playerNames;
	//location number 1-9
	int location;
	//the game board array
	char board[SIZE][SIZE];
	//[0] = player1's score, [1] = player2's score, [2] = number of ties
	int gameStats[3] = { 0, 0, 0 };

	//sets up the game board with values 1-9
	clearBoard(board);

	//initial welcom/prompts and asks for the player's names
	cout << "Welcome to Tic-Tac-Toe!\n" << "Please enter your names. Player 1 will go first. Then you can switch!" << endl;
	cout << "Player 1: ";
	cin >> playerNames.main;
	cout << "Player 2: ";
	cin >> playerNames.two;
	cout << endl;

	//[0] = player1's name, [1] = player2's name
	const string ORIGIN_NAMES[2] = { playerNames.main, playerNames.two };

	//while the player wants to continue
	while (cont == 'Y' || cont == 'y')
	{
		//the marker at the start of each game is X
		char playerMark = 'X';

		//checks for 3 in a row or ties after O's turn
		while (hasThreeInARow(board, playerMark) && tie(board, playerMark))
		{
			//Tells the user whose turn it is and their marker
			whosTurn(playerNames, playerMark);
			//displays the current game board
			displayBoard(board);

			do
			{
				//gets the player input for location of their choice
				location = getPlayerInput(playerNames);
			//if the location they choose is already taken it will prompt them again
			} while (isLegalMove(board, location));

			//updates board with the selected location for X
			placeMarkOnBoard(board, playerMark, location);
			//switches player mark from x to o
			playerNames = switchTurn(playerMark, playerNames);

			//checks for wins or ties after X's turn
			if (hasThreeInARow(board, playerMark) && tie(board, playerMark))
			{
				//Tells the user whose turn it is and their marker
				whosTurn(playerNames, playerMark);
				//displays the current game board
				displayBoard(board);

				do
				{
					//gets the player input for location of their choice
					location = getPlayerInput(playerNames);
				//if the location they choose is already taken it will prompt them again
				} while (isLegalMove(board, location));

				//updates the board with the selected location for O
				placeMarkOnBoard(board, playerMark, location);
				//switches player mark from O to X
				playerNames = switchTurn(playerMark, playerNames);
			}
		}
		//displays the winning game board
		displayBoard(board);
		//displays the winner of this game
		whoWon(board, playerMark, playerNames);
		//increases the scores based on the outcome of the game
		tie(board, playerMark);
		modifyGameScore(playerMark, board, playerNames, ORIGIN_NAMES, gameStats);
		//displays the game stats
		displayGameStats(gameStats, playerNames);
		//resets the board for the next game
		clearBoard(board);
		//prompts the user to input y or n to continue or stop
		cout << "Would you like to continue playing? (Y for yes or N for no)\n";
		cin >> cont;
	}
}