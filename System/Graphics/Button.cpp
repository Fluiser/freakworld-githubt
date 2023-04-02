#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Label.h"

namespace Engine {
	namespace Graphics {

		class Button : public Label {
		protected:
			double _width;		// ������ ������
			double _height;		// ������ ������
			sf::RectangleShape BOX;	// ������� ������������� � �������� width, height
		public:
			Button(double x, double y, double width, double height, sf::Font font, std::string text = "������")
			{

				_x = x;
				_y = y;
				_width = width;
				_height = height;
				_text = text;								// ��������� �����
				TXT.setFont(font);							// ��������� �����
				TXT.setCharacterSize(20); 					// � ��������, � �� ������!
				TXT.setColor(sf::Color::White);					// ������������� ���� ���������� ������
				TXT.setPosition(x, y);						// ������� ������

				BOX.setSize(sf::Vector2f(width, height));		// ������ ������
				BOX.setPosition(x, y);						// ���������� ������
				BOX.setFillColor(sf::Color(133, 133, 133));	// ���� ������
				BOX.setOutlineThickness(2);					// ������ X ��������
				BOX.setOutlineColor(sf::Color(66, 66, 66));		// ���� �������
			}
			//�������� ������� �� ������
			bool select(sf::Vector2i _mouse)
			{
				return  (_mouse.x > _x && _mouse.x < _x + _width) && (_mouse.y > _y && _mouse.y < _y + _height);
			}
			//����� ������
			sf::Text displayText()
			{
				TXT.setString(_text);  // ��������� � ��������� ����� ����������� �����
				return TXT;
			}
			//����� ������
			sf::RectangleShape displayButton()
			{
				return BOX;
			}
		};
	}

}