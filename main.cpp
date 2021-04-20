#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <map>
#include <ctime>
#include <climits>

using namespace std;

const int ARRAY_SIZE = 60;
const int MAX_PLAYERS = 6;
const int BOARD_SIZE = 135;
enum colorType {ORANGE, BLUE, GREEN, YELLOW, RED, PURPLE};
struct cardType 
{
	colorType cardColor;
	bool isDouble = false;
};

struct deckType
{
	cardType deck[ARRAY_SIZE];
	bool used[ARRAY_SIZE];
	int numUsed;
};

struct playerType
{
	colorType playerColor;
	int position;
};

struct playerListType
{
	playerType list[MAX_PLAYERS];
	int numPlayers;
};
/*
struct listType
{
	int listElem[ARRAY_SIZE];
	int listLength = 0;
}
*/




const map<colorType, string> colorsMap = {{ORANGE, "Orange"},{BLUE, "Blue"}, {GREEN, "Green"}, {YELLOW, "Yellow"}, {RED, "Red"}, {PURPLE, "Purple"}};
const map<string, colorType> colorStrMap = {{"orange", ORANGE},{"blue", BLUE}, {"green", GREEN}, {"yellow", YELLOW}, {"red",RED}, {"purple", PURPLE}};

colorType inputColor();
void toLowerStr(string&);
colorType generateColor();
void outputCard(cardType theCard);
deckType generateDeck();
void generateBoard(colorType board[], int numSpaces);
int getNumPlayers();
void setupPlayers(playerListType& playerList);
void printBoard(colorType board[], int numSpaces, playerListType& playerList);
void printPlayerOnBoard(playerListType& playerList, int boardPos);

int main()
{
	srand(time(0));
	colorType board[BOARD_SIZE];
	deckType myDeck = generateDeck();
	generateBoard(board,BOARD_SIZE);
	playerListType plt;
	plt.numPlayers = getNumPlayers();
	setupPlayers(plt);
	printBoard(board, BOARD_SIZE, plt);
	
	
	
	/*for(int i = 0; i < ARRAY_SIZE; i++)
	{
		outputCard(myDeck.deck[i]);
		cout << endl;
	}*/
	
	/*listType myList;
	for(int i = 0; i < 10; i++)
	{
		myList.listElem[myList.listLength] = i;
		myList.listLength++;
		
	}*/
	
	return 0;
}

string colorToString(colorType theColor)
{
	switch(theColor)
	{
		case ORANGE: return "Orange";
		case BLUE: return "Blue";
		case YELLOW: return "Yellow";
		case GREEN: return "Green";
		case RED: return "Red";
		case PURPLE: return "Purple";
	}
	return "Unknown";
}

colorType inputColor()
{
	colorType theColor = ORANGE;
	bool found = false;
	string colorStr;
	
	while(!found)
	{
		cout << "enter a color: " << endl;
		cin >> colorStr;
		toLowerStr(colorStr);
		//cout << "You entered: " << colorStr << endl;
		if(colorStrMap.count(colorStr) > 0)
		{
			theColor = colorStrMap.at(colorStr);
			found = true;
		} else
			cout << "That is not a valid color! The choices are orange, blue, green, yellow, red, and purple." << endl;
	}
	
	return theColor;
}


void toLowerStr(string& theString)
{
	for(int i = 0; i < theString.length(); i++ )
	{
		theString[i] = tolower(theString[i]);
	}
}

colorType generateColor()
{
	colorType theColor;
	int colorInt = rand() % 6;
	theColor = static_cast<colorType>(colorInt);
	return theColor;
}

void outputCard(cardType theCard)
{
	string doubled = theCard.isDouble ? "Double " : "";
	cout << doubled << colorsMap.at(theCard.cardColor) << " ";
	int num = theCard.isDouble ? 2 : 1;
	
	for(int i = 0; i < num; i++)
	{
	
		switch(theCard.cardColor)
		{
			case ORANGE: cout << "\033[1m\033[38;5;214m\033[48;5;202m[";
				cout <<"]\033[0m"; break;
			case BLUE: cout << "\033[1;34;44m[";
				cout << "]\033[0m"; break;
			case YELLOW: cout << "\033[1;33;43m[";
				cout <<"]\033[0m"; break;
			case GREEN: cout << "\033[1;32;42m[";
				cout << "]\033[0m"; break;
			case RED: cout << "\033[1;31;41m[";
				cout << "]\033[0m"; break;
			case PURPLE: cout << "\033[1;35;45m[";
				cout <<"]\033[0m"; break;
		}
		cout << " ";
	}
}


deckType generateDeck()
{
	deckType theDeck;
	map<colorType, string>::const_iterator it;
	int count = 0;
	for(it = colorsMap.begin(); it != colorsMap.end(); it++)
	{
		for(int i = 0; i < 6; i++)
		{
			theDeck.deck[count].cardColor = it->first;
			theDeck.deck[count].isDouble = false;
			count++;
		}
		for(int i = 0; i < 4; i++)
		{
			theDeck.deck[count].cardColor = it->first;
			theDeck.deck[count].isDouble = true;
			count++;
		}
	}
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		theDeck.used[i] = false;
	}
	theDeck.numUsed = 0;
	return theDeck;
}

void generateBoard(colorType board[], int numSpaces)
{
	board[0] = static_cast<colorType>(-1);
	for(int i = 1; i < numSpaces; i++)
	{
		board[i] = generateColor();
	}
}

int getNumPlayers()
{
	int numPlayers;
	cout << "Enter the number of players between 2 and 6: ";
	cin >> numPlayers;
	cout << endl;
	while(!cin || numPlayers < 2 || numPlayers > 4)
	{
		if(!cin)
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		cout << "that is not a valid value." << endl;
		cout << "Enter the number of players between 2 and 6: ";
		cin >> numPlayers;
		cout << endl;
	}
	return numPlayers;
}

void setupPlayers(playerListType& playerList)
{
	for(int i = 0; i < playerList.numPlayers; i++)
	{
		cout << "Player " << i + 1 << " ";
		playerList.list[i].playerColor = inputColor();
		for(int j = 0; j < i; j++)
		{
			if(playerList.list[j].playerColor == playerList.list[i].playerColor)
			{
				cout << "Player " << j + 1 << " has already picked that color. Please pick again." << endl;
				playerList.list[i].playerColor = inputColor();
				j = -1;
			}
		}
		playerList.list[i].position = 0;
	}
}

void printBoard(colorType board[], int numSpaces, playerListType& playerList) 
{
	string colorStr;
	for(int i = 0; i < numSpaces; i++)
	{
		switch(board[i])
			{
				case ORANGE: colorStr =  "\033[1m\033[38;5;214m\033[48;5;202m";break;
				case BLUE: colorStr = "\033[1;34;44m"; break;
				case YELLOW: colorStr = "\033[1;33;43m"; break;
				case GREEN: colorStr =  "\033[1;32;42m"; break;
				case RED: colorStr = "\033[1;31;41m"; break;
				case PURPLE: colorStr = "\033[1;35;45m"; break;
				default: colorStr = ""; break;
			}
		cout << colorStr << "[";
		printPlayerOnBoard(playerList, i);
		cout << colorStr;
		cout <<"]\033[0m";
		cout << " ";
		if((i+1) % 5 == 0)
			cout << endl;
	}
}

void printPlayerOnBoard(playerListType& playerList, int boardPos)
{
	for(int i = 0; i < playerList.numPlayers; i++)
	{
		if(playerList.list[i].position == boardPos)
		{
			switch(playerList.list[i].playerColor)
			{
				case ORANGE: cout << "\033[1m\033[38;5;214m\033[48;5;202m";break;
				case BLUE: cout << "\033[1;34;44m"; break;
				case YELLOW: cout << "\033[1;33;43m"; break;
				case GREEN: cout << "\033[1;32;42m"; break;
				case RED: cout << "\033[1;31;41m"; break;
				case PURPLE: cout << "\033[1;35;45m"; break;
				default: cout << "["; break;
			}
			cout << i + 1;
			cout <<"\033[0m";
		} else 
			cout << " ";
	}
}

