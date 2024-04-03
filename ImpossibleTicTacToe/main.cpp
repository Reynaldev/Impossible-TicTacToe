#include "main.h"
#include "crossshape.h"

struct Symbol
{
	union
	{
		CrossShape crossShape;
		sf::CircleShape circleShape;
	};

	SymbolTypeFlag type;
	float x, y;

	void createCross(float posX, float posY)
	{
		this->x = posX;
		this->y = posY;
		type = SYMBOL_TYPE_CROSS;

		crossShape = CrossShape(sf::Vector2f(x, y));
	}

	void createCircle(float radius)
	{
		type = SYMBOL_TYPE_CIRCLE;

		circleShape = sf::CircleShape(radius);
	}

	void draw(sf::RenderWindow &window) const
	{
		switch (type)
		{
		case SYMBOL_TYPE_CROSS:
			crossShape.draw(window);
			break;
		case SYMBOL_TYPE_CIRCLE:
			window.draw(circleShape);
			break;
		}
	}
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Impossible TicTacToe");
	window.setVerticalSyncEnabled(true);

	CrossShape cross(sf::Vector2f(0.0f, 150.0f));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2f mousePos = (sf::Vector2f) sf::Mouse::getPosition(window);

			cross.move(mousePos);

			//lines[0].position = sf::Vector2f((float)mousePos.x - (150.0f / 2.0f), (float)mousePos.y - (150.0f / 2.0f));
			//lines[1].position = sf::Vector2f((float)mousePos.x + (150.0f / 2.0f), (float)mousePos.y + (150.0f / 2.0f));
			//lines[2].position = sf::Vector2f((float)mousePos.x + (150.0f / 2.0f), (float)mousePos.y - (150.0f / 2.0f));
			//lines[3].position = sf::Vector2f((float)mousePos.x - (150.0f / 2.0f), (float)mousePos.y + (150.0f / 2.0f));

			//line1.setPosition(mousePos.x - (line1.getSize().x / 2.0f), mousePos.y - (line1.getSize().x / 2.0f));
			//line2.setPosition(mousePos.x - (line2.getSize().x / 2.0f), mousePos.y - (line2.getSize().y / 2.0f));
		}

		window.clear();

		cross.draw(window);

		window.display();
	}

	return 0;
}