#pragma once
#include <string>
#include "SFML/Graphics.hpp"

namespace Engine {
	namespace Graphics {
		class Label {
		public:
			Label();

			sf::Text displayText();
		protected:
			double _x;
			double _y;
			std::string _text;
			sf::Text TXT;
		};
	}
}