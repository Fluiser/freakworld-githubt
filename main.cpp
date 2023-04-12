#include <System/Window/Window.hpp>
#include <thread>
#include <chrono>

int main()
{
	Engine::Window::Window window;

	window.init({1280, 720}, "hell");

	while(!window.ShouldClose())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		glfwPollEvents();
	}

	return 0;
}