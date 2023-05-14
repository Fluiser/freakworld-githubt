#pragma once
#include <Util/VInc.hpp>
#include <vector>
#include <System/Graphics/Shader.hpp>

namespace Engine {
    namespace System {
        namespace Graphics {

            class Pipeline {
                VkDevice _device;
            public:

                std::vector<Engine::System::Graphics::Shader> shaders;

                Pipeline() = default;
                ~Pipeline();

                void initPipeline(VkDevice, VkExtent2D, unsigned multisampling = 0);


            };

        }
    }
}