#pragma once
#include "BaseTextArea.hpp"
#include <SFML/Graphics.hpp>
#include <string>

namespace Engine {
	namespace Graphics {
		namespace TextAreas {
			class CompoundTextArea : public BaseTextArea
			{
			public:
				CompoundTextArea(sf::Font, sf::Vector2i);

				void add(std::string str, sf::Color color = sf::Color::White, sf::Text::Style style = sf::Text::Bold);
				using BaseTextArea::render;
				using BaseTextArea::clear;

			};
		}
	}
}