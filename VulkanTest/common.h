#pragma once
//��ɴ�����ز���,�Զ�������Vulkan���ͷ�ļ�
#define GLFW_INCLUDE_VULKAN
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE


#include <GLFW/glfw3.h>

//��������
#include <iostream>
#include <stdexcept>
//��Դ����
#include <functional>
//ʹ��EXIT_SUCCESS��EXIT_FAILURE��
#include <cstdlib>

#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <array>

//����������ļ�
#include <fstream>

//�ߴ���
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <chrono>

//���ڴ�С,���Ϊȫ�ֱ���
const int WIDTH = 800;
const int HEIGHT = 600;

//ģ��·��
const std::string MODEL_PATH = "../model/viking_room.obj";
const std::string TEXTURE_PATH = "../model/viking_room.png";

//���У���
const std::vector<const char*> validationLayers =
{
	"VK_LAYER_KHRONOS_validation"
};

//������豸��չ�б�
const std::vector<const char*> deviceExtensions =
{
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

//�Ƿ���DEBUGģʽ�����Ƿ���У���
#ifdef  NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif //  NDEBUG

//�������������
struct QueueFamilyIndices
{
	int graphicsFamily = -1;
	int presentFamily = -1;

	bool isComplete()
	{
		return graphicsFamily >= 0 && presentFamily >= 0;
	}
};

//���潻����ϸ����Ϣ
struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

const int MAX_FRAMES_IN_FLIGHT = 2;

//����Ľṹ
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

////������������ɫ
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

//������������,��ű任����
struct UniformBufferObject
{
	alignas(16) glm::mat4 model;
	alignas(16) glm::mat4 view;
	alignas(16) glm::mat4 proj;
};