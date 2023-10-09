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
            auto& vxr = _VkDriver.getVertex();

            static constexpr auto move_vertx = [](std::pair<System::Graphics::Pipeline::Vertex&, float>& a, std::pair<System::Graphics::Pipeline::Vertex&, float>& b)
            {
                auto t = b.first;
                b.first = a.first;
                a.first = t;

                float tf = b.second;
                b.second = a.second;
                a.second = tf;
            };
            static constexpr auto distance_vertx = [](const glm::vec2& a) -> float {
                return sqrt(a.x*a.x + a.y*a.y);
            };
            static constexpr auto handleFreakAtanh = [](float& x)
            {
                if(x < 0)
                    x = M_PI + x + M_PI;
            };

            for(uint32_t i = 2; i < vxr.size(); i += 3)
            {                
                auto& an = vxr[i-2];
                auto& bn = vxr[i-1];
                auto& cn = vxr[i];

                glm::vec2 center{
                    (an.pos.x + bn.pos.x + cn.pos.x) / 3,
                    (an.pos.y + bn.pos.y + cn.pos.y) / 3
                };

                std::pair<System::Graphics::Pipeline::Vertex&, float> c(vxr[i],     atan2f(vxr[i].pos.y +   center.y,    vxr[i].pos.x  + center.x));
                std::pair<System::Graphics::Pipeline::Vertex&, float> b(vxr[i-1],   atan2f(vxr[i-1].pos.y  + center.y,  vxr[i-1].pos.x  + center.x));
                std::pair<System::Graphics::Pipeline::Vertex&, float> a(vxr[i-2],   atan2f(vxr[i-2].pos.y  + center.y,  vxr[i-2].pos.x  + center.x));



                if( c.second < b.second)
                {
                    move_vertx(c, b);
                }
                if( b.second < a.second )
                {
                    move_vertx(a,b);   
                }
                if( c.second < b.second)
                {
                    move_vertx(c, b);
                }               
            }
            _VkDriver.draw();
            _VkDriver.qSumbit();
            _VkDriver.display();
        }

    }
}