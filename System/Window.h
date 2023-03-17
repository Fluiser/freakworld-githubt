#pragma once
#include <SFML/Graphics.hpp>
#include <Gameplay/Objects.h>
#include "../Gameplay/Scene.hpp"
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

		void draw(const Engine::Objects::Object& obj, Scene::Scene& scene);
		void drawScene( Scene::Scene&);
		void changeScale(float);

	};
}