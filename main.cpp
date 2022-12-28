#include "System/Window.h"
#include "gameplay/Object.h"
#include "gameplay/Scene.h"
#include <iostream>
#include <thread>
#include <chrono>

/*
 * Нахуй векторы sfml.
 * Надо будет переделать.
 * */

int main()
{
	Engine::Window window(sf::VideoMode(1280, 720), "Hope has left this project");
	sf::Event event;
	
	sf::RectangleShape shape({200, 200});
	shape.setFillColor(sf::Color::Red);
	sf::CircleShape circle(3);
	circle.setFillColor(sf::Color::Yellow);

	circle.setPosition(1280/2, 720/2);

 
	struct {
		bool filled = false;
		sf::Vector2i pos;
	} last_point;

	Scene::Scene scene(Scene::Scene::type_t::DYNAMIC_SCENE);

	sf::Vector2f sizeWindow( window.getSize().x/2.0f, window.getSize().y/2.0f  );

	circle.setPosition(sizeWindow);

	//DEB_LOG("\n\n" << scene.getScale()/ (float)obj.texture->getSize().x << "\n" << scene.getScale()/ (float)obj.texture->getSize().y << "\n\n");

	decltype(auto) obj = scene.create< game_object::Static_Object >();

	for(int i = 0; i < 2; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            std::string path = "box";
            path += std::to_string(i+j);
            path += ".png";
            std::shared_ptr<sf::Texture> texture(std::make_shared<sf::Texture>());
            texture->loadFromFile(path);
            obj.form.emplace_back();
            obj.form.back().texture = texture;
            obj.form.back().sprite.setTexture(*texture);
            obj.form.back().gpos = {j, i};
        }
    }

	scene.setScale(scene.getScale());

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) return 0;
			if(event.type == sf::Event::MouseWheelMoved)
			{
				scene.changeScale(scene.getScale()*0.1*event.mouseWheel.delta);
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
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
					scene.offset.x += 10;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
				{
					auto v = scene.getVisibleArea(window.getSize());
					std::cout << "VISIBLE AREA: (" << v.start.x << "; " << v.start.y <<
								 ") -> (" << v.end.x << "; " << v.end.y << ")\n";
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) return 0;
			}
		}
		std::cout << "OFFSET : " << scene.offset.x << " " << scene.offset.y << "\n";
        window.clear();
        window.drawScene(scene);
		window.draw(circle);
		window.display();
	}

	return 0;
}
