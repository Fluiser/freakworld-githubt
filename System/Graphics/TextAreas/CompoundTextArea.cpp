#pragma once
#include <SFML/Graphics.hpp>
#include "CompoundTextArea.h"

namespace Engine {
	namespace Graphics {
		namespace TextAreas {
			CompoundTextArea::CompoundTextArea(sf::Font font, sf::Vector2i position) : BaseTextArea(font, position) {}

			void CompoundTextArea::add(std::string str, sf::Color color = sf::Color::White, sf::Text::Style style = sf::Text::Regular) {
				sf::Text text;
				text.setString(str);
				text.setCharacterSize(charSize);
				text.setStyle(style);
				text.setFillColor(color);
				text.setPosition((sf::Vector2f)(position + offset));

				offset.x += text.getLocalBounds().width;
			}
		};
	}
}