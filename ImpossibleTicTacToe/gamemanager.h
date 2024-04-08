#pragma once

#include "main.h"
#include "player.h"
#include "cell.h"

class GameManager
{
private:
	const static size_t MAX_PLAYERS = 2;

private:
	Player *players = new Player[sizeof(Player) * MAX_PLAYERS];

	PlayerState playerState;

	std::vector<Cell> cells;

	unsigned int currentPlayer;

	int winScore, tieScore, loseScore;

public:
	GameManager(Player *playerOne, Player *playerTwo, const sf::RenderWindow &window);
	~GameManager();

	void eventInput(const sf::Event &event);

	void nextTurn();

	void update(sf::RenderWindow &window);

	Player getCurrentPlayer() const { return players[currentPlayer]; }
	PlayerState getCurrentPlayerState() const { return playerState; }

	int getWinScore() const { return winScore; }
	int getTieScore() const { return tieScore; }
	int getLoseScore() const { return loseScore; }

};

