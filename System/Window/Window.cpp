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
            _VkDriver.initFrameBuffer(_window);
        }

        Engine::IODevices::Event waitEvent()
        {
            return Engine::IODevices::Event{};
        }

        void Window::drawPXS(Engine::System::Graphics::Pipeline::Vertex vertex)
        {
            vertex.pos.x = (vertex.pos.x - (_windowSize.x * 0.5f))
                                        /
                                (_windowSize.x*0.5f);
            vertex.pos.y = (vertex.pos.y - (_windowSize.y * 0.5f))
                                        /
                                (_windowSize.y*0.5f);
            std::cout << "px vec: " << vertex.pos.x << " x " << vertex.pos.y << "\n";
            _VkDriver.addVertex(vertex);
        }

        void Window::draw(Engine::System::Graphics::Pipeline::Vertex vertex)
        {
            _VkDriver.addVertex(vertex);
        }

        void Window::draw(decltype(Engine::System::Graphics::Pipeline::Vertex::pos) pos)
        {
            _VkDriver.addVertex(
                {
                    .pos = pos,
                    .color = {1.0f, 1.0f, 1.0f}
                }
            );
        }

        void Window::clear()
        {
            _VkDriver.clearVertex();
        }

        void Window::display()
        {
            _VkDriver.draw();
            _VkDriver.qSumbit();
            _VkDriver.display();
        }

    }
}
