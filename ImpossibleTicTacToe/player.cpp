#include "player.h"

Player::Player(const char *username, SymbolTypeFlag symbol, PlayerTypeFlag type)
{
	this->symbol = symbol;
	this->type = type;
	memcpy_s(this->name, sizeof(this->name), username, sizeof(char) * 8);
}
