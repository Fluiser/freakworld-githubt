#include "System/Window.h"
#include "gameplay/Object.h"
#include "gameplay/Scene.h"
#include <iostream>
#include <thread>
#include <chrono>

int main()
{
	Engine::Window window(sf::VideoMode(1280, 720), "window");
	sf::Event event;
	
	sf::RectangleShape shape({200, 200});
	shape.setFillColor(sf::Color::Red);
	sf::CircleShape circle(3);
	circle.setFillColor(sf::Color::Red);

	circle.setPosition(1280/2, 720/2);
	game_object::Dynamic_Object obj;

	obj.loadFromFile("box.png");
	auto c = obj.texture->getSize();
	auto s = obj.sprite.getScale();
	std::cout << "Scale: " << s.x << ' ' << s.y << '\n';
	std::cout << "Size: " << c.x << ' ' << c.y << '\n';
	std::cout << "Object size: " << obj.getSize().x << ' ' << obj.getSize().y << '\n';
 
	struct {
		bool filled = false;
		sf::Vector2i pos;
	} last_point;

	Scene::Scene scene(Scene::Scene::type_t::DYNAMIC_SCENE);

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) return 0;
			if(event.type == sf::Event::MouseWheelMoved)
			{
				scene.changeScale(window.scale*0.1*event.mouseWheel.delta);
			}
			if(event.type == sf::Event::MouseButtonPressed)
			{
				if(!last_point.filled)
				{
					last_point.pos = sf::Mouse::getPosition(window);
					last_point.filled = true;
				}
			}
			if(event.type == sf::Event::MouseButtonReleased)
			{
				last_point.filled = false;
			}
			if(event.type == sf::Event::MouseMoved && last_point.filled)
			{
				scene.offset.x -= (last_point.pos.x-event.mouseMove.x);
				scene.offset.y -= (last_point.pos.y-event.mouseMove.y);
				last_point.pos.x = event.mouseMove.x;
				last_point.pos.y = event.mouseMove.y;
			}
			if(event.type == sf::Event::KeyPressed)
			{
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					obj.move({-1, 0});
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					obj.move({1, 0});
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
					obj.move({0, -1});
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					obj.move({0, 1});
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) return 0;
			}
		}
		window.clear();
		window.draw(circle);
		window.draw(obj);
		window.drawScene(scene);
		window.display();
	}

	return 0;
}
