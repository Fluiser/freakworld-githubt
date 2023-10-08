#pragma once
#include <Util/VInc.hpp>
#include <vector>
#include <System/Graphics/Shader.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace Engine {
    namespace Window {
        namespace Wrapper {
            class VulkanDriver; } 
        }

    namespace System {
        namespace Graphics {

            class Pipeline {
            public:
                class Vertex {
                public:
                    glm::vec2 pos;
                    glm::vec3 color;
                private:
                    static VkVertexInputBindingDescription getDescription();
                    static std::array<VkVertexInputAttributeDescription, 2> getAttribyteDescription();
                    friend class Pipeline;
                    friend class Engine::Window::Wrapper::VulkanDriver;
                };
            private:
                VkDevice _device;

                // static inline int countPipelines = 0;
                // static inline VkPipeline graphicsPipeline = nullptr;
                VkPipeline _graphicsPipeline;
                VkPipelineLayout _pipeLayout;
                VkRenderPass _renderPass;

                VkExtent2D _extent;

                std::vector<VkFramebuffer> _swapchain_framebuffers;
                std::vector<VkCommandBuffer> _commandBuffers;

                VkSemaphore _imageAvailable;
                VkSemaphore _renderFinished;

                friend Engine::Window::Wrapper::VulkanDriver;

                size_t _lastSizeMem = 0;
                VkDeviceMemory _devMem;
                VkBuffer _vertexBuffer;
                std::vector<Vertex> _vertex;
                VkPhysicalDeviceMemoryProperties _memProps;
            public:

                std::vector<Engine::System::Graphics::Shader> shaders;

                Pipeline() = default;
                ~Pipeline();

                void initPipeline(VkDevice, VkExtent2D, VkFormat, unsigned multisampling = 0, uint32_t maxBytesRequiresVRAM = 1024*1024*128);
                void initFramebuffers(std::vector<VkImageView>&, VkExtent2D);
                void initCommandBuffers(VkCommandPool cmdPool);

                void beginCommands(); // NEED SYNC
                void draw();
                void addVertex(Vertex);
                void clearVertex();
                size_t size();
                void endCommands(); // NEED SYNC

                void initMemType(VkPhysicalDevice dev);
                static uint32_t findMemType(uint32_t filter, VkMemoryPropertyFlags flag, VkPhysicalDeviceMemoryProperties& prop);

                // static void initGraphicsPipeline(Pipeline*, size_t);

            };

        }
    }
}
