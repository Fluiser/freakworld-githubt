#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <vector>
#include "../System/Util.cpp"
#include "Object.h"
#include <Windows.h>
#include <string>
#include <exception>
#include <iostream>
#include <boost/stacktrace.hpp>

#define ABSTRACT_MESSAGE_ERROR(function) function { \
std::cout << "Call virtual function: " << #function << '\n'; \
std::cout << boost::stacktrace::stacktrace(); \
_exit(-10); } 

namespace game_object {
	//information about object
	//stuctured like a hit-boxes.
	//Just info about form.
	Object::Object() {}
	Object::~Object() {}
	BoxForm::BoxForm() {}
	bool BoxForm::canView(Math::vec2f scene_start, Math::vec2f scene_end) const 
	{
		auto pos = sprite.getPosition();
		auto size = sprite.getScale();
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
		
	//debug
	ABSTRACT_MESSAGE_ERROR(bool Object::canView(Math::vec2f scene_start, Math::vec2f scene_end) const)
	ABSTRACT_MESSAGE_ERROR(bool Object::inObject(Math::vec2f) const)
    ABSTRACT_MESSAGE_ERROR(void Object::render(Engine::Window&) const)

	sf::Vector2f Object::getSize() const
	{
		auto size = this->texture->getSize();
		auto scale = this->sprite.getScale();
		return sf::Vector2f{size.x * scale.x, size.y * scale.y};
	}


	//end debug section

	Static_Object::Static_Object(): Object() {}
	bool Static_Object::canView(Math::vec2f scene_start, Math::vec2f scene_end) const 
	{
		for(const auto& box: *form)
		{
			if(box.canView(scene_start, scene_end)) return true;
		}
		return false;
	}

	bool Static_Object::inObject(Math::vec2f vec)
	{
		for(const auto& box: *this->form)
		{
			if(box.inObject(vec)) return true;
		}
		return false;
	}

	Dynamic_Object::Dynamic_Object(): Object() {}

	bool Dynamic_Object::canView(Math::vec2f scene_start, Math::vec2f scene_end) const
	{
		auto pos = this->sprite.getPosition();
		auto size = this->getSize();
		Math::vec2f end{ pos.x + size.x, pos.y + size.y };
		if (end.x < scene_start.x ||
			end.y < scene_start.y) return false;
		if (pos.x > scene_end.x ||
			pos.y > scene_end.y) return false;
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
		return 	point.x >= pos.x && point.x <= end.x &&
				point.y >= pos.y && point.y <= end.y;
	}

}

#undef ABSTRACT_MESSAGE_ERROR