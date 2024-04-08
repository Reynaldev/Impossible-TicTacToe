#include "player.h"

Player::Player(const char *username, PlayerTypeFlag type)
{
	this->type = type;
	memcpy_s(this->name, sizeof(this->name), username, sizeof(char) * 8);
}
