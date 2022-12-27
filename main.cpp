#include "System/Window.h"
#include "gameplay/Object.h"
#include "gameplay/Scene.h"
#include <iostream>
#include <thread>
#include <chrono>

int main()
{
	Engine::Window window(sf::VideoMode(1280, 720), "fuck");
	sf::Event event;
	
	sf::RectangleShape shape({200, 200});
	shape.setFillColor(sf::Color::Red);
	sf::CircleShape circle(3);
	circle.setFillColor(sf::Color::Yellow);

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

	auto* obfdsafddafsj = (game_object::Dynamic_Object*)scene.get({ 0, 0 });

	sf::Vector2f sizeWindow( window.getSize().x/2.0f, window.getSize().y/2.0f  );

	circle.setPosition(sizeWindow);

	DEB_LOG("\n\n" << scene.getScale()/ (float)obj.texture->getSize().x << "\n" << scene.getScale()/ (float)obj.texture->getSize().y << "\n\n");

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
				scene.offset.x += (last_point.pos.x-event.mouseMove.x);
				scene.offset.y -= (last_point.pos.y-event.mouseMove.y);
				last_point.pos.x = event.mouseMove.x;
				last_point.pos.y = event.mouseMove.y;
			}
			if(event.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
				{
					auto v = scene.getVisibleArea(window.getSize());
					std::cout << "VISIBLE AREA: (" << v.start.x << "; " << v.start.y <<
								 ") -> (" << v.end.x << "; " << v.end.y << ")\n";
				}
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
		obj.sprite.setScale(
			scene.getScale()/ (float)obj.texture->getSize().x,
			scene.getScale()/ (float)obj.texture->getSize().y
		);
        window.clear();
        window.drawScene(scene);
        for(int x = 0; x < 10; ++x) {
            obj.sprite.setPosition(
                    sizeWindow - sf::Vector2f(scene.offset.x, -scene.offset.y) + scene.getPosition(sf::Vector2i(x, x)));
            window.draw(obj);
        }
		window.draw(circle);
		window.display();
	}

	return 0;
}
