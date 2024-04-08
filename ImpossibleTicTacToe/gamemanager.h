#pragma once

#include "main.h"
#include "player.h"
#include "cell.h"

class GameManager
{
private:
	const static size_t MAX_PLAYERS = 2;

private:
	Cell cells[9];

	Player *players = new Player[sizeof(Player) * MAX_PLAYERS];

	bool nextTurn = false;
	bool isFinished = false;

	int currentPlayer;

	int winScore, tieScore, loseScore;

public:
	GameManager(Player *playerOne, Player *playerTwo, const sf::RenderWindow &window);
	~GameManager();

	void eventInput(const sf::Event &event);

	void update(sf::RenderWindow &window);

	Player getCurrentPlayer() const { return players[currentPlayer]; }

	int getWinScore() const { return winScore; }
	int getTieScore() const { return tieScore; }
	int getLoseScore() const { return loseScore; }

};

