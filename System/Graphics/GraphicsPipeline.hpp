#pragma once
#include <Util/VInc.hpp>
#include <vector>
#include <System/Graphics/Shader.hpp>

namespace Engine {
    namespace System {
        namespace Graphics {

            class Pipeline {
            public:

                std::vector<Engine::System::Graphics::Shader> shaders;

                Pipeline() = default;
                ~Pipeline();

                void initPipeline();


            };

        }
    }
}