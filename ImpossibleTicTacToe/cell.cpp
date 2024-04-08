#include "cell.h"

Cell::Cell()
{
	backgroundShape.setSize(sf::Vector2f(w, h));
	backgroundShape.setPosition(sf::Vector2f(x, y));
	backgroundShape.setFillColor(sf::Color(150, 150, 150));
	backgroundShape.setOutlineColor(sf::Color::White);
}

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

void Cell::setSize(sf::Vector2f size)
{
	w = size.x - 2.5f;
	h = size.y - 2.5f;

	backgroundShape.setSize(sf::Vector2f(w, h));
}

void Cell::insertSymbol(SymbolSignFlag sym)
{
	this->sym = sym;

	switch (this->sym)
	{
	case SYMBOL_SIGN_CROSS:
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
	case SYMBOL_SIGN_CIRCLE:
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

	if (sym != SYMBOL_SIGN_EMPTY)
	{
		window.draw(foregroundShape, fgShapeVertSize, (sym == SYMBOL_SIGN_CROSS) ? sf::Lines : sf::LineStrip);
	}

	isMouseClicked = false;
}

void Cell::reset()
{
	isMouseClicked = false;
	isMouseEntered = false;

	if (sym != SYMBOL_SIGN_EMPTY)
	{
		fgShapeVertSize = 0;
		sym = SYMBOL_SIGN_EMPTY;

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
