#include "main.h"
#include "gamemanager.h"

int main()
{
	srand(time(0));

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
	GameManager game(new Player("Player", PLAYER_HUMAN), new Player("CPU", PLAYER_AI), window);

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


		/* Player one */
		// Player name label
		txtNormal.setString(game.getPlayer(0).name);
		txtNormal.setPosition(sf::Vector2f((window.getSize().x - txtNormal.getLocalBounds().width), 0.f));

		window.draw(txtNormal);

		// Win score label
		txtNormal.setString(std::to_string(game.getPlayer(0).scoreWin) + " :Win");
		txtNormal.setPosition(sf::Vector2f((window.getSize().x - txtNormal.getLocalBounds().width), 50.f));

		window.draw(txtNormal);

		// Lose score label
		txtNormal.setString(std::to_string(game.getPlayer(0).scoreLose) + " :Lose");
		txtNormal.setPosition(sf::Vector2f((window.getSize().x - txtNormal.getLocalBounds().width), 100.f));

		window.draw(txtNormal);

		/* Player two */
		// Player name label
		txtNormal.setString(game.getPlayer(1).name);
		txtNormal.setPosition(sf::Vector2f(0.f, 0.f));

		window.draw(txtNormal);

		// Win score label
		txtNormal.setString("Win: " + std::to_string(game.getPlayer(1).scoreWin));
		txtNormal.setPosition(sf::Vector2f(0.f, 50.f));

		window.draw(txtNormal);

		// Lose score label
		txtNormal.setString("Lose: " + std::to_string(game.getPlayer(1).scoreLose));
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