#include "cell.h"

Cell::Cell(sf::Vector2f pos, sf::Vector2f size)
{
	x = pos.x + 2.5f;
	y = pos.y + 2.5f;
	w = size.x - 2.5f;
	h = size.y - 2.5f;

	backgroundShape.setSize(sf::Vector2f(w, h));
	backgroundShape.setPosition(sf::Vector2f(x, y));
	backgroundShape.setFillColor(sf::Color(150, 150, 150));
	backgroundShape.setOutlineColor(sf::Color::White);

	//printf("X: %.1f\tY: %.1f\n", x, y);
	//printf("Shape X: %.1f\tShape Y: %.1f\n", shape.getPosition().x, shape.getPosition().y);
	//printf("W: %.1f\tH: %.1f\n", w, h);
	//printf("Shape W: %.1f\tShape H: %.1f\n", shape.getSize().x, shape.getSize().y);
}

Cell::~Cell()
{
	reset();

	delete[] foregroundShape;
}

void Cell::setPosition(sf::Vector2f pos)
{
	x = pos.x;
	y = pos.y;

	backgroundShape.move(pos);
}

void Cell::insertSymbol(SymbolTypeFlag type)
{
	this->type = type;

	switch (this->type)
	{
	case SYMBOL_TYPE_CROSS:
	{
		CrossShape cross(sf::Vector2f(x + 2.5f, y + 2.5f), sf::Vector2f((w + x) - 2.5f, (h + y) - 2.5f));

		fgShapeVertSize = cross.getPointCount();

		foregroundShape = new sf::Vertex[sizeof(sf::Vertex) * fgShapeVertSize];

		for (size_t i = 0; i < fgShapeVertSize; i++)
		{
			sf::Vector2f vert = cross.getPoint(i);
			foregroundShape[i] = vert;
		}

		break;
	}
	case SYMBOL_TYPE_CIRCLE:
	{
		sf::CircleShape circle((w / 2.f) - 2.5f);

		fgShapeVertSize = circle.getPointCount() + 1;

		foregroundShape = new sf::Vertex[sizeof(sf::Vertex) * fgShapeVertSize];

		for (size_t i = 0; i < (fgShapeVertSize - 1); i++)
		{
			sf::Vector2f vert = circle.getPoint(i) + sf::Vector2f(x + 2.5f, y + 2.5f);
			foregroundShape[i] = vert;
		}

		foregroundShape[fgShapeVertSize - 1] = foregroundShape[0];

		break;
	}
	}
}

void Cell::draw(sf::RenderWindow &window)
{
	window.draw(backgroundShape);

	if (type != 0)
	{
		window.draw(foregroundShape, fgShapeVertSize, (type == SYMBOL_TYPE_CROSS) ? sf::Lines : sf::LineStrip);
	}

	isMouseClicked = false;
}

void Cell::reset()
{
	isMouseClicked = false;
	isMouseEntered = false;

	if (type != 0)
	{
		fgShapeVertSize = NULL;
		type = NULL;

		delete[] foregroundShape;
	}
}

void Cell::onMouseEntered(const sf::Event &e)
{
	sf::Vector2f mousePos((float)e.mouseMove.x, (float)e.mouseMove.y);

	if (mousePos.x > x
		&& mousePos.x < (x + w)
		&& mousePos.y > y
		&& mousePos.y < (y + h))
	{
		isMouseEntered = true;
	}
	else
	{
		isMouseEntered = false;
	}
}

void Cell::onMouseButtonClicked(const sf::Event &e)
{
	sf::Vector2f mousePos((float)e.mouseButton.x, (float)e.mouseButton.y);

	if (mousePos.x > x
		&& mousePos.x < (x + w)
		&& mousePos.y > y
		&& mousePos.y < (y + h))
	{
		isMouseClicked = true;
	}
}
