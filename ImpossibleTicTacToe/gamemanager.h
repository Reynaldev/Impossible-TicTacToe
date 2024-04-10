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

public:
	GameManager(Player *playerOne, Player *playerTwo, const sf::RenderWindow &window);
	~GameManager();

	void eventInput(const sf::Event &event);

	void update(sf::RenderWindow &window);

	// Return the current player
	Player getCurrentPlayer() const { return players[currentPlayer]; }

	// Return the player by index. Not bound checking.
	Player getPlayer(int index) const { return players[index]; }

};

