#pragma once
#include <System/Util.cpp>
#include <Windows.h>
#include <memory>
#include <SFML/Graphics.hpp>
#include <vector>

namespace Scene {	
	class Scene;
}


namespace Engine 
{
	class Window;

    namespace Objects {

	//information about object
	//stuctured like a hit-boxes.
	//Just info about form.

		class Object {
		protected:
			Object();
		public:

			// grid world position
			sf::Vector2i gpos;


			~Object();

			virtual void render(Engine::Window&, const Scene::Scene&) const;
			virtual bool canView(sf::Vector2f scene_start, sf::Vector2f scene_end) const;
			virtual bool inObject(Math::vec2f) const;
			virtual void setScale(sf::Vector2f);
			virtual void setScale(float);
			virtual void normalize(const Engine::Window&, const Scene::Scene&);
		};
	}
	
}