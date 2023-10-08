#include <System/Window/Window.hpp>
#include <thread>
#include <chrono>
#include <iostream>
#include <System/Graphics/Shader.hpp>

int main()
{
	Engine::Window::Window window;

	window.init({720, 720}, "hell");

	while(!window.ShouldClose())
	{
		// std::this_thread::sleep_for(std::chrono::milliseconds(20));
		glfwPollEvents();
		// std::this_thread::sleep_for(std::chrono::milliseconds(30));
		window.clear();

		window.draw({{0.0, -0.5},  {0.9f, 0.2f, 0.9f}});
		window.draw({{0.5, 0.5},  {0.3f, 0.5f, 0.6f}});
		window.draw({{-0.5, 0.5}, 	{0.1f, 0.5f, 0.1f}});
		// bool start = true;
		// static std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		// static float angle = 0;
		// static constexpr float stepangle = (M_PI*2.0f/3.0f);
		// static constexpr float ss = stepangle/2;
		// static float colorss = 0;
		// static float colorangle = angle;
		
		// if(start || std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin).count() >= 10)
		// {
		// 	if(start) start = false;
		// 	window
		// 	.clear();
		// 	window
		// 	.draw({{cos(angle), sin(angle)},
		// 		{abs(cos(colorangle )), abs(sin(colorangle )), abs(tanh(colorangle))}});
		// 	window
		// 	.draw({{cos(angle + stepangle), sin(angle + stepangle)},
		// 		{abs(cos(colorangle + stepangle)), abs(sin(colorangle + stepangle )), abs(tanh(colorangle + stepangle))}});
		// 	window
		// 	.draw({{cos(angle + stepangle*2), sin(angle + stepangle*2)},
		// 		{abs(cos(colorangle + stepangle * 2)), abs(sin(colorangle + stepangle * 2)), abs(tanh(colorangle + stepangle * 2))}});
		// 	window
		// 	.draw({{cos(ss + angle), sin(ss + angle)},
		// 		{abs(cos(colorss + colorangle )), abs(sin(colorss + colorangle )), abs(sin(colorss+colorangle)*cos(ss*2 + colorangle))}});
		// 	window
		// 	.draw({{cos(ss + angle + stepangle), sin(ss + angle + stepangle)},
		// 		{abs(cos(colorss + colorangle + stepangle)), abs(sin(colorss + colorangle + stepangle )), abs(sin(colorss+colorangle)*cos(colorss*2 + colorangle + stepangle))}});
		// 	window
		// 	.draw({{cos(ss + angle + stepangle*2), sin(ss + angle + stepangle*2)},
		// 		{abs(cos(colorss + colorangle + stepangle * 2)), abs(sin(colorss + colorangle + stepangle * 2)), abs(sin(colorss+colorangle)*cos(colorss*2 + colorangle + stepangle * 2))}});
			
		// 	angle += M_PI/200;
		// 	colorangle += M_PI/150;
		// }
		window.display();

	
	}

	return 0;
}

