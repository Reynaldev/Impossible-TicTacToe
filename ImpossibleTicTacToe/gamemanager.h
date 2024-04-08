#pragma once

#include "main.h"
#include "player.h"

class GameManager
{
private:
	const static size_t MAX_PLAYERS = 2;

private:
	Player *players = new Player[sizeof(Player) * MAX_PLAYERS];

	PlayerState playerState;

	unsigned int currentPlayer;

	int winScore, tieScore, loseScore;

public:
	GameManager(Player *playerOne, Player *playerTwo);
	~GameManager();

	void nextTurn();

	Player* getCurrentPlayer() const { return &players[currentPlayer]; }
	PlayerState getCurrentPlayerState() const { return playerState; }

	int getWinScore() const { return winScore; }
	int getTieScore() const { return tieScore; }
	int getLoseScore() const { return loseScore; }

};

