#include "System/Window.h"
#include "Gameplay/Objects.h"
#include "Gameplay/Scene.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <Gameplay/Player.h>
#include <System/Handlers.h>

/*
 * Нахуй векторы sfml.
 * Надо будет переделать.
 * */


int main()
{
	init_handlers();

	Engine::Window window(sf::VideoMode(1280, 720), "fuck");
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

	Scene::Scene scene(Scene::Scene::type_t::DYNAMIC_SCENE, window.getSize());

	sf::Vector2f sizeWindow( window.getSize().x/2.0f, window.getSize().y/2.0f  );

	circle.setPosition(sizeWindow);

	//DEB_LOG("\n\n" << scene.getScale()/ (float)obj.texture->getSize().x << "\n" << scene.getScale()/ (float)obj.texture->getSize().y << "\n\n");

	decltype(auto) obj = scene.create< Engine::Objects::Static_Object >();
	decltype(auto) path_obj = scene.create< Engine::Objects::Dynamic_Object >();
	
	if(!obj.clip){
		std::cout << "what the fuck";
	return 1;
	}

	path_obj.texture = std::make_shared<sf::Texture>();
	path_obj.texture->loadFromFile("red.png");
	path_obj.sprite.setTexture(*path_obj.texture);
	

	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 2; ++j)
		{
			std::string path = "box";
			path += std::to_string(i+j);
			path += ".png";
			std::shared_ptr<sf::Texture> texture(std::make_shared<sf::Texture>());
			texture->loadFromFile(path);
			obj.form.emplace_back();
			obj.form.back().texture = texture;
			obj.form.back().sprite.setTexture(*texture);
			obj.form.back().gpos = {j+1, i+1};
		}
	}

	scene.setScale(scene.getScale());
	sf::Vector2i vec_mouse;

	float fps = 0;

	std::thread fpsCalc([&] {
		sf::Clock timer;
		int timerMS;
		while(window.isOpen())
		{
			if( (timerMS = timer.getElapsedTime().asMilliseconds()) >= 1000)
			{
				float fpsPS = fps * (1000.0f/((float)timerMS));
				fps = 0;
				timer.restart();
				std::cout << "FPS: " << fpsPS << "\n";
			} else {
				std::this_thread::sleep_for(std::chrono::milliseconds(1000 - timerMS));
			}
		}
	});

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
				vec_mouse = path_obj.gpos = scene.getVirtualPos(
					(sf::Vector2f)sf::Mouse::getPosition(window) + sf::Vector2f(scene.offset.x, -scene.offset.y)
				);
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
		//std::cout << "OFFSET : " << scene.offset.x << " " << scene.offset.y << "\n";
		window.clear();
		window.drawScene(scene);
		std::vector<sf::Vector2i> vpath = Gameplay::constructPath(sf::Vector2i(0, 0), vec_mouse, scene, 10);
		//std::cout << vpath.size() << " <" << vec_mouse.x << "; " << vec_mouse.y << ">\n";
		if (vpath.size() > 0)
		{
			// std::cout << "Достигаем\n";
			path_obj.gpos = vec_mouse;
			path_obj.normalize(window, scene);
			window.draw(path_obj, scene);
			for (auto pos : vpath)
			{
				path_obj.gpos = pos;
				path_obj.normalize(window, scene);
				window.draw(path_obj, scene);
			}
		} else {
			//std::cout << "Недостигаем.\n";
		}
		window.draw(circle);
		window.display();
		fps += 1.0f;
	}

	return 0;
}