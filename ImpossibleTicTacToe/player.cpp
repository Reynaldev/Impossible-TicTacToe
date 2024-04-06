#include "player.h"

Player::Player(const char *username, SymbolTypeFlag type)
{
	this->symbol = type;
	memcpy_s(this->name, sizeof(this->name), username, sizeof(char) * 8);
}
