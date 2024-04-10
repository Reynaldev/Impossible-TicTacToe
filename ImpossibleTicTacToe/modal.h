#pragma once

#include "main.h"

namespace Modal
{
	struct Modal
	{
		bool modalActive;
		sf::RectangleShape mShape;
		sf::Font mFont;
		sf::Text mText;
		std::string mTitle;
	};

	static void show(sf::RenderWindow &window, const std::string &title, const std::string &text)
	{
		static Modal modal;

		modal.modalActive = true;

		if (!modal.mFont.loadFromFile("assets/fonts/Minecraft.ttf"))
		{
			printf("Cannot load the font file for modal\n");
			return;
		}

		modal.mText.setFont(modal.mFont);
		modal.mText.setString(text);
		modal.mText.setCharacterSize(18);

		modal.mShape.setSize(sf::Vector2f(250.f, modal.mText.getLocalBounds().height + 10.f));
		modal.mShape.setPosition(((sf::Vector2f)window.getSize() - modal.mShape.getSize()) / 2.f);
		modal.mShape.setFillColor(sf::Color(200, 200, 200));
		modal.mShape.setOutlineThickness(5.f);
		modal.mShape.setOutlineColor(sf::Color::White);

		modal.mText.setPosition(
			sf::Vector2f(
				((modal.mShape.getPosition().x + modal.mShape.getSize().x) / 2.f) + modal.mText.getLocalBounds().width,
				modal.mShape.getPosition().y
			)
		);

		window.draw(modal.mShape);
		window.draw(modal.mText);
	}

};

