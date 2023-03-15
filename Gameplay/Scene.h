#pragma once
#include <vector>
#include <memory>
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


		std::vector<std::unique_ptr<Engine::Objects::Object>> objects;
		float scale = 100.0;

		friend Engine::Window;
	
	protected:
		inline int separateFloat(float n) const;
	public:
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
		T& create()
		{
			this->objects.emplace_back(std::make_unique<T>());
			return *((T*)this->objects.back().get());
		}
		
		template<class T = Engine::Objects::Object>
		T* get(sf::Vector2i); // Разделять объекты по map'aм

		area_t getVisibleArea(sf::Vector2u) const;
		sf::Vector2f getPositionf(sf::Vector2i) const ; // преобразует виртуальное пространство в позицию на окне.
		sf::Vector2i getPositioni(sf::Vector2i p) const; //

		sf::Vector2i getVirtualPos(sf::Vector2f) const; // преобразует позицию на окне в виртуальное пространство.

		void changeScale(float);
		void setScale(float);

		const float& getScale() const noexcept;
	};
};