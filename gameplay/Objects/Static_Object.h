#pragma once
#include "Object.h"

namespace Engine 
{
	namespace Objects {

		class BoxForm: public Object {
		public:

			std::shared_ptr<sf::Texture> texture;
			sf::Sprite sprite;

			sf::Vector2f getSize() const;

			BoxForm();

			bool canView(sf::Vector2f scene_start, sf::Vector2f scene_end) const override;
			bool inObject(Math::vec2f) const override;
			void normalize(const Engine::Window&, const Scene::Scene&) override;
		};

		class Static_Object : public Object {
		public:

			Static_Object();

			// gameplay object collision box
			std::vector<BoxForm> form;

			bool canView(sf::Vector2f scene_start, sf::Vector2f scene_end) const override;
			bool inObject(Math::vec2f);
			void render(Engine::Window&, const Scene::Scene&) const override;
			virtual void setScale(sf::Vector2f) override;
			virtual void setScale(float) override;
			void normalize(const Engine::Window&, const Scene::Scene&) override;
		};

	}
}