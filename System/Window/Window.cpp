#include "Window.hpp"
#include <iostream>
namespace Engine{
    namespace Window {

        Window::Window() {}
        Window::~Window() 
        {
            glfwDestroyWindow(_window);
        }

        void Window::init(  Math::vec2i size,
                            std::string&& title, 
                            std::initializer_list<std::pair<int,int>> settings,
                            GLFWmonitor* monitor)
        {

            if(!glfwInit())
                throw std::runtime_error("glfwInit() return false.");
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 0);
            for(const auto& pair: settings)
            {
                glfwWindowHint(pair.first, pair.second);
            }
            
            _window_title.swap(title);
            _window = glfwCreateWindow(size.x, size.y, _window_title.c_str(), monitor, 0);
            _windowSize = size;

            if(!_window)
            {
                glfwTerminate();
                throw std::runtime_error("glfwCreateWindow() return NULL");
            }
#ifdef DEBUG
            _VkDriver.init(std::vector<const char*>{VK_EXT_DEBUG_UTILS_EXTENSION_NAME}, std::vector<const char*>{VK_KHR_SWAPCHAIN_EXTENSION_NAME}, _window);
#else
            _VkDriver.init(std::vector<const char*>{}, std::vector<const char*>{VK_KHR_SWAPCHAIN_EXTENSION_NAME}, _window);
#endif
            _VkDriver.initFrameBuffer(size.x, size.y);
        }

        Engine::IODevices::Event waitEvent()
        {
            return Engine::IODevices::Event{};
        }

    }
}