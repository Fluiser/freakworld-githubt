#pragma once
#include "../System/Util.cpp"
#include <Windows.h>
#include <memory>
#include <SFML/Graphics.hpp>
#include <vector>

namespace Engine {
	class Window;
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
		Math::vec2i gpos;

		std::shared_ptr<sf::Texture> texture;
		sf::Sprite sprite;

		sf::Vector2f getSize() const;


		~Object();

		virtual void render(Engine::Window&) const;
		virtual bool canView(Math::vec2f scene_start, Math::vec2f scene_end) const;
		virtual bool inObject(Math::vec2f) const;
	};

	class BoxForm: public Object{
	public:
		BoxForm();

		bool canView(Math::vec2f scene_start, Math::vec2f scene_end) const override;
		bool inObject(Math::vec2f) const override;
	};

	class Static_Object : public Object {
	public:
		Static_Object();

		// gameplay object collision box
		std::shared_ptr<std::vector<BoxForm>> form;

		bool canView(Math::vec2f scene_start, Math::vec2f scene_end) const override;
		bool inObject(Math::vec2f);
	};

	class Dynamic_Object : public Object {
	public:
		Dynamic_Object();

		float HP = INFINITY;

		bool canView(Math::vec2f scene_start, Math::vec2f scene_end) const override;
		bool inObject(Math::vec2f) const override;

		void loadFromFile(const std::string&);
		void move(Math::vec2f vec);
	};

	
}