#ifdef WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#define VK_PROTOTYPES
#endif
#define GLFW_INCLUDE_VULKAN
#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <System/Util.hpp>
#include <System/Graphics/GraphicsPipeline.hpp>


namespace Engine {
    namespace Window {
        class Window;
        namespace Wrapper {

            class VulkanDriver {

                uint32_t _idxFamilyPresent;
                uint32_t _idxFamilyRender;
                VkExtent2D _extent;

                friend Window;

                VkPhysicalDevice _PhysicalDevice;
                VkDevice _device;

                VkQueue _renderq;
                VkQueue _presentq;

                VkCommandPool _renderPool;
                VkCommandPool _presentPool;

                VkInstance _instance;
                VkSurfaceKHR _surface;

                VkFormat _format;
                std::vector<VkImage> _swapchain_images; // Why are you swapchain, but I save all frames in images?
                std::vector<VkImageView> _swapchain_images_views;

                VkSwapchainKHR _swapchain;

                std::vector<Engine::System::Graphics::Pipeline> _pipelines;

                VkApplicationInfo _appInfo;

                bool __BigEndian; // if true - format VK_FORMAT_R8G8B8A8_SRGB. or VK_FORMAT_B8G8R8A8_SRGB if false.

            protected:
                uint32_t getIndexImage(Engine::System::Graphics::Pipeline* = nullptr) const;
                uint32_t _indexImage;
            public:
                // inline static int QueueCount = 0;

                void operator=(const VulkanDriver&) = delete;

                VulkanDriver(const VulkanDriver&) = delete;
                VulkanDriver();
                ~VulkanDriver();
                
                void init(std::vector<const char*> req_extension, std::vector<const char*> deviceExtension, GLFWwindow* window);
                void initFrameBuffer(GLFWwindow*);

                void qSumbit(Engine::System::Graphics::Pipeline* = nullptr);
                void display(Engine::System::Graphics::Pipeline* = nullptr);

                void draw();
            };

        }
    }
}