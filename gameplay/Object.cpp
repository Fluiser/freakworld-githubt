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
#include "Scene.h"
#include "../System/Window.h"

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
		
	//debug
	ABSTRACT_MESSAGE_ERROR(bool Object::canView(sf::Vector2f scene_start, sf::Vector2f scene_end) const)
	ABSTRACT_MESSAGE_ERROR(bool Object::inObject(Math::vec2f) const)
    ABSTRACT_MESSAGE_ERROR(void Object::render(Engine::Window&, const Scene::Scene&) const)
    ABSTRACT_MESSAGE_ERROR(	void Object::setScale(sf::Vector2f))
    ABSTRACT_MESSAGE_ERROR(	void Object::setScale(float))
    ABSTRACT_MESSAGE_ERROR(	void Object::normalize(const Engine::Window&, const Scene::Scene&))

    void Dynamic_Object::normalize(const Engine::Window& window, const Scene::Scene& scene)
    {
	    sf::Vector2i windowSize(window.getSize().x/2, window.getSize().y/2);
        this->sprite.setPosition(
                (sf::Vector2f)windowSize - sf::Vector2f(scene.offset.x, -scene.offset.y) + scene.getPositionf(this->gpos)
                );
    }
    void Static_Object::normalize(const Engine::Window& window, const Scene::Scene& scene)
    {
        for(auto& box: this->form)
        {
            box.normalize(window, scene);
        }
    }
    void BoxForm::normalize(const Engine::Window& window, const Scene::Scene& scene)
    {
	    sf::Vector2i windowSize(window.getSize().x/2, window.getSize().y/2);
        this->sprite.setPosition(
                (sf::Vector2f)windowSize - sf::Vector2f(scene.offset.x, -scene.offset.y) + scene.getPositionf(this->gpos)
                );
    }

    void Static_Object::render(Engine::Window& window, const Scene::Scene& scene) const
    {
        sf::Vector2f size((float)window.getSize().x, (float)window.getSize().y);
        for(auto& box: this->form)
        {
            if (!box.canView(sf::Vector2f(0,0), size)) {
                continue;
            }
            window.draw(box.sprite);
        }
    }
    void Dynamic_Object::render(Engine::Window& window, const Scene::Scene& scene) const
    {
        {
            sf::Vector2f size((float)window.getSize().x, (float)window.getSize().y);

            if (!this->canView(sf::Vector2f(0,0), size))
                return;
        }
        window.draw(this->sprite);
    }

    void Static_Object::setScale(sf::Vector2f vec)
    {
	    for(auto& box: this->form)
        {
	        box.sprite.setScale(vec);
        }
    }
    void Dynamic_Object::setScale(sf::Vector2f vec)
    {
	    this->sprite.setScale(vec);
    }

    void Static_Object::setScale(float scale)
    {
	    for(auto& box: this->form)
        {
	        auto size = box.texture->getSize();
	        box.sprite.setScale(scale / size.x, scale / size.x);
        }
    }
    void Dynamic_Object::setScale(float scale)
    {
        auto size = texture->getSize();
        sprite.setScale(scale / size.x, scale / size.x);
    }

//	sf::Vector2f Object::getSize() const
//	{
//		auto size = this->texture->getSize();
//		auto scale = this->sprite.getScale();
//		return sf::Vector2f{size.x * scale.x, size.y * scale.y};
//	}


	//end debug section

	Static_Object::Static_Object(): Object() {}
	bool Static_Object::canView(sf::Vector2f scene_start, sf::Vector2f scene_end) const
	{
		for(const auto& box: form)
		{
			if(box.canView(scene_start, scene_end)) return true;
		}
		return false;
	}

	bool Static_Object::inObject(Math::vec2f vec)
	{
		for(const auto& box: this->form)
		{
			if(box.inObject(vec)) return true;
		}
		return false;
	}

	Dynamic_Object::Dynamic_Object(): Object() {}

    sf::Vector2f Dynamic_Object::getSize() const
    {
        auto s = this->sprite.getScale();
        auto size = this->texture->getSize();
        return sf::Vector2f((float)(size.x * s.x), (float)(size.y * s.y));
    }
    sf::Vector2f BoxForm::getSize() const
    {
        auto s = this->sprite.getScale();
        auto size = this->texture->getSize();
        return sf::Vector2f((float)(size.x * s.x), (float)(size.y * s.y));
    }

	bool Dynamic_Object::canView(sf::Vector2f scene_start, sf::Vector2f scene_end) const
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