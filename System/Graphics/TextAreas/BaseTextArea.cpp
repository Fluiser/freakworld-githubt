#pragma once
#include <SFML/Graphics.hpp>
#include "BaseTextArea.hpp"
#include <iostream>
#include <System/Window.h>

namespace Engine {
	namespace Graphics {
		namespace TextAreas {

			BaseTextArea::BaseTextArea(sf::Font font, sf::Vector2i pos) {
				_font = font;
				position = pos;
			}
			BaseTextArea::~BaseTextArea() {}

			void BaseTextArea::setCharacterSize(int size) {
				charSize = size;
			}

			void BaseTextArea::clear() {
				parts.clear();
			}

			void BaseTextArea::setPosition(float x, float y) {
				for (auto it = parts.begin(); it != parts.end(); it++) {
					sf::Vector2f prev_pos = (*it).getPosition();
					(*it).setPosition(sf::Vector2f(prev_pos.x - position.x + x, prev_pos.y - position.y + y));
				}
			}

			 void BaseTextArea::render(Engine::Window& window, const Scene::Scene& scene) const {
				for (auto& it: parts) {
					window.draw(it);
				}
			};

			size_t BaseTextArea::getLength() const
			{
				return parts.size();
			}

			sf::Text& BaseTextArea::operator[](int i)
			{
				return parts[i];
			}
		}
	}
}