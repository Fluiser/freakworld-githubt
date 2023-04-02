#pragma once
#include <System/Window.h>
#include <SFML/Graphics.hpp>

namespace Engine {

	namespace Graphics {
		namespace TextAreas {
			class BaseTextArea
			{
			protected:

			public:
				BaseTextArea(sf::Font, sf::Vector2i);
				~BaseTextArea();

				void setCharacterSize(int);
				virtual void render(Engine::Window& window, const Scene::Scene& scene) const;
				virtual void clear();

				void setPosition(float x, float y);
			protected:
				std::vector<sf::Text> parts;
				sf::Vector2i offset = { 0,0 };
				sf::Vector2i position = {};
				int charSize = 16;
				sf::Font _font;
			};
		}
	}
}