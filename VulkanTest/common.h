#pragma once
//完成窗口相关操作,自动包含了Vulkan库的头文件
#define GLFW_INCLUDE_VULKAN
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE


#include <GLFW/glfw3.h>

//用来报错
#include <iostream>
#include <stdexcept>
//资源管理
#include <functional>
//使用EXIT_SUCCESS和EXIT_FAILURE宏
#include <cstdlib>

#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <array>

//载入二进制文件
#include <fstream>

//线代库
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <chrono>

//窗口大小,设计为全局变量
const int WIDTH = 800;
const int HEIGHT = 600;

//模型路径
const std::string MODEL_PATH = "../model/viking_room.obj";
const std::string TEXTURE_PATH = "../model/viking_room.png";

//添加校验层
const std::vector<const char*> validationLayers =
{
	"VK_LAYER_KHRONOS_validation"
};

//所需的设备扩展列表
const std::vector<const char*> deviceExtensions =
{
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

//是否处于DEBUG模式决定是否开启校验层
#ifdef  NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif //  NDEBUG

//保存队列族索引
struct QueueFamilyIndices
{
	int graphicsFamily = -1;
	int presentFamily = -1;

	bool isComplete()
	{
		return graphicsFamily >= 0 && presentFamily >= 0;
	}
};

//保存交换链细节信息
struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

const int MAX_FRAMES_IN_FLIGHT = 2;

//顶点的结构
struct Vertex
{
	glm::vec3 pos;
	glm::vec3 color;
	glm::vec2 texCoord;

	static VkVertexInputBindingDescription getBindingDescription()
	{
		VkVertexInputBindingDescription bindingDescription {};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return bindingDescription;
	}

	static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions()
	{
		std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions {};

		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);

		attributeDescriptions[2].binding = 0;
		attributeDescriptions[2].location = 2;
		attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

		return attributeDescriptions;
	}

	bool operator ==(const Vertex& other)const
	{
		return pos == other.pos && color == other.color && texCoord == other.texCoord;
	}
};

////顶点的坐标和颜色
//const std::vector<Vertex> vertices =
//{
//	{{-1.0f, -1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
//	{{1.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
//	{{1.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
//	{{-1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
//
//	{{-1.0f, -1.0f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
//	{{1.0f, -1.0f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
//	{{1.0f, 1.0f, -0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
//	{{-1.0f, 1.0f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
//};
//
//const std::vector<uint16_t> indices =
//{
//	0, 1, 2, 2, 3, 0,
//	4, 5, 6, 6, 7, 4
//};

//设置描述符集,存放变换矩阵
struct UniformBufferObject
{
	alignas(16) glm::mat4 model;
	alignas(16) glm::mat4 view;
	alignas(16) glm::mat4 proj;
};