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

	printf("Cell[%.1f, %.1f] Type: %d\n", x, y, this->type);

	switch (this->type)
	{
	case SYMBOL_TYPE_CIRCLE:
		sf::CircleShape circle((w / 2.f) - 2.5f);
		circle.setFillColor(sf::Color(0, 0, 0, 0));
		circle.setOutlineColor(sf::Color(50, 50, 50));
		circle.setPosition(sf::Vector2f(x, y));

		fgShapeVertSize = circle.getPointCount();
		
		foregroundShape = new sf::Vertex[sizeof(sf::Vertex) * fgShapeVertSize];

		for (int i = 0; i < fgShapeVertSize; i++)
		{
			sf::Vector2f vert = circle.getPoint(i) + sf::Vector2f(x + 2.5f, y + 2.5f);
			foregroundShape[i] = vert;
		}

		break;
	}
}

void Cell::draw(sf::RenderWindow &window)
{
	window.draw(backgroundShape);

	if (type != 0)
	{
		window.draw(foregroundShape, fgShapeVertSize, sf::LineStrip);
	}

	isMouseClicked = false;
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
