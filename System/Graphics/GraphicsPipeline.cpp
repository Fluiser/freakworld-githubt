#include "GraphicsPipeline.hpp"
#include <System/Util.hpp>

namespace {
    const char* ProgramEntryName = "main";
}

namespace Engine {
    namespace System {
        namespace Graphics {
            
            Pipeline::~Pipeline()
            {
                for(auto& s: shaders)
                {
                    s.destroy(_device);
                }
            }

            void Pipeline::initPipeline(
                VkDevice device,
                VkExtent2D extent,
                unsigned multisamplingOption)
            {
///////////////////////////////SHADERS////////////////////////////////
                for(auto& s: shaders)
                    s.destroy(device);
                shaders.resize(0);
                shaders.reserve(2);

                VkPipelineShaderStageCreateInfo vrx;
                ZeroMem(vrx);
                vrx.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
                vrx.stage = VK_SHADER_STAGE_VERTEX_BIT;
                shaders.emplace_back();
                auto& vrxShader = shaders.back();
                vrxShader.createFromFile(device, "vert.spv");
                vrx.module = vrxShader._shaderModule;
                vrx.pName = ProgramEntryName;

                VkPipelineShaderStageCreateInfo frag;
                frag.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
                frag.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
                shaders.emplace_back();
                auto& fragShader = shaders.back();
                fragShader.createFromFile(device, "frag.spv");
                frag.module = fragShader._shaderModule;
                frag.pName = ProgramEntryName;
//////////////////////////////////pipeline////////////////////////////////////////////
                VkPipelineVertexInputStateCreateInfo vertexIInfo;
                ZeroMem(vertexIInfo);
                vertexIInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

                VkPipelineInputAssemblyStateCreateInfo assemblyIInfo;
                ZeroMem(assemblyIInfo);
                assemblyIInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
                assemblyIInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
                assemblyIInfo.primitiveRestartEnable = VK_FALSE;

                VkViewport viewport;
                ZeroMem(viewport);
                viewport.y = viewport.x = 0.0f;
                viewport.width = (float)extent.width;
                viewport.height = (float)extent.height;
                viewport.maxDepth = 1.0f;
                viewport.minDepth = 0.0f;

                VkRect2D scissor;
                scissor.offset = {0, 0};
                scissor.extent = extent;

                VkPipelineViewportStateCreateInfo viewportstate;
                ZeroMem(viewportstate);
                viewportstate.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
                viewportstate.viewportCount = 1;
                viewportstate.pViewports = &viewport;
                viewportstate.scissorCount = 1;
                viewportstate.pScissors = &scissor;

                VkPipelineRasterizationStateCreateInfo raster;
                ZeroMem(raster);
                raster.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
                raster.rasterizerDiscardEnable = VK_FALSE;
                raster.depthClampEnable = VK_FALSE;
                raster.polygonMode = VK_POLYGON_MODE_FILL;
                // raster.lineWidth = 1.0f;
                //raster.cullMode = VK_CULL_MODE_BACK_BIT;
                //raster.frontFace = VK_FRONT_FACE_CLOCKWISE;
                raster.depthBiasEnable = VK_FALSE;

                VkPipelineMultisampleStateCreateInfo multisampling;
                ZeroMem(multisampling);
                multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
                multisampling.sampleShadingEnable = multisamplingOption > 0 ? VK_TRUE : VK_FALSE;
                multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
                multisampling.minSampleShading = 1.0f;
                multisampling.pSampleMask = nullptr;
                multisampling.alphaToCoverageEnable = VK_TRUE;
                multisampling.alphaToOneEnable = VK_FALSE;

                
            }
        }
    }
}
