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
                vkFreeMemory(_device, _devMem, nullptr);
                vkDestroyBuffer(_device, _vertexBuffer, nullptr);
                for(auto& framebuffer: _swapchain_framebuffers)
                {
                    vkDestroyFramebuffer(_device, framebuffer, nullptr);
                }
                vkDestroyPipelineLayout(_device, _pipeLayout, nullptr);
                vkDestroyRenderPass(_device, _renderPass, nullptr);
                vkDestroySemaphore(_device, _imageAvailable, nullptr);
                vkDestroySemaphore(_device, _renderFinished, nullptr);
            }

            void Pipeline::initPipeline(
                VkDevice device,
                VkExtent2D extent,
                VkFormat format,
                unsigned multisamplingOption)
            {
                _extent = extent;
                _device = device;
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
                ZeroMem(frag);
                frag.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
                frag.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
                shaders.emplace_back();
                auto& fragShader = shaders.back();
                fragShader.createFromFile(device, "frag.spv");
                frag.module = fragShader._shaderModule;
                frag.pName = ProgramEntryName;

                VkPipelineShaderStageCreateInfo shaderStages[] = {vrx, frag};
//////////////////////////////////pipeline////////////////////////////////////////////
                VkPipelineVertexInputStateCreateInfo vertexIInfo;
                ZeroMem(vertexIInfo);
                vertexIInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

                ////////////////shaders///////////////////
                auto bindDesc = Vertex::getDescription();
                auto attrdDesc = Vertex::getAttribyteDescription();

                vertexIInfo.vertexBindingDescriptionCount = 1;
                vertexIInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attrdDesc.size());
                vertexIInfo.pVertexBindingDescriptions = &bindDesc;
                vertexIInfo.pVertexAttributeDescriptions = attrdDesc.data();
                //////////////////////////////////////////

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
                raster.lineWidth = 1.0f;
                raster.cullMode = VK_CULL_MODE_BACK_BIT;
                raster.frontFace = VK_FRONT_FACE_CLOCKWISE;
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

                VkPipelineColorBlendAttachmentState crBlendAttachment;
                ZeroMem(crBlendAttachment);
                crBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
                crBlendAttachment.blendEnable = VK_FALSE;
                // if blendEnable is VK_TRUE
                crBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
                crBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
                crBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
                crBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
                crBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
                crBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;
                ///////////////////////////////////////

                VkPipelineColorBlendStateCreateInfo colorBlending;
                ZeroMem(colorBlending);
                colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
                colorBlending.logicOpEnable = VK_FALSE;
                colorBlending.logicOp = VK_LOGIC_OP_COPY;
                colorBlending.attachmentCount = 1;
                colorBlending.pAttachments = &crBlendAttachment;

#ifdef __VULKAN_DYNAMIC_LINE
                VkDynamicState __states = VK_DYNAMIC_STATE_LINE_WIDTH;
                VkPipelineDynamicStateCreateInfo DSCI;
                ZeroMem(DSCI);
                DSCI.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
                DSCI.dynamicStateCount = 1;
                DSCI.pDynamicStates = &__states;
#endif
                VkPipelineLayoutCreateInfo pipelayout;
                ZeroMem(pipelayout);
                pipelayout.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
                CRITICAL_VULKAN_CALLBACK(vkCreatePipelineLayout(_device, &pipelayout, nullptr, &_pipeLayout));

                VkAttachmentDescription colorAttachment;
                ZeroMem(colorAttachment);
                colorAttachment.format = format;
                colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
                colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR; 
                colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;

                colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
                colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

                colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
                colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

                //@ColorAttachments
                VkAttachmentReference colorAttachmentRef;
                colorAttachmentRef.attachment = 0;
                colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

                VkSubpassDescription subpass;
                ZeroMem(subpass);
                subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
                subpass.colorAttachmentCount = 1;
                subpass.pColorAttachments = &colorAttachmentRef;

                VkSubpassDependency dependency;
                ZeroMem(dependency);
                dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
                dependency.dstSubpass = 0;
                dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
                dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
                dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
                dependency.srcAccessMask = 0;

                VkRenderPassCreateInfo renderPassInfo;
                ZeroMem(renderPassInfo);
                renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
                renderPassInfo.attachmentCount = 1;
                renderPassInfo.pAttachments = &colorAttachment;
                renderPassInfo.subpassCount = 1;
                renderPassInfo.pSubpasses = &subpass;
                renderPassInfo.dependencyCount = 1;
                renderPassInfo.pDependencies = &dependency;

                CRITICAL_VULKAN_CALLBACK(vkCreateRenderPass(_device, &renderPassInfo, nullptr, &_renderPass));

                VkGraphicsPipelineCreateInfo pipelineInfo;
                ZeroMem(pipelineInfo);
                pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
                pipelineInfo.stageCount = 2;
                pipelineInfo.pStages = shaderStages;

                pipelineInfo.pVertexInputState = &vertexIInfo;
                pipelineInfo.pInputAssemblyState = &assemblyIInfo;
                pipelineInfo.pViewportState = &viewportstate;
                pipelineInfo.pRasterizationState = &raster;
                pipelineInfo.pMultisampleState = &multisampling;
                pipelineInfo.pDepthStencilState = nullptr;
                pipelineInfo.pColorBlendState = &colorBlending;
                pipelineInfo.pTessellationState = nullptr;
#ifdef __VULKAN_DYNAMIC_LINE
                pipelineInfo.pDynamicState = &DSCI;
#else
                pipelineInfo.pDynamicState = nullptr;
#endif
                pipelineInfo.layout = _pipeLayout;
                pipelineInfo.renderPass = _renderPass;
                pipelineInfo.subpass = 0;

                //@pipeline
                pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
                pipelineInfo.basePipelineIndex = -1;
                /*
                    @initGraphicsPipeline
                    Хоть и смысл в том, что может быть много граф. конвеейеров,
                    но на данный момент это не нужно и пока не реализовано.

                    Надо вынести все требующиеся аргументы в члены класса, потому как вызвать vkCreateGraphisPipelines с структурами, которые удалены - не очень хорошая идея.
                    @костыль
                */
                CRITICAL_VULKAN_CALLBACK(vkCreateGraphicsPipelines(_device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &_graphicsPipeline));           

                VkSemaphoreCreateInfo SemaphoreInfo;
                ZeroMem(SemaphoreInfo);
                SemaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

                CRITICAL_VULKAN_CALLBACK(vkCreateSemaphore(device, &SemaphoreInfo, nullptr, &_imageAvailable));
                CRITICAL_VULKAN_CALLBACK(vkCreateSemaphore(device, &SemaphoreInfo, nullptr, &_renderFinished));
            }

            void Pipeline::initMemType(VkPhysicalDevice dev)
            {
                vkGetPhysicalDeviceMemoryProperties(dev, &_memProps);
            }

            void Pipeline::initFramebuffers(std::vector<VkImageView>& swapchainImageView, VkExtent2D extent)
            {
                _swapchain_framebuffers.resize(swapchainImageView.size());
                for(size_t i = 0; i < swapchainImageView.size(); ++i)
                {
                    VkFramebufferCreateInfo createInfo;
                    ZeroMem(createInfo);
                    createInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
                    createInfo.renderPass = _renderPass;
                    createInfo.attachmentCount = 1;
                    createInfo.pAttachments = &swapchainImageView[i];
                    createInfo.width = extent.width;
                    createInfo.height = extent.height;
                    createInfo.layers = 1;

                    CHECK_VULKAN_CALLBACK(vkCreateFramebuffer(_device, &createInfo, nullptr, &_swapchain_framebuffers[i]));
                }
            }

            void Pipeline::initCommandBuffers(VkCommandPool cmdPool)
            {
                _commandBuffers.resize(_swapchain_framebuffers.size());

                VkCommandBufferAllocateInfo info;
                ZeroMem(info);
                info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
                info.commandPool = cmdPool;
                info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
                info.commandBufferCount = (uint32_t)_commandBuffers.size();
                //Можно создать ещё буффер команд, который будет вспомогательным и будет использованы в первичном буфере для воспроизведения часто используемых команд.

                CRITICAL_VULKAN_CALLBACK(vkAllocateCommandBuffers(_device, &info, _commandBuffers.data()));
            }

            void Pipeline::endCommands()
            {
                for(auto& cmd: _commandBuffers)
                {
                    vkCmdEndRenderPass(cmd);
                    CHECK_VULKAN_CALLBACK(vkEndCommandBuffer(cmd));
                }

                vkDestroyBuffer(_device, _vertexBuffer, nullptr); // Если вызвано во время рендера - то игра в рулетку.

                VkBufferCreateInfo bufferInfo;
                ZeroMem(bufferInfo);
                bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
                bufferInfo.size = (sizeof(_vertex[0]) * _vertex.size());
                bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
                bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE; // Только для одного семейства рендера. //@option

                CRITICAL_VULKAN_CALLBACK(vkCreateBuffer(_device, &bufferInfo, nullptr, &_vertexBuffer));

                if(_lastSizeMem < (sizeof(_vertex[0]) * _vertex.size()))
                {
                    _lastSizeMem = bufferInfo.size;

                    if(_lastSizeMem > 0)
                    {
                        vkFreeMemory(_device, _devMem, nullptr);
                    }

                    VkMemoryRequirements memreq;
                    ZeroMem(memreq);
                    vkGetBufferMemoryRequirements(_device, _vertexBuffer, &memreq);

                    VkMemoryAllocateInfo allocInfo;
                    ZeroMem(allocInfo);
                    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
                    allocInfo.allocationSize = memreq.size;
                    allocInfo.memoryTypeIndex = findMemType(memreq.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, _memProps);

                    CRITICAL_VULKAN_CALLBACK(vkAllocateMemory(_device, &allocInfo, nullptr, &_devMem));
                }

                CRITICAL_VULKAN_CALLBACK(vkBindBufferMemory(_device, _vertexBuffer, _devMem, 0));
                void* data;
                vkMapMemory(_device, _devMem, 0, bufferInfo.size, 0, &data);
                memcpy(data, _vertex.data(), (size_t)bufferInfo.size);
                vkUnmapMemory(_device, _devMem);
            }

            void Pipeline::clearVertex()
            {
                _vertex.clear();
            }

            size_t Pipeline::size()
            {
                return _vertex.size();
            }

            void Pipeline::addVertex(Vertex x)
            {
                _vertex.emplace_back(x);
            }

            void Pipeline::draw()
            {
                for(int i = 0; i < _swapchain_framebuffers.size(); ++i)
                {
                    vkCmdBindPipeline(_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, _graphicsPipeline);
                    VkDeviceSize offsets[] = {0};
                    vkCmdBindVertexBuffers(_commandBuffers[i], 0, 1, &_vertexBuffer, offsets);
                    vkCmdDraw(_commandBuffers[i], static_cast<uint32_t>(_vertex.size()), 1, 0, 0);
                }
            }  

            void Pipeline::beginCommands()
            {
                VkClearValue clearValue = {0.0f, 0.0f, 0.0f, 1.0f};
                for(int i = 0; i < _swapchain_framebuffers.size(); ++i)
                {
                    VkCommandBufferBeginInfo begin;
                    ZeroMem(begin);
                    begin.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
                    begin.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
                    begin.pInheritanceInfo = nullptr;

                    CHECK_VULKAN_CALLBACK(vkBeginCommandBuffer(_commandBuffers[i], &begin));

                    VkRenderPassBeginInfo rpass;
                    ZeroMem(rpass);
                    rpass.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
                    rpass.renderPass = _renderPass;
                    rpass.framebuffer = _swapchain_framebuffers[i];
                    rpass.renderArea.extent = _extent;
                    //rpass.renderArea.offset sets from ZeroMem
                    rpass.clearValueCount = 1;
                    rpass.pClearValues = &clearValue;
                    
                    vkCmdBeginRenderPass(_commandBuffers[i], &rpass, VK_SUBPASS_CONTENTS_INLINE);
                    vkCmdBindPipeline(_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, _graphicsPipeline);
                }
            }

            VkVertexInputBindingDescription Pipeline::Vertex::getDescription() 
            {
                return VkVertexInputBindingDescription {
                    .binding = 0,
                    .stride = sizeof(Pipeline::Vertex),
                    .inputRate = VK_VERTEX_INPUT_RATE_VERTEX
                };
            }
            std::array<VkVertexInputAttributeDescription, 2> Pipeline::Vertex::getAttribyteDescription()
            {
                static std::array<VkVertexInputAttributeDescription, 2> array{};

                array[0].binding = 0;
                array[0].location = 0;
                array[0].format = VK_FORMAT_R32G32_SFLOAT;
                array[0].offset = offsetof(Vertex, pos);

                array[1].binding = 0;
                array[1].location = 1;
                array[1].format = VK_FORMAT_R32G32B32_SFLOAT;
                array[1].offset = offsetof(Vertex, color);

                return array;
            }

            uint32_t Pipeline::findMemType(uint32_t filter, VkMemoryPropertyFlags flag, VkPhysicalDeviceMemoryProperties& prop)
            {
                for(uint32_t i = 0; i < prop.memoryTypeCount; ++i)
                {
                    if(
                        (filter & (1 << i)) &&
                        (prop.memoryTypes[i].propertyFlags & flag)
                    )
                        return i;
                }
                DEB_LOG("uint32_t Pipeline::findMemType(uint32_t filter, VkMemoryPropertyFlags flag, VkPhysicalDeviceMemoryProperties& prop): Can't find memory type\n");
                return 0;
            }
        }
    }
}
