#pragma once
#include "../System/Util.cpp"
#include <Windows.h>
#include <memory>
#include <SFML/Graphics.hpp>
#include <vector>

namespace Engine {
	class Window;
}
namespace Scene {
    class Scene;
}

namespace game_object {
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

	class BoxForm: public Object{
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