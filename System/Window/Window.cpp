#include "Window.hpp"

namespace Engine{
    namespace Window {

        Window::Window() {}
        Window::~Window() {}

        void Window::init(  Math::vec2i size,
                            std::string&& title, 
                            std::initializer_list<std::pair<int,int>> settings,
                            GLFWmonitor* monitor)
        {

            if(!glfwInit())
                throw std::runtime_error("glfwInit() return false.");
            
            for(const auto& pair: settings)
            {
                glfwWindowHint(pair.first, pair.second);
            }
            
            _window_title.swap(title);
            _window = glfwCreateWindow(size.x, size.y, _window_title.c_str(), monitor, 0);

            if(!_window)
            {
                glfwTerminate();
                throw std::runtime_error("glfwCreateWindow() return NULL");
            }

            _VkDriver.init(std::vector<const char*>{});
            glfwCreateWindowSurface(
                _VkDriver.instance,
                _window,
                0,
                &_VkDriver.surface
            );
        }

        Engine::IODevices::Event waitEvent()
        {
            return Engine::IODevices::Event{};
        }

    }
}