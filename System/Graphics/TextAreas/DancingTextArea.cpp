#pragma once
#include "DancingTextArea.hpp"
#include <math.h>
#include <System/Window.h>

namespace Engine {
	namespace Graphics {
		namespace TextAreas {

			DancingTextArea::DancingTextArea(sf::Font font, sf::Vector2i pos, std::shared_ptr<sf::Color[]> colors, int colorCount) : BaseTextArea(font, pos) {
				_colors = colors;
				_colorsCount = colorCount;
			}

			void DancingTextArea::setAmplitude(float new_amplitude) {
				amplitude = new_amplitude;
			}

			void DancingTextArea::setStep(float new_step) {
				step = new_step;
			}

			void DancingTextArea::add(std::string str, sf::Text::Style style) {
				sf::Text text;
				text.setString(str);
				text.setCharacterSize(charSize);
				text.setStyle(style);
				text.setFont(_font);

				if (str[0] != '\n')
					text.setPosition((sf::Vector2f)(position + offset));
				else
					text.setPosition(sf::Vector2f(position.x, position.y + text.getLocalBounds().height));

				offset.x += text.getLocalBounds().width;
				parts.emplace_back(text);
			}

			void DancingTextArea::render(Engine::Window& window, const Scene::Scene& scene) const {
				int i = 0;
				for (const auto& it : parts) {
					++i;
					sf::Vector2f prev_pos = it.getPosition();
					auto* _it = const_cast<sf::Text*>(&it);
					_it->setPosition(sf::Vector2f(prev_pos.x, prev_pos.y + sinf(offsetX + (step * _colorsCount + i)) * amplitude * charSize));
					_it->setColor(_colors[((int)(step * _colorsCount / 2.0f) + i) % _colorsCount]);
					window.draw(it);

					_it->setPosition(prev_pos);
				}
			}
		}
	}
}