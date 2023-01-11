#pragma once
#include <iostream>
#include "Scene.h"

namespace Scene {
	Scene::Scene::Scene(type_t t):
	type(t)
	{

	}


	void Scene::setScale(float s)
	{
		if(s > 254)
		{
			setScale(254.0f);
			return;
		}
		if(s < 30)
		{
			setScale(30);
			return;
		}
		offset.x = (int)((float)offset.x/scale*s);
		offset.y = (int)((float)offset.y/scale*s);
		scale = s;

		for (auto& ptr : this->objects)
		{
			ptr->setScale( scale - 1.0f );
		}
	}

	Engine::Objects::Object* Scene::get(sf::Vector2i v)
	{
		for (auto& obj : this->objects)
		{
			if (obj->gpos.x == v.x && obj->gpos.y == v.y)
				return &(*obj);
		}
		return nullptr;
	}

	int Scene::separateFloat(float n) const
	{
		return n >= 0 ?
			(float)((int)n) < n ?
				(int)(n + 1) : (int)n
			:
			(float)((int)n) > n ?
				(int)(n - 1) : (int)n;
	}

	sf::Vector2f Scene::getPositionf(sf::Vector2i p) const
	{

		return sf::Vector2f(
				(((float)p.x) * (scale)),
				(((float)-p.y) * (scale))
		);
	}
	sf::Vector2i Scene::getPositioni(sf::Vector2i p) const
	{

		return sf::Vector2i(
				(((float)p.x) * (scale)),
				(((float)-p.y) * (scale))
		);
	}

	Scene::area_t Scene::getVisibleArea(sf::Vector2u visibleArea) const
	{
		return area_t{
			sf::Vector2i(   Scene::separateFloat(((float)visibleArea.x/2)/scale ),
								Scene::separateFloat(((float)visibleArea.y / 2) / scale)
						),
			sf::Vector2i(   Scene::separateFloat((float)(offset.x + visibleArea.x) / scale),
								Scene::separateFloat((float)(offset.y + visibleArea.y) / scale )
						)
		};
	}

	const float& Scene::getScale() const noexcept
	{
		return this->scale;
	}

	void Scene::changeScale(float s)
	{
		float nscale = scale + s;
		this->setScale(nscale);
	}


};
