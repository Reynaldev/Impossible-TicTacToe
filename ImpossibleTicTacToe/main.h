#pragma once

#include <iostream>
#include <array>
#include <string>

#include <SFML/Graphics.hpp>

#define CELL_SIZE 150

typedef int SymbolTypeFlag;
typedef int PlayerTypeFlag;
typedef int PlayerStateFlag;

enum SymbolType
{
	SYMBOL_TYPE_EMPTY = -1,
	SYMBOL_TYPE_CROSS,
	SYMBOL_TYPE_CIRCLE
};

template <typename T>
constexpr int arrLen(T *arr) { return sizeof(arr) / sizeof(*arr); }