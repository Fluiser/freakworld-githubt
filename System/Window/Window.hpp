#pragma once
#ifdef WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#define VK_PROTOTYPES
#endif
#define GLFW_INCLUDE_VULKAN

#include <System/Window/Vulkan.hpp>
#include <GLFW/glfw3.h>
#include <System/Util.hpp>
#include <errors.h>
#include <string>
#include <mutex>

#include <System/IODevices/Event.hpp>

namespace Engine{
    namespace Window {
        class Window {
        private:
            GLFWwindow* _window;
            std::string _window_title;
            std::mutex _event_mtx;

            Wrapper::VulkanDriver _VkDriver;

            Math::vec2i _windowSize;
        public:

            Window(const Window&) = delete;
            Window();
            ~Window();

            void init(  Math::vec2i size,
                        std::string&& title,
                        std::initializer_list<std::pair<int, int>> settings = {
                            {GLFW_CLIENT_API, GLFW_NO_API},
                            {GLFW_RESIZABLE, GLFW_TRUE}
                        },
                        GLFWmonitor* monitor = nullptr);
            Engine::IODevices::Event waitEvent();
            inline bool ShouldClose()
            { return glfwWindowShouldClose(_window); }

            void display();
            void draw();
        };
    }
}