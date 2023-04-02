#pragma once
#include <SFML/Graphics.hpp>
#include "CompoundTextArea.hpp"


namespace Engine {
	namespace Graphics {
		namespace TextAreas {
			CompoundTextArea::CompoundTextArea(sf::Font font, sf::Vector2i position) : BaseTextArea(font, position) {}

			void CompoundTextArea::add(std::string str, sf::Color color , sf::Text::Style style ) {
				sf::Text text;
				text.setString(str);
				text.setCharacterSize(charSize);
				text.setStyle(style);
				text.setFont(_font);
				text.setFillColor(color);

				if(str[0] != '\n')
					text.setPosition((sf::Vector2f)(position + offset));
				else
					text.setPosition(sf::Vector2f(position.x, position.y + text.getLocalBounds().height));

				offset.x += text.getLocalBounds().width;
				parts.emplace_back(text);
			}
		};
	}
}