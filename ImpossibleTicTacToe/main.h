#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

#define CELL_SIZE 150

typedef unsigned int SymbolTypeFlag;

enum SymbolType
{
	SYMBOL_TYPE_CROSS,
	SYMBOL_TYPE_CIRCLE
};