#pragma once
#include <list>
#include <memory>
#include <map>
#include "../System/Util.hpp"
#include "Objects.h"

namespace Engine {
	class Window;
}

/**
 * Штож. 
 * Поскольку я делаю в одиночку, то могу позволить себе всю неадекватную дрянь.
 * Дык вот. Основными косяки являются:
 * 		Неправильная система координат:
 * 			offset вверх, по факту, отрицательный, но у меня положительный. При операциях с ним его надо инвертировать. 
 * 				scene.getVirtualPos(
					(sf::Vector2f)sf::Mouse::getPosition(window) + sf::Vector2f(scene.offset.x, -scene.offset.y)
				);
 *	 	Рендер объектов ( я попытался его скрыть ):
			Объект сначала надо нормализировать, а потом рендерить.
				Gameplay::Objects::SomeObject.normalize() -> .render(Window, Scene)
 
 *
 * 
 * Возможно что-то ещё, но я уже забыл.
 * 
 */

namespace Scene {
	class Scene {
		/*
		 * Сцена - область из клеток.
		 * Нуль-точка - Середина.
		 * */

		float scale = 100.0;

		std::map<int, std::list<Engine::Objects::Static_Object>> _static_objects;
		std::list<Engine::Objects::Dynamic_Object> _dynamic_objects;

		inline static int calcIdx(sf::Vector2i v)
		{
			return ((v.x << 16) & 0xffff0000) | (v.y & 0xffff);
		}

	protected:
		inline int separateFloat(float n) const;

		class __iterator {
			typedef decltype(_static_objects.begin()) T1; // STATIC
			typedef decltype(_dynamic_objects.begin()) T2; // DYNAMIC
			// OK?
			typedef Engine::Objects::Object TT; // target type


			T1 src1;
			decltype(_static_objects.begin()->second.begin()) src1_iter;
			T2 src2;
			const Scene* const _scene;
		public:
			// Будем надеяться на лучшее...
			using value_type = TT*;
			using difference_type = TT*;
			using pointer = TT*;
			using reference = TT&;

			explicit __iterator(
				T1 iterator1,
				T2 iterator2,
				const Scene* arg_scene
			): 	src1(iterator1),
				src2(iterator2),
				_scene(arg_scene)
			{
				if(src1 != _scene->_static_objects.end())
					src1_iter = src1->second.begin();
			}

			__iterator operator++()
			{
				if(src1 != _scene->_static_objects.end()) {
					++src1_iter;
					if(src1_iter == src1->second.end()) {
						src1++;
						if(src1 == _scene->_static_objects.end()) return (*this);
						else src1_iter = src1->second.begin();
						return (*this);
					}
				}
				if(src2 != _scene->_dynamic_objects.end()) {
					++src2;
					return (*this);
				}
				return (*this);
			}
			__iterator operator++(int)
			{
				__iterator it = (*this);
				++(*this);
				return it;
			}
			bool operator==(const __iterator& another)
			{
				return (another.src1 == src1 && another.src2 == src2);
			}
			bool operator!=(const __iterator& another)
			{
				return (another.src1 != src1 || another.src2 != src2);
			}
			TT* operator*() const
			{
				if(src1 != _scene->_static_objects.end()) {
					return (TT*)(&(*src1_iter));
				}
				return (TT*)(&(*src2));
			}
		};

		friend Engine::Window;
		friend __iterator;
	public:
		
		__iterator begin();
		__iterator end();

		sf::Vector2i offset{0, 0};
		sf::Vector2u windowSize;


		struct area_t {
			sf::Vector2i start;
			sf::Vector2i end;
		};


		enum type_t {
			INFINITY_GENERATION,
			FIXED,
			DYNAMIC_SCENE
		} type;

		Scene(type_t, sf::Vector2u ws);

		template<class T>
		T& create(sf::Vector2i);

		// {
		// 	this->objects.emplace_back(std::make_unique<T>());
		// 	return *((T*)this->objects.back().get());
		// }
		
		template<class T = Engine::Objects::Object>

		std::list<T>* get(sf::Vector2i); // Разделять объекты по map'aм // Почти тоже, что и map, но с коллизией
		
		template<class T> 
		std::list<T>* find(sf::Vector2i); // find - сравнивает позиции точно.

		area_t getVisibleArea(sf::Vector2u) const;
		sf::Vector2f getPositionf(sf::Vector2i) const ; // преобразует виртуальное пространство в позицию на окне.
		sf::Vector2i getPositioni(sf::Vector2i p) const; //

		sf::Vector2i getVirtualPos(sf::Vector2f) const; // преобразует позицию на окне в виртуальное пространство.

		void changeScale(float);
		void setScale(float);

		const float& getScale() const noexcept;
	};
};