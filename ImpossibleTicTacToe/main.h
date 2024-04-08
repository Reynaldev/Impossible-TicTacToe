#pragma once

#include <iostream>
#include <array>
#include <string>

#include <SFML/Graphics.hpp>

#define CELL_SIZE 150

typedef unsigned int SymbolTypeFlag;
typedef unsigned int PlayerTypeFlag;
typedef unsigned int PlayerStateFlag;

enum SymbolType
{
	SYMBOL_TYPE_CROSS = 1,
	SYMBOL_TYPE_CIRCLE
};