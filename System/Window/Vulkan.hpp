#ifdef WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#define VK_PROTOTYPES
#endif
#define GLFW_INCLUDE_VULKAN
#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <System/Graphics/System/RenderPool.hpp>
#include <System/Util.hpp>


namespace Engine {
    namespace Window {
        class Window;
        namespace Wrapper {

            class VulkanDriver {
                std::vector<Engine::System::Graphics::RenderPool> _render_queue;

                uint32_t _idxFamilyPresent;
                uint32_t _idxFamilyRender;
            protected:

                friend Window;

                VkPhysicalDevice _PhysicalDevice;
                VkDevice _device;

                VkQueue _renderq;
                VkQueue _presentq;

                VkInstance _instance;
                VkSurfaceKHR _surface;

                VkFormat _format;
                std::vector<VkImage> _swapchain_images; // Why are you swapchain, but I save all frames in images?
                std::vector<VkImageView> _swapchain_images_view;
                VkSwapchainKHR _swapchain;

                VkApplicationInfo _appInfo;

            public:
                // inline static int QueueCount = 0;

                void operator=(const VulkanDriver&) = delete;

                VulkanDriver(const VulkanDriver&) = delete;
                VulkanDriver();
                ~VulkanDriver();
                
                void init(std::vector<const char*> req_extension, std::vector<const char*> deviceExtension, GLFWwindow* window);
                void initFrameBuffer(uint32_t w_x, uint32_t w_y);
            };

        }
    }
}