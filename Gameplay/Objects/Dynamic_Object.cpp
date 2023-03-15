#pragma once
#include "Dynamic_Object.h"
#include <System/Window.h>

namespace Engine
{
	namespace Objects
	{
		Dynamic_Object::Dynamic_Object(): Object() {}

		sf::Vector2f Dynamic_Object::getSize() const
		{
			auto s = this->sprite.getScale();
			auto size = this->texture->getSize();
			return sf::Vector2f((float)(size.x * s.x), (float)(size.y * s.y));
		}

		void Dynamic_Object::normalize(const Engine::Window& window, const Scene::Scene& scene)
		{
			sf::Vector2i windowSize(window.getSize().x / 2, window.getSize().y / 2 + 1);
			this->sprite.setPosition(
				(sf::Vector2f)windowSize - sf::Vector2f(scene.offset.x, -scene.offset.y) + scene.getPositionf(this->gpos));
		}

		void Dynamic_Object::render(Engine::Window &window, const Scene::Scene &scene) const
		{
			{
				sf::Vector2f size((float)window.getSize().x, (float)window.getSize().y);

				if (!this->canView(sf::Vector2f(0, 0), size))
					return;
			}
			window.draw(this->sprite);
		}

		void Dynamic_Object::setScale(sf::Vector2f vec)
		{
			this->sprite.setScale(vec);
		}

		void Dynamic_Object::setScale(float scale)
		{
			auto size = texture->getSize();
			sprite.setScale(scale / (size.x), scale / (size.y));
		}

		bool Dynamic_Object::canView(sf::Vector2f scene_start, sf::Vector2f scene_end) const
		{
			auto pos = this->sprite.getPosition();
			auto size = this->getSize();
			Math::vec2f end{pos.x + size.x, pos.y + size.y};
			if (end.x < scene_start.x ||
				end.y < scene_start.y)
				return false;
			if (pos.x > scene_end.x ||
				pos.y > scene_end.y)
				return false;
			return true;
		}

		void Dynamic_Object::loadFromFile(const std::string& path)
		{
			this->texture = std::make_shared<sf::Texture>();
			this->texture->loadFromFile(path);
			this->sprite.setTexture(*this->texture);
		}

		void Dynamic_Object::move(Math::vec2f vec)
		{
			this->sprite.move(vec.x, vec.y);
		}

		bool Dynamic_Object::inObject(Math::vec2f point) const
		{
			auto pos = this->sprite.getPosition();
			auto end = this->getSize() + pos;
			return point.x >= pos.x && point.x <= end.x &&
				   point.y >= pos.y && point.y <= end.y;
		}

	}
}