#pragma once

#include "main.h"

enum PlayerType
{
	PLAYER_HUMAN,
	PLAYER_AI
};

class Player
{
public:
	PlayerTypeFlag type;
	SymbolSignFlag symbol;
	char name[8];

	int scoreWin = 0;
	int scoreLose = 0;

	/* Default constructor. Use Player(const char *username, SymbolTypeFlag symbol, PlayerTypeFlag type) instead */
	Player() {}

	Player(const char *username, PlayerTypeFlag type);
};

