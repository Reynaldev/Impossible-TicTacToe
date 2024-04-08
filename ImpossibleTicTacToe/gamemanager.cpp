#include "gamemanager.h"

GameManager::GameManager(Player *playerOne, Player *playerTwo, const sf::RenderWindow &window)
{
	players[0] = *playerOne;
	players[1] = *playerTwo;

	currentPlayer = 0;

	delete playerOne;
	delete playerTwo;

	// Cell drawings
	for (int i = 0; i < 9; i++)
	{
		float row = (float)(floor(i / 3) * 3);
		float col = (float)(row + i);

		int randColor = rand() % 256;

		float size = 100.0f;
		float paddingX = (float)((window.getSize().x - size) / 3);
		float paddingY = (float)((window.getSize().y - size) / 3);

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
			for (Cell &cell : cells)
				cell.reset();
	}
}

void GameManager::nextTurn()
{
	currentPlayer = (currentPlayer + 1) % MAX_PLAYERS;
}

void GameManager::update(sf::RenderWindow &window)
{
	for (Cell &cell : cells)
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
				nextTurn();
			}
		}

		cell.draw(window);
	}
}
