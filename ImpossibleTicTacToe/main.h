#pragma once

#include <iostream>
#include <array>

#include <SFML/Graphics.hpp>

#define CELL_SIZE 150

typedef unsigned int SymbolTypeFlag;

enum SymbolType
{
	SYMBOL_TYPE_CROSS = 1,
	SYMBOL_TYPE_CIRCLE
};