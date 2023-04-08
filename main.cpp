#include "System/Window.h"
#include "Gameplay/Objects.h"
#include "Gameplay/Scene.hpp"
#include <iostream>
#include <thread>
#include <System/Graphics/String.hpp>
#include <chrono>
#include <Gameplay/Player.h>
#include <System/Handlers.h>
#include <math.h>
#include <System/Discord.hpp>

/*
 * Нахуй векторы sfml.
 * Надо будет переделать.
 * */

float hue2rgb(float p, float q, float t) {
	if (t < 0.0f) t += 1.0f;
	if (t > 1.0f) t -= 1.0f;
	if (t < 1.0f / 6.0f) return p + (q - p) * 6.0f * t;
	if (t < 1.0f / 2.0f) return q;
	if (t < 2.0f / 3.0f) return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;
	return p;
}

uint32_t hslToRgb(float h, float s, float l) {
	float r, g, b;
	float q = l < 0.5 ? l * (1.0f + s) : l + s - l * s;
	float p = 2.0f * l - q;
	r = hue2rgb(p, q, h + 1.0f / 3.0f);
	g = hue2rgb(p, q, h);
	b = hue2rgb(p, q, h - 1.0f / 3.0f);
	if (r < 0.1 && g < 0.1 && b < 0.1)
		std::cout << h << " " << s << " " << l << "\n";
	return ((int)round(r * 255.0f) << 24 | ((int)round(g * 255.0f) << 16) | ((int)round(b * 255.0f) << 8));
}

int main(int argc, char** argv)
{

	std::shared_ptr<sf::Color[]> colors = std::make_shared<sf::Color[]>(100);

	for (int i = 1; i <= 20; ++i)
	{//
		int f = hslToRgb(i / 100.0f * 5, 1, 0.5);
		colors[i - 1] = sf::Color(f | 0x000000ff);
	}

	init_handlers();

	Engine::Window window(sf::VideoMode(1280, 720), "frog");
	sf::Event event;

	window.setVerticalSyncEnabled(true);

	sf::RectangleShape shape({ 200, 200 });
	shape.setFillColor(sf::Color::Red);

	sf::Font font;
	font.loadFromFile("e.ttf");

	Engine::Graphics::String str(20.0f, {50, 250}, Engine::Graphics::String::RAINBOW | Engine::Graphics::String::WAVE, font);
	str.setCharSize(72);
	str.add("I feel like shit");

	str.setColorSet(colors, 20);

	struct {
		bool filled = false;
		sf::Vector2i pos;
	} last_point;

	Scene::Scene scene(Scene::Scene::type_t::DYNAMIC_SCENE, window.getSize());

	Discord::init(argv[0], "DYNAMIC_SCENE", "DefaultWorld");
	Discord::CallbackThread(window);

	sf::Vector2i lastmousePressed;

	//DEB_LOG("\n\n" << scene.getScale()/ (float)obj.texture->getSize().x << "\n" << scene.getScale()/ (float)obj.texture->getSize().y << "\n\n");

	auto& obj = scene.create< Engine::Objects::Static_Object >({ 0,0 });
	auto& path_obj = scene.create< Engine::Objects::Dynamic_Object >({ 3,3 });
	auto& mouse_obj = scene.create< Engine::Objects::Dynamic_Object >({ 0, 0 });

	if (!obj.clip) {
		std::cout << "what the fuck";
		return 1;
	}

	path_obj.texture = std::make_shared<sf::Texture>();
	path_obj.texture->loadFromFile("red.png");
	path_obj.sprite.setTexture(*path_obj.texture);

	mouse_obj.texture = std::make_shared<sf::Texture>();
	mouse_obj.texture->loadFromFile("m.png");
	mouse_obj.sprite.setTexture(*mouse_obj.texture);


	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			std::string path = "box";
			path += std::to_string(i + j);
			path += ".png";
			std::shared_ptr<sf::Texture> texture(std::make_shared<sf::Texture>());
			texture->loadFromFile(path);
			obj.form.emplace_back();
			obj.form.back().texture = texture;
			obj.form.back().sprite.setTexture(*texture);
			obj.form.back().gpos = { j + 1, i + 1 };
		}
	}

	scene.setScale(scene.getScale());
	sf::Vector2i vec_mouse;

	float fps = 0;

	std::thread fpsCalc([&] {
		sf::Clock timer;
		int timerMS;
		while (window.isOpen())
		{
			if ((timerMS = timer.getElapsedTime().asMilliseconds()) >= 1000)
			{
				float fpsPS = fps * (1000.0f / ((float)timerMS));
				fps = 0;
				timer.restart();
				std::cout << "FPS: " << fpsPS << "\n";
			}
			else {
				std::this_thread::sleep_for(std::chrono::milliseconds(1000 - timerMS));
			}
		}
		});

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) return 0;
			if (event.type == sf::Event::MouseWheelMoved)
			{
				scene.changeScale(scene.getScale() * 0.1 * event.mouseWheel.delta);
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				lastmousePressed = sf::Mouse::getPosition(window);
				if (!last_point.filled)
				{
					last_point.pos = lastmousePressed;
					last_point.filled = true;
				}
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if ((sf::Vector2i)lastmousePressed == (sf::Vector2i)sf::Mouse::getPosition(window))
				{
					vec_mouse = mouse_obj.gpos = scene.getVirtualPos(
						(sf::Vector2f)sf::Mouse::getPosition(window) + sf::Vector2f(scene.offset.x, -scene.offset.y)
					);
				}
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				last_point.filled = false;
			}

			if (event.type == sf::Event::MouseMoved && last_point.filled)
			{
				scene.offset.x += (last_point.pos.x - event.mouseMove.x);
				scene.offset.y -= (last_point.pos.y - event.mouseMove.y);
				last_point.pos.x = event.mouseMove.x;
				last_point.pos.y = event.mouseMove.y;
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
					scene.offset.x += 10;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
				{
					auto v = scene.getVisibleArea(window.getSize());
					std::cout << "VISIBLE AREA: (" << v.start.x << "; " << v.start.y <<
						") -> (" << v.end.x << "; " << v.end.y << ")\n";
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) return 0;
			}
		}
		//std::cout << "OFFSET : " << scene.offset.x << " " << scene.offset.y << "\n";
		window.clear();
		std::vector<sf::Vector2i> vpath = Gameplay::constructPath(sf::Vector2i(0, 0), vec_mouse, scene, 10);
		//std::cout << vpath.size() << " <" << vec_mouse.x << "; " << vec_mouse.y << ">\n";
		if (vpath.size() > 0)
		{
			// std::cout << "Достигаем\n";
			for (auto pos : vpath)
			{
				path_obj.gpos = pos;
				path_obj.normalize(window, scene);
				window.draw(path_obj, scene);
			}
		}
		else {
			//std::cout << "Недостигаем.\n";
		}
		window.drawScene(scene);
		window.draw(str);
		str.normalize();
		window.display();
		fps += 1.0f;
	}

	return 0;
}