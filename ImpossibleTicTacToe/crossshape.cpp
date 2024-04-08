#include "crossshape.h"

CrossShape::CrossShape(sf::Vector2f pos, sf::Vector2f size)
{
	lines = new sf::Vertex[sizeof(sf::Vertex) * MAX_VERTICES];

	lines[0] = sf::Vertex(sf::Vector2f(pos.x, pos.y));			// Top-left
	lines[1] = sf::Vertex(sf::Vector2f(size.x, size.y));		// Bottom-right
	lines[2] = sf::Vertex(sf::Vector2f(size.x, pos.y));			// Top-right
	lines[3] = sf::Vertex(sf::Vector2f(pos.x, size.y));			// Bottom-left

	x = pos.x;
	y = pos.y;
	w = size.x;
	h = size.y;

	update();
}

CrossShape::~CrossShape()
{
	delete[] lines;
}

void CrossShape::move(sf::Vector2f pos)
{
	lines[0].position = sf::Vector2f(pos.x - (w / 2.0f), pos.y - (w / 2.0f));
	lines[1].position = sf::Vector2f(pos.x + (w / 2.0f), pos.y + (w / 2.0f));
	lines[2].position = sf::Vector2f(pos.x + (w / 2.0f), pos.y - (w / 2.0f));
	lines[3].position = sf::Vector2f(pos.x - (w / 2.0f), pos.y + (w / 2.0f));

	update();
}

sf::Vector2f CrossShape::getPoint(size_t index) const
{
	return sf::Vector2f(lines[index].position.x, lines[index].position.y);
}
