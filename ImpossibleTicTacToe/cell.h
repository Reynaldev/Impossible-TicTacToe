#pragma once

#include "main.h"

class Cell
{
private:
	bool isMouseEntered = false;
	bool isMouseClicked = false;

public:
	sf::RectangleShape backgroundShape;

	SymbolTypeFlag type;
	float x, y, w, h;

	Cell(sf::Vector2f pos, sf::Vector2f size);

	void setPosition(sf::Vector2f pos);
	void insertSymbol(SymbolTypeFlag type);

	void draw(sf::RenderWindow &window) const;

	void onMouseEntered(const sf::Event &e);
	void onMouseButtonClicked(const sf::Event &e);

	bool mouseEntered() const { return this->isMouseEntered; }
	bool mouseClicked() const { return this->isMouseClicked; }

	//void createCross(float posX, float posY)
	//{
	//	this->x = posX;
	//	this->y = posY;
	//	type = SYMBOL_TYPE_CROSS;

	//	crossShape = CrossShape(sf::Vector2f(x, y));
	//}

	//void createCircle(float radius)
	//{
	//	type = SYMBOL_TYPE_CIRCLE;

	//	circleShape = sf::CircleShape(radius);
	//}

	//void draw(sf::RenderWindow &window) const
	//{
	//	switch (type)
	//	{
	//	case SYMBOL_TYPE_CROSS:
	//		crossShape.draw(window);
	//		break;
	//	case SYMBOL_TYPE_CIRCLE:
	//		window.draw(circleShape);
	//		break;
	//	}
	//}
};

