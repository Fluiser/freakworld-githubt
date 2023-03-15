#pragma once
#include "Static_Object.h"
#include <System/Window.h>

namespace Engine 
{
    namespace Objects {
		BoxForm::BoxForm() {}

		void BoxForm::normalize(const Engine::Window& window, const Scene::Scene& scene)
		{
			sf::Vector2i windowSize(window.getSize().x/2, window.getSize().y/2 + 1);
			this->sprite.setPosition(
					(sf::Vector2f)windowSize - sf::Vector2f(scene.offset.x, -scene.offset.y) + scene.getPositionf(this->gpos)
					);
		}

		bool BoxForm::canView(sf::Vector2f scene_start, sf::Vector2f scene_end) const
		{
			auto pos = sprite.getPosition();
			sf::Vector2f size(texture->getSize().x * sprite.getScale().x,
							texture->getSize().y * sprite.getScale().y);
			Math::vec2f end{ pos.x + size.x, pos.y + size.y };
			if (end.x < scene_start.x ||
				end.y < scene_start.y) return false;
			if (pos.x > scene_end.x ||
				pos.y > scene_end.y) return false;
			return true;
		}

		bool BoxForm::inObject(Math::vec2f vec) const 
		{
			auto pos = this->sprite.getPosition();
			auto size = this->getSize();

			return (vec.x >= pos.x && vec.x <= (pos.x + size.x) &&
					vec.y >= pos.y && vec.y <= (pos.y + size.y));
			return 0;
		}

        
		sf::Vector2f BoxForm::getSize() const
		{
			auto s = this->sprite.getScale();
			auto size = this->texture->getSize();
			return sf::Vector2f((float)(size.x * s.x), (float)(size.y * s.y));
		}
    }
}