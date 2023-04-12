#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <System/Util.hpp>
#include <cmath>
#include <memory>

namespace {
	constexpr float PID6 = (float)(M_PI / 6.0f); // Pi divided by 6
	constexpr float PID2 = (float)(M_PI / 2.0f);
	sf::String _str_space(" ");
}

namespace Engine {
	namespace Graphics {

		class String: public sf::Drawable {
		public:
			class _proxy_colors {
				friend String;
				typedef std::shared_ptr<sf::Color[]> ptr;
			public:
				ptr _colors{};
				size_t _size = 0;

				_proxy_colors() {}

				_proxy_colors(ptr colors, size_t size): _colors(colors), _size(size) {}

				template<int N>
				_proxy_colors(const sf::Color(&colors)[N])
				{
					_size = (sizeof(colors) / sizeof(colors[0]));
					_colors = std::make_shared<sf::Color[]>(_size);
					
					for (size_t i = 0; i < _size; ++i)
						_colors[i] = colors[i];
				}

				_proxy_colors(const _proxy_colors&) = default;
			}; // Мне не нравится. Переделай.

		protected:

			unsigned _charSize = 12;
			float _ampl = 0; // амплитуда
			float _stage = 0; // фаза
			std::vector<sf::Text> _particles;
			sf::Vector2f _position;
			int _type;
			sf::Font _font;

			sf::Clock _timer_Rainbow;
			sf::Clock _timer_Bounce;

			_proxy_colors _color_set{};
			int _color_offset = 0;
		public:
			static sf::Font _default_font;

			enum TYPE : int {
				RAINBOW = 1,
				WAVE = 1 << 1,
				CHAOS = 1 << 2,
				BOUNCE = 1 << 3,
				INTERTIAL_BOUNCE = 1 << 4
			};

			String(String&&) = default;
			String(const String&) = default;
			String(float ampligute, sf::Vector2f pos, int type = 0, sf::Font font = _default_font);

			void setPosition(sf::Vector2f);
			void setAmplitude(float);
			void setCharSize(unsigned);

			void setColorSet(_proxy_colors::ptr, size_t);
			template<size_t N>
			void setColorSet(const sf::Color (&arr)[N])
			{
				_color_set = _proxy_colors(arr);
			}

			void setFillColor(sf::Color); 

			void changeStage(float);
			void setStage(float);
			const float& getStage();

			void add(sf::Text);
			void add(sf::String);

			void normalize(); // Необходимо для синхронизации относительно времени.
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		};

	}
}