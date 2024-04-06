#include "main.h"
#include "cell.h"
#include "crossshape.h"
#include "player.h"

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
		float paddingX = (float)((window.getSize().x - size) / 3);
		float paddingY = (float)((window.getSize().y - size) / 3);

		Cell cell(
			sf::Vector2f(
				(size * fmodf(col, 3.f)) + paddingX,
				(size * (row / 3.f)) + paddingY
			),
			sf::Vector2f(size, size)
		);
		cells.push_back(cell);
	}

	// Players init
	SymbolTypeFlag randSym = (rand() % 2) + 1;

	// Player
	Player player("Dummy", (SymbolType)randSym, (PlayerType) PLAYER_HUMAN);

	// CPU
	Player cpu("CPU", (SymbolType)randSym, (PlayerType) PLAYER_AI);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				exit(0);
			}

			if (event.type == sf::Event::MouseMoved)
				for (Cell &cell : cells)
					cell.onMouseEntered(event);

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
					for (Cell &cell : cells)
						cell.onMouseButtonClicked(event);
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.scancode == sf::Keyboard::Scan::R)
					for (Cell &cell : cells)
						cell.reset();
			}
		}

		window.clear(sf::Color(200, 200, 200));

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

			if (cell.mouseClicked() && !cell.isFilled())
			{
				cell.insertSymbol(player.symbol);
			}

			cell.draw(window);
		}

		window.display();
	}

	return 0;
}