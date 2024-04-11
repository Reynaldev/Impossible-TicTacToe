#pragma once

#include <iostream>
#include <string>
#include <ctime>

#include <SFML/Graphics.hpp>

#define CELL_SIZE 150

typedef int SymbolSignFlag;
typedef int PlayerTypeFlag;
typedef int PlayerStateFlag;

enum SymbolSign
{
	SYMBOL_SIGN_EMPTY = -1,
	SYMBOL_SIGN_CROSS,
	SYMBOL_SIGN_CIRCLE
};