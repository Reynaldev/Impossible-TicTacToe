#include "crossshape.h"

CrossShape::CrossShape(sf::Vector2f size)
{
	sf::Vertex newLines[MAX_VERTICES] = {
		sf::Vertex(sf::Vector2f(size.x, size.x)),
		sf::Vertex(sf::Vector2f(size.y, size.y)),
		sf::Vertex(sf::Vector2f(size.y, size.x)),
		sf::Vertex(sf::Vector2f(size.x, size.y))
	};

	x = size.x;
	y = size.x;
	w = size.y;
	h = size.y;

	memcpy_s(lines, sizeof(lines), newLines, sizeof(newLines));
}

void CrossShape::move(sf::Vector2f pos)
{
	lines[0].position = sf::Vector2f(pos.x - (w / 2.0f), pos.y - (w / 2.0f));
	lines[1].position = sf::Vector2f(pos.x + (w / 2.0f), pos.y + (w / 2.0f));
	lines[2].position = sf::Vector2f(pos.x + (w / 2.0f), pos.y - (w / 2.0f));
	lines[3].position = sf::Vector2f(pos.x - (w / 2.0f), pos.y + (w / 2.0f));
}

void CrossShape::draw(sf::RenderWindow &window) const
{
	window.draw(lines, MAX_VERTICES, sf::Lines);
}
