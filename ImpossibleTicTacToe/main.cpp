#include "main.h"
#include "crossshape.h"

struct Cell
{
	sf::RectangleShape shape;

	SymbolTypeFlag type;
	float x, y, w, h;

	Cell() {}

	Cell(sf::Vector2f pos, sf::Vector2f size)
	{
		x = pos.x + 2.5f;
		y = pos.y + 2.5f;
		w = size.x - 2.5f;
		h = size.y - 2.5f;

		shape.setSize(sf::Vector2f(w, h));
		shape.setPosition(sf::Vector2f(x, y));
		shape.setFillColor(sf::Color(150, 150, 150));
		shape.setOutlineColor(sf::Color::White);

		//printf("X: %.1f\tY: %.1f\n", x, y);
		//printf("Shape X: %.1f\tShape Y: %.1f\n", shape.getPosition().x, shape.getPosition().y);
		//printf("W: %.1f\tH: %.1f\n", w, h);
		//printf("Shape W: %.1f\tShape H: %.1f\n", shape.getSize().x, shape.getSize().y);
	}

	void setPosition(sf::Vector2f pos)
	{
		x = pos.x;
		y = pos.y;

		shape.move(pos);
	}

	void onMouseEntered(const sf::Event &e)
	{
		sf::Vector2f mousePos((float)e.mouseMove.x, (float)e.mouseMove.y);

		if (mousePos.x > x
			&& mousePos.x < (x + w)
			&& mousePos.y > y
			&& mousePos.y < (y + h))
		{
			shape.setOutlineThickness(2.5f);
		}
		else
		{
			shape.setOutlineThickness(0.f);
		}

		//printf("Mouse:\n\tX: %.1f\tY: %.1f\n", mousePos.x, mousePos.y);
	}

	void onMouseButtonClicked(const sf::Event &e)
	{
		sf::Vector2f mousePos((float)e.mouseButton.x, (float)e.mouseButton.y);

		if (mousePos.x > x
			&& mousePos.x < (x + w)
			&& mousePos.y > y
			&& mousePos.y < (y + h))
		{
			shape.setFillColor(sf::Color(50, 50, 50));
		}
		else
		{
			shape.setFillColor(sf::Color(150, 150, 150));
		}
	}

	void draw()
	{

	}

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

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Impossible TicTacToe");
	window.setVerticalSyncEnabled(true);

	std::vector<Cell> cells;

	for (int i = 0; i < 9; i++)
	{
		float row = (float)(floor(i / 3) * 3);
		float col = (float)(row + i);

		int randColor = rand() % 256;

		float size = 100.0f;
		float paddingX = (float)(window.getSize().x / 3);
		float paddingY = (float)(window.getSize().y / 3);

		Cell cell(
			sf::Vector2f(
				(size * fmodf(col, 3.f)) + paddingX,
				(size * (row / 3.f)) + paddingY
			),
			sf::Vector2f(size, size)
		);
		cells.push_back(cell);
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseMoved)
				for (Cell &cell : cells)
				{
					cell.onMouseEntered(event);
				}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
					for (Cell &cell : cells)
						cell.onMouseButtonClicked(event);
			}
		}

		window.clear(sf::Color(200, 200, 200));

		//cross.draw(window);

		for (Cell &cell : cells)
		{
			window.draw(cell.shape);
		}

		window.display();
	}

	return 0;
}