#include <System/Window/Window.hpp>
#include <thread>
#include <chrono>
#include <iostream>
#include <System/Graphics/Shader.hpp>

int main()
{
	Engine::Window::Window window;

	window.init({1000, 1000}, "hell");

	while(!window.ShouldClose())
	{
		// std::this_thread::sleep_for(std::chrono::milliseconds(20));
		glfwPollEvents();
		// std::this_thread::sleep_for(std::chrono::milliseconds(30));

		bool start = true;
		static std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		static float angle = 0;
		static constexpr float stepangle = (M_PI*2.0f/3.0f);
		static constexpr float ss = stepangle/2;
		static float colorss = 0;
		static float colorangle = angle;
		static float fuckColor = -3;
		
		if(start || std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin).count() >= 10)
		{
			if(start) start = false;
			window
			.clear();
			
			static auto ccol = [&](float ang) -> glm::vec3 {
				ang = (ang/(M_PI*2));
				ang -= (float)trunc(ang);
				float r;
				float g = 0;
				float b = 0;
				*((int*)&r) = *(int*)(&ang) & 					   	  0b11111111 << 16;
				*((int*)&g) = *(int*)(&ang) & 			      0b1111111111111111 << 8;
				*((int*)&b) = *(int*)(&ang) &         0b11111111111111111111111111111111;
				glm::vec3 v{
					r,g,b
				};
				v.b = v.b - (float)trunc(v.b);
				v.r = v.r - (float)trunc(v.r);
				v.g = v.g - (float)trunc(v.g);

				v.b = 1.0f - v.b;
				v.r = 1.0f - v.r;
				v.g = 1.0f - v.g;
				
				
				return v;
			};

			for(int i = 0; i < 3000; ++i)
			{ 
				window.draw({{cos((i * stepangle/(100)) + angle), 							sin((i * stepangle/(100)) + angle)}, {1, 0, 0}});
				window.draw({{cos((i * stepangle/(100)) + angle+stepangle*2), 				sin((i * stepangle/(100)) + angle+sqrt(stepangle))}, {0, 1, 0}});
				window.draw({{cos((i * stepangle/(100)) + sqrt(angle)+stepangle), 				sin((i * stepangle/(100)) + angle+stepangle*2)}, {0, 0, 1}});
				
			}

			// window
			// .draw({{cos(angle), sin(angle)},
			// 	{abs(cos(colorangle )), abs(sin(colorangle )), abs(tanh(colorangle))}});
			// window
			// .draw({{cos(angle + stepangle), sin(angle + stepangle)},
			// 	{abs(cos(colorangle + stepangle)), abs(sin(colorangle + stepangle )), abs(tanh(colorangle + stepangle))}});
			// window
			// .draw({{cos(angle + stepangle*2), sin(angle + stepangle*2)},
			// 	{abs(cos(colorangle + stepangle * 2)), abs(sin(colorangle + stepangle * 2)), abs(tanh(colorangle + stepangle * 2))}});
			// window
			// .draw({{cos(ss + angle), sin(ss + angle)},
			// 	{abs(cos(colorss + colorangle )), abs(sin(colorss + colorangle )), abs(sin(colorss+colorangle)*cos(ss*2 + colorangle))}});
			// window
			// .draw({{cos(ss + angle + stepangle), sin(ss + angle + stepangle)},
			// 	{abs(cos(colorss + colorangle + stepangle)), abs(sin(colorss + colorangle + stepangle )), abs(sin(colorss+colorangle)*cos(colorss*2 + colorangle + stepangle))}});
			// window
			// .draw({{cos(ss + angle + stepangle*2), sin(ss + angle + stepangle*2)},
			// 	{abs(cos(colorss + colorangle + stepangle * 2)), abs(sin(colorss + colorangle + stepangle * 2)), abs(sin(colorss+colorangle)*cos(colorss*2 + colorangle + stepangle * 2))}});
			
			angle += M_PI/200;
			colorangle += M_PI/150;
		}
		window.display();

	
	}

	return 0;
}

