#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Label.h"

namespace Engine {
	namespace Graphics {
		class Button : Label {
		public:
			Button();

			bool select(sf::Vector2i);
			sf::Text displayText();
		sf:RectangleShape displayButton();
		protected:
			double _width;
			double _height;
			sf::RectangleShape BOX;
		};
	}
}