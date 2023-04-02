#pragma once
#include <SFML/Graphics.hpp>

namespace Scene {
	class Scene;
}

namespace Engine {
	class Window;
	namespace Graphics {
		namespace TextAreas {
			class BaseTextArea
			{
			public:
				BaseTextArea(sf::Font, sf::Vector2i);
				~BaseTextArea();

				void setCharacterSize(int);
				virtual void render(Engine::Window& window, const Scene::Scene& scene) const;
				void clear();

				void setPosition(float x, float y);

				sf::Text& operator[](int i);

				size_t getLength() const;
			protected:
				std::vector<sf::Text> parts;
				sf::Vector2i offset = { 0,0 };
				sf::Vector2i position = {};
				int charSize = 72;
				sf::Font _font;
			};
		}
	}
}