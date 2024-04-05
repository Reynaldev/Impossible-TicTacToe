#pragma once

#include "main.h"
#include "crossshape.h"

class Cell
{
private:
	SymbolTypeFlag type;

	bool isMouseEntered = false;
	bool isMouseClicked = false;

public:
	sf::RectangleShape backgroundShape;
	sf::Vertex *foregroundShape = nullptr;

	size_t fgShapeVertSize;

	float x, y, w, h;

	Cell(sf::Vector2f pos, sf::Vector2f size);
	~Cell();

	void setPosition(sf::Vector2f pos);
	void insertSymbol(SymbolTypeFlag type);

	void draw(sf::RenderWindow &window);

	void onMouseEntered(const sf::Event &e);
	void onMouseButtonClicked(const sf::Event &e);

	bool mouseEntered() const { return this->isMouseEntered; }
	bool mouseClicked() const { return this->isMouseClicked; }

	bool isFilled() const { return (this->type != 0); }
};

