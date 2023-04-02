#pragma once
#include <string>
#include "SFML/Graphics.hpp"

namespace Engine {
	namespace Graphics {

		class Label {
		public:
			std::string _text;	//�����
		protected:
			double _x;		//���������� x
			double _y;		//���������� y

			sf::Text TXT;		//������������ �����

		public:
			Label(sf::Font font, double x, double y, std::string text = "�����")
			{
				_x = x;
				_y = y;
				_text = text;								// ��������� �����
				TXT.setFont(font);							// ��������� �����
				TXT.setCharacterSize(20); 					// � ��������, � �� ������!
				TXT.setColor(sf::Color::White);					// ������������� ���� ���������� ������
				TXT.setPosition(x, y);						// ������� ������
			}
			sf::Text displayText()
			{
				TXT.setString(_text);						// ��������� � ��������� ����� ����������� �����
				return TXT;
			}
		};
	}
}