#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Label.h"

namespace Engine {
	namespace Graphics {

		class Button : public Label {
		protected:
			double _width;		// Ширина Кнопки
			double _height;		// Высота Кнопки
			sf::RectangleShape BOX;	// Создаем прямоугольник с размером width, height
		public:
			Button(double x, double y, double width, double height, sf::Font font, std::string text = "Кнопка")
			{

				_x = x;
				_y = y;
				_width = width;
				_height = height;
				_text = text;								// загружает текст
				TXT.setFont(font);							// загружаем фрифт
				TXT.setCharacterSize(20); 					// в пикселях, а не точках!
				TXT.setColor(sf::Color::White);					// устанавливаем цвет выводимого текста
				TXT.setPosition(x, y);						// позиция текста

				BOX.setSize(sf::Vector2f(width, height));		// размер кнопки
				BOX.setPosition(x, y);						// координаты кнопки
				BOX.setFillColor(sf::Color(133, 133, 133));	// цвет кнопки
				BOX.setOutlineThickness(2);					// Контур X пикселей
				BOX.setOutlineColor(sf::Color(66, 66, 66));		// Цвет контура
			}
			//Проверка нажатия на кнопку
			bool select(sf::Vector2i _mouse)
			{
				return  (_mouse.x > _x && _mouse.x < _x + _width) && (_mouse.y > _y && _mouse.y < _y + _height);
			}
			//Вывод Текста
			sf::Text displayText()
			{
				TXT.setString(_text);  // загружаем в выводимый текст загружаемый текст
				return TXT;
			}
			//Вывод кнопки
			sf::RectangleShape displayButton()
			{
				return BOX;
			}
		};
	}

}