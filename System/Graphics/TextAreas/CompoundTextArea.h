#pragma once
#include "BaseTextArea.h"
#include <SFML/Graphics.hpp>
#include <string>

namespace Engine {
	namespace Graphics {
		namespace TextAreas {
			class CompoundTextArea : public BaseTextArea
			{
			public:
				CompoundTextArea(sf::Font, sf::Vector2i);

				void add(std::string str, sf::Color color, sf::Text::Style style);
				void render(Engine::Window&, const Scene::Scene&) const;
			};
		}
	}
}