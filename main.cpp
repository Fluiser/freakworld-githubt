#include <System/Window/Window.hpp>
#include <thread>
#include <chrono>
#include <iostream>
#include <System/Graphics/Shader.hpp>

int main()
{
	Engine::Window::Window window;

	window.init({1280, 720}, "hell");

	std::cout << _binary_fragmentShader_start;

	while(!window.ShouldClose())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		glfwPollEvents();
	}

	return 0;
}