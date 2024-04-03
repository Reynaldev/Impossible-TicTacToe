#pragma once

#include "main.h"

class CrossShape
{
private:
	const static unsigned int MAX_VERTICES = 4;

	sf::Vertex lines[MAX_VERTICES];
	float x, y, w, h;

public:
	CrossShape() {}

	CrossShape(sf::Vector2f size);

	void move(sf::Vector2f pos);

	void draw(sf::RenderWindow &window) const;
};

