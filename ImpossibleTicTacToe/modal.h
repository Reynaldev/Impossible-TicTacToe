#pragma once

#include "main.h"

namespace Modal
{
	enum ModalButton
	{
		MODAL_NO_BUTTON = 0,
		MODAL_OK_BUTTON = 1 << 0
	};

	struct Modal
	{
		bool modalActive;
		sf::RectangleShape mShape;
		sf::Font mFont;
		sf::Text mText;
		std::string mTitle;

		Modal()
		{
			if (!mFont.loadFromFile("assets/fonts/Minecraft.ttf"))
			{
				printf("Cannot load the font file for modal\n");
				return;
			}

			mText.setFont(this->mFont);
			mText.setCharacterSize(18);

			mShape.setFillColor(sf::Color(200, 200, 200));
			mShape.setOutlineThickness(5.f);
			mShape.setOutlineColor(sf::Color::White);
		}
	} static modal;

	static void show(sf::RenderWindow &window, const std::string &title, const std::string &text)
	{
		if (title != modal.mTitle)
		{
			modal.modalActive = true;

			modal.mText.setString(text);

			sf::Vector2f shapeSize(250.f, modal.mText.getLocalBounds().height + 10.f);

			if ((modal.mText.getLocalBounds().width > shapeSize.x) || (modal.mText.getLocalBounds().height > shapeSize.y))
			{
				shapeSize = modal.mText.getLocalBounds().getSize();

				// Padding
				shapeSize.x += 10.f;
				shapeSize.y += 10.f;
			}

			modal.mShape.setSize(shapeSize);
			modal.mShape.setPosition(((sf::Vector2f)window.getSize() - modal.mShape.getSize()) / 2.f);

			modal.mText.setPosition(
				sf::Vector2f(
					((modal.mShape.getPosition().x + modal.mShape.getSize().x) / 2.f) + modal.mText.getLocalBounds().width,
					modal.mShape.getPosition().y
				)
			);
		}

		window.draw(modal.mShape);
		window.draw(modal.mText);
	}

};

