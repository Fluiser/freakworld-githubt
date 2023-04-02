#pragma once
#include "BaseTextArea.hpp"

namespace Engine {
	namespace Graphics {
		namespace TextAreas {
			class DancingTextArea : public BaseTextArea {
			public:
				DancingTextArea(sf::Font font, sf::Vector2i pos, std::shared_ptr<sf::Color[]> colors, int colorCount);

				void add(std::string str, sf::Text::Style style = sf::Text::Bold);
				void setAmplitude(float);
				void setStep(float);
				void render(Engine::Window& window, const Scene::Scene& scene) const override;
				using BaseTextArea::clear;
			private:
				inline static constexpr float offsetX = 0.52359f;
				float amplitude = 1.0f;
				float step = 0;
				std::shared_ptr< sf::Color[]> _colors;
				int _colorsCount;
			};
		}
	}
}