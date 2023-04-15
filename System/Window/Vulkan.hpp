#include <GLFW/glfw3.h>
#if defined(WIN32)
#define VK_USE_PLATFORM_WIN32_KHR
#else
#define VK_USE_PLATFORM_XCB_KHR
#endif
#include <vulkan/vulkan.hpp>
#include <vector>
#include <string>
#include <System/Graphics/System/RenderPool.hpp>


namespace Engine {
    namespace Window {
        class Window;
        namespace Wrapper {

            class VulkanDriver {
                std::vector<Engine::System::Graphics::RenderPool> _render_queue;
            protected:

                friend Window;

                VkPhysicalDevice _PhysicalDevice;
                VkDevice _device;

                VkApplicationInfo appInfo{};
                VkInstance instance;
                VkSurfaceKHR surface;
            public:
                void operator=(const VulkanDriver&) = delete;

                VulkanDriver(const VulkanDriver&) = delete;
                VulkanDriver();
                ~VulkanDriver();
                
                void init(std::vector<const char*> req_extension);
            };

        }
    }
}