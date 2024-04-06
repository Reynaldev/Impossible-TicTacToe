#pragma once

#include "main.h"

class Player
{
public:
	SymbolTypeFlag symbol;
	char name[8];

	Player(const char *username, SymbolTypeFlag type);
};

