#pragma once
#include <SFML/Graphics.hpp>
#include <Gameplay/Objects.h>
#include "../Gameplay/Scene.h"
#include <iostream>

namespace Engine {
	class Window: public sf::RenderWindow {

		inline void drawLine(const sf::Vector2f& s, const sf::Vector2f& e, sf::Color frogColor = sf::Color::Green);

	public:
		float scale = 30.0;

		using RenderWindow::draw;
		using RenderWindow::getSize;

		Window(): RenderWindow()
		{

		}
		template<class... Args>
		Window(Args... args): RenderWindow(args...)
		{

		}

		void draw(const Engine::Objects::Object& obj, const Scene::Scene& scene);
		void drawScene(const Scene::Scene&);
		void changeScale(float);

	};
}