#include "gamemanager.h"
#include "ai.h"

GameManager::GameManager(Player *playerOne, Player *playerTwo, const sf::RenderWindow &window)
{
	SymbolSignFlag sym = rand();

	playerOne->symbol = (sym % 2);
	playerTwo->symbol = (sym + 1) % 2;

	currentPlayer = (playerTwo->symbol == SYMBOL_SIGN_CROSS);

	players[0] = *playerOne;
	players[1] = *playerTwo;

	delete playerOne;
	delete playerTwo;

	// Cell drawings
	for (int i = 0; i < 9; i++)
	{
		const static float size = 100.0f;
		const static float paddingX = (float)((window.getSize().x - size) / 3);
		const static float paddingY = (float)((window.getSize().y - size) / 3);

		float row = (float)(floor(i / 3) * 3);
		float col = (float)(row + i);


		cells[i].setPosition(
			sf::Vector2f(
				(size * fmodf(col, 3.f)) + paddingX,
				(size * (row / 3.f)) + paddingY
			)
		);

		cells[i].setSize(sf::Vector2f(size, size));
	}
}

GameManager::~GameManager()
{
	delete[] players;
}

void GameManager::eventInput(const sf::Event &event)
{
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
		{
			for (Cell &cell : cells)
				cell.reset();

			isFinished = false;
		}
	}
}

void GameManager::update(sf::RenderWindow &window)
{
	if (nextTurn)
	{
		currentPlayer = (currentPlayer + 1) % MAX_PLAYERS;
		nextTurn = false;
	}

	// AI
	if ((players[currentPlayer].type == PLAYER_AI) && (!isFinished))
	{
		solve(cells, (SymbolSign)players[currentPlayer].symbol);
		//int index = rand() % 10;

		//while (cells[index].isFilled())
		//	index = rand() % 10;

		//cells[index].insertSymbol(players[currentPlayer].symbol);

		nextTurn = true;
	}

	// To keep track of filled cells
	int filledCells = 0;

	// Draw the cells
	for (Cell &cell : cells)
	{
		if (!isFinished)
		{
			if (players[currentPlayer].type == PLAYER_HUMAN)
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
					cell.insertSymbol(players[currentPlayer].symbol);

					nextTurn = true;
				}
			}
		}

		if (cell.isFilled())
			filledCells++;

		cell.draw(window);
	}

	isFinished = (filledCells == 9);
}
