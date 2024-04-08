#include "main.h"
#include "gamemanager.h"

int main()
{
	// Init
	// Window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Impossible TicTacToe", sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	// UI
	// Font
	sf::Font font;
	if (!font.loadFromFile("assets/fonts/Minecraft.ttf"))
	{
		printf("Cannot load font file\n");
		return 1;
	}

	sf::Text txtBig, txtNormal;

	txtBig.setFont(font);
	txtNormal.setFont(font);

	txtBig.setCharacterSize(32);
	txtNormal.setCharacterSize(24);

	txtBig.setFillColor(sf::Color::White);
	txtNormal.setFillColor(sf::Color::White);

	// Players init
	SymbolTypeFlag randSym = (rand() % 2) + 1;

	GameManager game(new Player("Dummy", (SymbolType)randSym, PLAYER_HUMAN), new Player("CPU", (SymbolType)randSym, PLAYER_AI), window);

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

			game.eventInput(event);
		}

		window.clear(sf::Color(200, 200, 200));

		game.update(window);

		// Win score label
		txtNormal.setString("Win: " + std::to_string(game.getWinScore()));
		txtNormal.setPosition(sf::Vector2f(0.f, 0.f));

		window.draw(txtNormal);

		// Tie score label
		txtNormal.setString("Tie: " + std::to_string(game.getTieScore()));
		txtNormal.setPosition(sf::Vector2f(0.f, 50.f));

		window.draw(txtNormal);

		// Lose score label
		txtNormal.setString("Lose: " + std::to_string(game.getLoseScore()));
		txtNormal.setPosition(sf::Vector2f(0.f, 100.f));

		window.draw(txtNormal);

		// Player's turn text label
		txtBig.setString("It's " + std::string(game.getCurrentPlayer().name) + "'s turn");
		txtBig.setPosition(
			sf::Vector2f(((window.getSize().x - txtBig.getLocalBounds().width) / 2.f) - 15.f, 0.f)
		);
		
		window.draw(txtBig);

		window.display();
	}

	return 0;
}