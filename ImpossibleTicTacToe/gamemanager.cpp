#include "gamemanager.h"

GameManager::GameManager(Player *playerOne, Player *playerTwo)
{
	players[0] = *playerOne;
	players[1] = *playerTwo;

	currentPlayer = 0;

	delete playerOne;
	delete playerTwo;
}

GameManager::~GameManager()
{
	delete[] players;
}

void GameManager::nextTurn()
{
	currentPlayer = (currentPlayer + 1) % MAX_PLAYERS;
}
