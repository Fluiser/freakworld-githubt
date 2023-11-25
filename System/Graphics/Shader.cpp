#include "Shader.hpp"
#include <System/Util.hpp>
#include <fstream>

namespace Engine {
    namespace System {
        namespace Graphics {

            void Shader::destroy(VkDevice dev)
            {
                if(_isBinary)
                    vkDestroyShaderModule(dev, _shaderModule, nullptr);
            }

            bool Shader::isComplete() const noexcept
            {
                return (!_isBinary);
            }

            void Shader::createFromFile(VkDevice device, std::string path)
            {
                std::ifstream file(path, std::ios::binary);
                if(!file.is_open()) {
                    DEB_LOG("Shader (" << path << ") can't be read or not exist")
                }
                _program.insert(_program.begin(), std::istreambuf_iterator<char>(file), {});
                
                VkShaderModuleCreateInfo crInfo;
                ZeroMem(crInfo);
                crInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
                crInfo.codeSize = _program.size();
                crInfo.pCode = (const uint32_t*)_program.data();

                CRITICAL_VULKAN_CALLBACK(vkCreateShaderModule(device, &crInfo, nullptr, &_shaderModule));
                _isBinary = true;
            }

            void Shader::createFromMemory(VkDevice device, const char* mem, size_t size)
            {
                _program.resize(size);
                memcpy(_program.data(), mem, size);

                VkShaderModuleCreateInfo crInfo;
                ZeroMem(crInfo);
                crInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
                crInfo.codeSize = size;
                crInfo.pCode = (const uint32_t*)mem;

                CRITICAL_VULKAN_CALLBACK(vkCreateShaderModule(device, &crInfo, nullptr, &_shaderModule));
                _isBinary = true;
            }

        }
    }
}