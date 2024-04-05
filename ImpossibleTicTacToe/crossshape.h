#pragma once

#include "main.h"

class CrossShape : public sf::Shape
{
private:
	const static size_t MAX_VERTICES = 4;

	sf::Vertex *lines;
	float x, y, w, h;

public:
	CrossShape(sf::Vector2f pos, sf::Vector2f size);
	~CrossShape();

	void move(sf::Vector2f pos);

	sf::Vector2f getPoint(size_t index) const override;

	sf::Vertex * getLines() const { return lines; }

	size_t getPointCount() const override { return this->MAX_VERTICES; }
};

