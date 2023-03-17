#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Object.h"
#include <string>
#include <exception>
#include <iostream>
#include <boost/stacktrace.hpp>
#include <Gameplay/Scene.hpp>
#include <System/Window.h>
#include <System/Util.hpp>

#define ABSTRACT_MESSAGE_ERROR(function) function { \
std::cout << "Call virtual function: " << #function << '\n'; \
std::cout << boost::stacktrace::stacktrace(); \
_exit(-10); } 


namespace Engine 
{
	namespace Objects {

		//information about object
		//stuctured like a hit-boxes.
		//Just info about form.
		Object::Object() {}
		Object::~Object() {}

			
		//debug
		ABSTRACT_MESSAGE_ERROR(bool Object::canView(sf::Vector2f scene_start, sf::Vector2f scene_end) const)
		ABSTRACT_MESSAGE_ERROR(bool Object::inObject(Math::vec2f) const)
		ABSTRACT_MESSAGE_ERROR(void Object::render(Engine::Window&, const Scene::Scene&) const)
		ABSTRACT_MESSAGE_ERROR(void Object::setScale(sf::Vector2f))
		ABSTRACT_MESSAGE_ERROR(void Object::setScale(float))
		ABSTRACT_MESSAGE_ERROR(void Object::normalize(const Engine::Window&, const Scene::Scene&))





		//end debug section
	}

}

#undef ABSTRACT_MESSAGE_ERROR