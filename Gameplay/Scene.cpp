#pragma once
#include <iostream>
#include <math.h>
#include "Scene.hpp"
#include <boost/stacktrace.hpp>

namespace Scene {
	Scene::Scene::Scene(type_t t, sf::Vector2u ws):
	type(t),
	windowSize(ws),
	_static_objects(),
	_dynamic_objects()
	{

	}

	Scene::__iterator Scene::begin()
	{
		return __iterator(_static_objects.begin(), _dynamic_objects.begin(), this);
	}
	Scene::__iterator Scene::end()
	{
		return __iterator(_static_objects.end(), _dynamic_objects.end(), this);
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

		auto& _this = *this;

		for (auto* ptr: (_this))
		{
			ptr->setScale( scale - 1.0f );
		}
	}

	sf::Vector2i Scene::getVirtualPos(sf::Vector2f pos) const
	{
		pos.x -= (windowSize.x/2);
		pos.y -= (windowSize.y/2);
		pos.x /= scale;
		pos.y /= -scale;
		return sf::Vector2i(ceil(pos.x - 1), ceil(pos.y));
	}

	template<class T>
	T& Scene::create(sf::Vector2i)
	{
		std::cout << "Use Scene::create with template T: " << typeid(T).name() << "\n" << boost::stacktrace::stacktrace() << "\n";
		exit(-10);
	}

	template<>
	Engine::Objects::Static_Object& Scene::create(sf::Vector2i vec)
	{
		int idx = Scene::calcIdx(vec);
		if(_static_objects.count(idx) > 0) {
			_static_objects.insert({idx, decltype(_static_objects)::value_type::second_type()});
		}
		_static_objects[idx].emplace_back();
		return _static_objects[idx].back();
	}
	
	template<>
	Engine::Objects::Dynamic_Object& Scene::create(sf::Vector2i vec)
	{
		_dynamic_objects.emplace_back();
		return _dynamic_objects.back();
	}

	template<>
	std::list<Engine::Objects::Static_Object>* Scene::get(sf::Vector2i v)
	{
		int idx = Scene::calcIdx(v);
		if(_static_objects.count(idx) > 0) 
			return (&_static_objects[idx]);
	}

	template<>
	std::list<Engine::Objects::Object>* Scene::get(sf::Vector2i v)
	{
		return (std::list<Engine::Objects::Object>*)
				(this->get<Engine::Objects::Static_Object>(v));
	}


	// template<>
	// std::list<Engine::Objects::Static_Object>* Scene::find(sf::Vector2i vec)
	// {
	// 	for(auto& pair: _static_objects)
	// 	{
	// 		if(pair.second.size() && pair.second.front().gpos == vec)
	// 			return (&pair.second);
	// 	}
	// 	return nullptr;
	// }

	// template<>
	// std::list<Engine::Objects::Object>* Scene::find(sf::Vector2i vec)
	// {
	// 	return 	(std::list<Engine::Objects::Object>*)
	// 			(this->find<Engine::Objects::Static_Object>(vec) || 
	// 			this->find<Engine::Objects::Dynamic_Object>(vec) );
	// }

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
