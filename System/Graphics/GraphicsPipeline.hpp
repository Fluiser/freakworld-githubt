#pragma once
#include <Util/VInc.hpp>
#include <vector>
#include <System/Graphics/Shader.hpp>

namespace Engine {
    namespace System {
        namespace Graphics {

            class Pipeline {
                VkDevice _device;

                // static inline int countPipelines = 0;
                // static inline VkPipeline graphicsPipeline = nullptr;
                VkPipeline _graphicsPipeline;
                VkPipelineLayout _pipeLayout;
                VkRenderPass _renderPass;

                VkExtent2D _extent;

                std::vector<VkFramebuffer> _swapchain_framebuffers;
                std::vector<VkCommandBuffer> _commandBuffers;
            public:

                std::vector<Engine::System::Graphics::Shader> shaders;

                Pipeline() = default;
                ~Pipeline();

                void initPipeline(VkDevice, VkExtent2D, VkFormat, unsigned multisampling = 0);
                void initFramebuffers(std::vector<VkImageView>&, VkExtent2D);
                void initCommandBuffers(VkCommandPool cmdPool);

                void beginCommands(); // NEED SYNC
                void draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);
                void endCommands(); // NEED SYNC


                // static void initGraphicsPipeline(Pipeline*, size_t);

            };

        }
    }
}