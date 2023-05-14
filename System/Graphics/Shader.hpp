#pragma once
#include <Util/VInc.hpp>
#include <vector>
#include <string>

namespace Engine {
    namespace System {
        namespace Graphics {
            class Shader {
                bool _isBinary = false;
                std::vector<char> _program;
                VkShaderModule _shaderModule = nullptr;

                VkDevice _p_dev;
            public:

                Shader() = default;
                ~Shader();

                VkShaderModule& get();
                const VkShaderModule& get() const;

                bool isComplete() const noexcept;

                void createFromFile(VkDevice device, std::string path);
                void createFromMemory(VkDevice device, const char* memory, size_t size);
            };
        }
    }
}