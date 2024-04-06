#pragma once

#include "main.h"

enum PlayerState
{
	PLAYER_ONE,
	PLAYER_TWO
};

class Player
{
public:
	SymbolTypeFlag symbol;
	char name[8];

	Player(const char *username, SymbolTypeFlag type);
};

