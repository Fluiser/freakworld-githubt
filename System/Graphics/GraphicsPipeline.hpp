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

            public:

                std::vector<Engine::System::Graphics::Shader> shaders;

                Pipeline() = default;
                ~Pipeline();

                void initPipeline(VkDevice, VkExtent2D, VkFormat, unsigned multisampling = 0);

                // static void initGraphicsPipeline(Pipeline*, size_t);

            };

        }
    }
}