#include "main.h"
#include "cell.h"
#include "crossshape.h"

struct Player
{
public:
	SymbolTypeFlag symbol;
	char name[8];

	Player(const char *username, SymbolTypeFlag type)
	{
		this->symbol = type;
		memcpy_s(this->name, sizeof(this->name), username, sizeof(char) * 8);
	}
};

int main()
{
	// Init
	// Wwndow
	sf::RenderWindow window(sf::VideoMode(800, 600), "Impossible TicTacToe", sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	// Cell drawings
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

	// Player
	Player player("Dummy", SYMBOL_TYPE_CIRCLE);

	// CPU

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
			if (cell.mouseEntered())
			{
				if (cell.isFilled())
					cell.backgroundShape.setOutlineColor(sf::Color(200, 0, 0));
				else
					cell.backgroundShape.setOutlineColor(sf::Color::White);

				cell.backgroundShape.setOutlineThickness(2.5f);
			}
			else
			{
				cell.backgroundShape.setOutlineThickness(0.f);
			}

			if (cell.mouseClicked())
			{
				//cell.backgroundShape.setFillColor(sf::Color(50, 50, 50));
				cell.insertSymbol(player.symbol);
			}
			else
			{
				//cell.backgroundShape.setFillColor(sf::Color(150, 150, 150));
			}

			cell.draw(window);
		}

		window.display();
	}

	return 0;
}