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
		x = pos.x;
		y = pos.y;
		w = size.x;
		h = size.y;

		shape.setSize(size);
		shape.setPosition(pos);
		shape.setFillColor(sf::Color::White);

		printf("X: %.1f\tY: %.1f\n", x, y);
		printf("Shape X: %.1f\tShape Y: %.1f\n", shape.getPosition().x, shape.getPosition().y);
		printf("W: %.1f\tH: %.1f\n", w, h);
		printf("Shape W: %.1f\tShape H: %.1f\n", shape.getSize().x, shape.getSize().y);
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
			shape.setOutlineThickness(5.f);
			shape.setOutlineColor(sf::Color::Blue);
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
			printf("Square at X: %.1f Y: %.1f\n", x, y);
			shape.setFillColor(sf::Color(50, 50, 50));
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

	//CrossShape cross(sf::Vector2f(0.0f, 150.0f));

	std::vector<Cell> cells;

	for (int i = 0; i < 9; i++)
	{
		float row = (float)(floor(i / 3) * 3);
		float col = (float)(row + i);

		int randColor = rand() % 256;

		Cell cell(sf::Vector2f(50.f * fmodf(col, 3), 50.f * (row / 3.f)), sf::Vector2f(50.f, 50.f));
		cell.shape.setFillColor(sf::Color(randColor, randColor, randColor));
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
				for (Cell cell : cells)
					cell.onMouseEntered(event);

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
					for (Cell cell : cells)
						cell.onMouseButtonClicked(event);
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2f mousePos = (sf::Vector2f) sf::Mouse::getPosition(window);

			//cross.move(mousePos);

			//lines[0].position = sf::Vector2f((float)mousePos.x - (150.0f / 2.0f), (float)mousePos.y - (150.0f / 2.0f));
			//lines[1].position = sf::Vector2f((float)mousePos.x + (150.0f / 2.0f), (float)mousePos.y + (150.0f / 2.0f));
			//lines[2].position = sf::Vector2f((float)mousePos.x + (150.0f / 2.0f), (float)mousePos.y - (150.0f / 2.0f));
			//lines[3].position = sf::Vector2f((float)mousePos.x - (150.0f / 2.0f), (float)mousePos.y + (150.0f / 2.0f));

			//line1.setPosition(mousePos.x - (line1.getSize().x / 2.0f), mousePos.y - (line1.getSize().x / 2.0f));
			//line2.setPosition(mousePos.x - (line2.getSize().x / 2.0f), mousePos.y - (line2.getSize().y / 2.0f));
		}

		window.clear();

		//cross.draw(window);

		for (Cell cell : cells)
		{
			window.draw(cell.shape);
		}

		window.display();
	}

	return 0;
}