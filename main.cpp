#include <System/Window/Window.hpp>
#include <thread>
#include <chrono>
#include <iostream>
#include <System/Graphics/Shader.hpp>

int main()
{
	Engine::Window::Window window;

	window.init({1280, 720}, "hell");

	while(!window.ShouldClose())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		glfwPollEvents();
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
		window.draw();
		window.display();
	}

	return 0;
}