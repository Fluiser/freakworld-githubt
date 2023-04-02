#pragma once
#include <string>
#include "SFML/Graphics.hpp"

namespace Engine {
	namespace Graphics {

		class Label {
		public:
			std::string _text;	//Текст
		protected:
			double _x;		//Координата x
			double _y;		//Координата y

			sf::Text TXT;		//Отображаемый текст

		public:
			Label(sf::Font font, double x, double y, std::string text = "Текст")
			{
				_x = x;
				_y = y;
				_text = text;								// загружает текст
				TXT.setFont(font);							// загружаем фрифт
				TXT.setCharacterSize(20); 					// в пикселях, а не точках!
				TXT.setColor(sf::Color::White);					// устанавливаем цвет выводимого текста
				TXT.setPosition(x, y);						// позиция текста
			}
			sf::Text displayText()
			{
				TXT.setString(_text);						// загружаем в выводимый текст загружаемый текст
				return TXT;
			}
		};
	}
}