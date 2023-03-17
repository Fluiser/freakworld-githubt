#pragma once
#include "Object.h"

namespace Engine 
{
	namespace Objects {

	class Dynamic_Object : public Object {
		public:
			std::shared_ptr<sf::Texture> texture;
			sf::Sprite sprite;

			Dynamic_Object();

	//		float HP = INFINITY;

			bool canView(sf::Vector2f scene_start, sf::Vector2f scene_end) const override;
			bool inObject(Math::vec2f) const override;
			sf::Vector2f getSize() const;

			void loadFromFile(const std::string&);
			void move(Math::vec2f vec);
			void render(Engine::Window&, const Scene::Scene&) const override;
			virtual void setScale(sf::Vector2f) override;
			virtual void setScale(float) override;
			void normalize(const Engine::Window&, const Scene::Scene&) override;
		};
		
	}
}