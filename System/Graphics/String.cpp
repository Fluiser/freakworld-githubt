#include "String.hpp"

namespace Engine {
	namespace Graphics {

		sf::Font String::_default_font{};

		String::String(	float ampligute,
						sf::Vector2f pos,
						int type, 
						sf::Font font): _ampl(ampligute/2),
										_position(pos),
										_type(type)
		{
			if (_default_font.getInfo().family.empty()) {
				_default_font = font;
			} else if (font.getInfo().family.empty()) {
				font = String::_default_font;
			}
			this->_font = font;
		}

		void String::setCharSize(unsigned s)
		{
			_charSize = s;
			if(_particles.size())
			{
				auto it = _particles.begin();
				it->setCharacterSize(s);
				++it;
				for(auto& p: _particles)
				{
					it->setCharacterSize(s);
					it->setPosition(p.getLocalBounds().width + p.getPosition().x, _position.y);
					++it;
					if(it == _particles.end()) break;
				}
			}
		}

		void String::add(sf::String str)
		{
			bool is_space = false;
			for (const auto& s : str) 
			{
				sf::Text text(s, _font, _charSize);
				if (_particles.empty()) {
					text.setPosition(_position);
				} else {
					float offx = 	_particles.back().getPosition().x +
									_particles.back().getLocalBounds().width;
					text.setPosition(offx, _position.y);
				}
				_particles.emplace_back(text);
			}
		}

		void String::add(sf::Text text)
		{
			for (const auto& s : text.getString())
			{
				sf::Text ctxt(sf::String(s), (text.getFont() == nullptr ? _font : *text.getFont()), text.getCharacterSize());
				if (_particles.empty()) {
					text.setPosition(_position);
				} else {
					float offx = 	_particles.back().getPosition().x +
									_particles.back().getLocalBounds().width;
					text.setPosition(offx, _position.y);
				}
				_particles.emplace_back(ctxt);
			}
		}

		void String::normalize()
		{
			if (_type & RAINBOW && _color_set._size > 0 && _timer_Rainbow.getElapsedTime().asMilliseconds() >= 250)
			{
				if(++_color_offset >= _color_set._size) _color_offset = 0;
				for (int idx = 0, icolor = _color_offset; idx < _particles.size(); ++idx, ++icolor)
				{
					if (icolor >= _color_set._size) icolor = 0;
					_particles[idx].setFillColor(_color_set._colors[icolor]);
				}
				
				_timer_Rainbow.restart();
			}
			if (_type & WAVE || _type & CHAOS)
			{
				float cf = ((float)_timer_Bounce.getElapsedTime().asMilliseconds()/450.0f);
				bool wave = _type & WAVE;
				bool chaos = _type & CHAOS;
				
				if (wave)
					_stage += (M_PI * cf);
				if (chaos)
					_stage += (M_PI * cf);

				float dub_stage = _stage;
				for (auto& txt : _particles)
				{
					if(txt.getString() == _str_space) continue;
					auto pos = txt.getPosition();
					txt.setPosition(pos.x, _position.y + (sinf(dub_stage) * _ampl));

					if (wave)
						dub_stage += (PID6);
					if (chaos)
						dub_stage += (M_PI);
				}

				_timer_Bounce.restart();
			}
					//CHAOS = 1 << 2
		}

		void String::setFillColor(sf::Color color)
		{
			for (auto& p : _particles)
				p.setFillColor(color);
		}

		//@----- SETTERS

		void String::setColorSet(_proxy_colors::ptr ptr, size_t n)
		{
			_color_set = _proxy_colors(ptr, n);
		}

		void String::setPosition(sf::Vector2f pos)
		{
			_position = pos;
		}

		void String::setAmplitude(float a)
		{
			_ampl = a/2;
		}

		void String::setStage(float f)
		{
			_stage = f;
		}

		void String::changeStage(float f)
		{
			_stage += f;
		}

		//@----- GETTERS

		const float& String::getStage()
		{
			return _stage;
		}

		//yes
		void String::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			for (const auto& p : _particles)
				target.draw(p);
		}
	}
}