#include <GLFW/glfw3.h>
#if defined(WIN32)
#define VK_USE_PLATFORM_WIN32_KHR
#else
#define VK_USE_PLATFORM_XCB_KHR
#endif
#include <vulkan/vulkan.hpp>
#include <vector>


namespace Engine {
    namespace Window {
        class Window;
        namespace Wrapper {
            
            class VulkanDriver {
            protected:

                friend Window;

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