#pragma once
#include "Static_Object.h"
#include <System/Window.h>

namespace Engine
{
	namespace Objects
	{

		Static_Object::Static_Object() : Object() {}

		void Static_Object::normalize(const Engine::Window& window, const Scene::Scene& scene)
		{
			for (auto &box : this->form)
			{
				box.normalize(window, scene);
			}
		}

		bool Static_Object::canView(sf::Vector2f scene_start, sf::Vector2f scene_end) const
		{
			for (const auto &box : form)
			{
				if (box.canView(scene_start, scene_end))
					return true;
			}
			return false;
		}

		bool Static_Object::inObject(Math::vec2f vec)
		{
			for (const auto &box : this->form)
			{
				if (box.inObject(vec))
					return true;
			}
			return false;
		}

		void Static_Object::setScale(float scale)
		{
			for (auto &box : this->form)
			{
				auto size = box.texture->getSize();
				box.sprite.setScale(scale / (size.x), scale / (size.y));
			}
		}

		void Static_Object::render(Engine::Window& window, const Scene::Scene& scene) const
		{
			sf::Vector2f size((float)window.getSize().x, (float)window.getSize().y);
			for (auto &box : this->form)
			{
				if (!box.canView(sf::Vector2f(0, 0), size))
				{
					continue;
				}
				window.draw(box.sprite);
			}
		}

		void Static_Object::setScale(sf::Vector2f vec)
		{
			for (auto &box : this->form)
			{
				box.sprite.setScale(vec);
			}
		}

	}
}