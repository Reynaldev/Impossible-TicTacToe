#include "gamemanager.h"
#include "ai.h"
#include "modal.h"

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
	static int nextPos = 0;
	static SymbolSign nextSym = SYMBOL_SIGN_EMPTY;

	if (!isFinished)
	{
		if (nextSym != SYMBOL_SIGN_EMPTY)
		{
			if (isWinning(cells, (SymbolSign)players[currentPlayer].symbol, nextPos))
			{
				players[currentPlayer].scoreWin++;
				players[(currentPlayer + 1) % 2].scoreLose++;
				
				isFinished = true;
			}

			nextSym = SYMBOL_SIGN_EMPTY;
		}

		if (nextTurn)
		{
			currentPlayer = (currentPlayer + 1) % MAX_PLAYERS;
			nextTurn = false;
		}

		// AI
		if ((players[currentPlayer].type == PLAYER_AI))
		{
			solve(cells, (SymbolSign)players[currentPlayer].symbol, (SymbolSign)(players[(currentPlayer + 1) % 2].symbol), nextPos);
			nextSym = (SymbolSign)players[currentPlayer].symbol;

			nextTurn = true;
		}
	}

	// To keep track of filled cells
	int filledCells = 0;

	// Draw the cells
	for (int i = 0; i < 9; i++)
	{
		if (cells[i].mouseEntered())
		{
			if (cells[i].isFilled() && players[currentPlayer].type != PLAYER_HUMAN)
				cells[i].backgroundShape.setOutlineColor(sf::Color(200, 0, 0));
			else
				cells[i].backgroundShape.setOutlineColor(sf::Color::White);

			cells[i].backgroundShape.setOutlineThickness(2.5f);
		}
		else
		{
			cells[i].backgroundShape.setOutlineThickness(0.f);
		}

		if (!isFinished)
		{
			if (players[currentPlayer].type == PLAYER_HUMAN)
			{
				if (cells[i].mouseClicked() && !cells[i].isFilled())
				{
					cells[i].insertSymbol(players[currentPlayer].symbol);
					nextPos = i;
					nextSym = (SymbolSign)players[currentPlayer].symbol;

					nextTurn = true;
				}
			}

			if (cells[i].isFilled())
				filledCells++;
		}


		cells[i].draw(window);
	}

	if (!isFinished)
		isFinished = (filledCells == 9);
	else
	{
		Modal::show(window, "Win modal", players[currentPlayer].name + " win!");
	}

	if (isFinished && filledCells == 9)
	{
		printf("It's a tie!");
	}
}
