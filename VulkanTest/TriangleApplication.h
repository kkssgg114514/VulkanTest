#pragma once
#include "common.h"

//�������װ����
class TriangleApplication
{
public:
	void run();

private:
	//��ʼ��GLFW
	void initWindow();

	//������Դ�ĳ�ʼ��
	void initVulkan();

	void mainLoop();

	//������Դ������
	void cleanup();

	//����ʵ��
	void createInstance();

	//�����ȡ����չ�Ƿ�����չ֧���б���
	bool isExtensionSupport(std::vector<const char*> glfwExtensions);

	//�������п��õ�У���
	bool checkValidationLayerSupport();

	//�����Ƿ�����У��㷵��������չ
	std::vector<const char*> getRequiredExtensions();

	//��vkDebugUtilsMessengerCallbackEXTΪԭ�͵ľ�̬����
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData);

	//���õ��Իص�����
	void setupDebugCallback();

	//��ѯϵͳ�е��Կ��豸,ѡ��һ��֧��������豸ʹ��
	void pickPhysicalDevice();

	//����ȡ���豸�Ƿ��������
	bool isDeviceSuitable(VkPhysicalDevice device);

	//���豸��Ȩ���
	int rateDeviceSuitability(VkPhysicalDevice device);

	//������Ҫ�Ķ�����
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

	//�����߼��豸
	void createLogicalDevice();

	//�������ڱ���
	void createSurface();

	//����豸��չ֧��
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);

	//��д��������Ϣ
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

	//ѡ����ʵı����ʽ
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

	//ѡ����ʵĳ���ģʽ
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);

	//ѡ����ʵĽ�����Χ
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	//�������ϼ���������������������
	void createSwapChain();

	//����ͼ����ͼ
	void createImageViews();
	//�򻯴���
	VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);

	//����ͼ�ι���
	void createGraphicsPipeline();

	//����������ļ�
	static std::vector<char> readFile(const std::string& filename);

	//������ɫ��ģ��
	VkShaderModule createShaderModule(const std::vector<char>& code);

	//��Ⱦ����
	void createRenderPass();

	//����֡�������Ĵ���
	void createFramebuffers();

	//����ָ���
	void createCommandPool();

	//��¼ָ��
	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

	//Ϊ�������е�ÿһ��ͼ�񴴽�ָ������
	void createCommandBuffers();

	//���ƺ���
	void drawFrame();

	//�����ź�������
	void createSyncObjects();

	//�ؽ�������.����һ�Ѻ���
	void recreateSwapChain();

	//������������ָ��,�����ؽ�,ͨ���ڴ��ڴ�С�ı�ʱ
	void cleanupSwapChain();

	//���ڴ�С�ı�ʱ�ĺ���
	static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

	//�������㻺��
	void createVertexBuffer();

	//������������
	void createIndexBuffer();

	//��ѯ����ʵ��ڴ�����
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

	//��������ĸ�������
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties,
					  VkBuffer& buffer, VkDeviceMemory& bufferMemory);

	//�ڻ���֮�临������
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	//���������������,��������ָ���¼��ָ���
	VkCommandBuffer beginSingleTimeCommands();
	void endSingleTimeCommands(VkCommandBuffer commandBuffer);

	//�ṩ��ɫ��ʵ�õ�ÿһ��������������
	void createDescriptorSetLayout();

	void createUniformBuffers();

	//����uniform������
	void updateUniformBuffer(uint32_t currentImage);

	//������������
	void createDescriptorPool();
	//������������
	void createDescriptorSets();

	//��������ͼ��
	void createTextureImage();

	//��ͼ�����Ĳ���
	void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkFormat format, VkImageTiling tiling,
					 VkImageUsageFlagBits usage, VkMemoryPropertyFlags properties,
					 VkImage& image, VkDeviceMemory& imageMemory);

	//����ͼ�񲼾ֱ任
	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);

	//���ƻ��嵽ͼ��
	void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

	//����ͼ����ͼ����
	void createTextureImageView();

	//ʹ�ò��������������ݽ��в���
	void createTextureSampler();

	//�������ͼ����Ҫ����Դ
	void createDepthResources();

	//���Ҽȷ�����Ҫ,�豸��֧�ֵ�ͼ���ʽ
	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	//�����ʺ���Ϊ��ȸ��ŵ�ͼ�����ݸ�ʽ
	VkFormat findDepthFormat();

	//����ģ��
	void loadModel();

	//����ԭʯ����ͼ��ͬϸ������
	void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);
private:
	//���ھ��
	GLFWwindow* window;

	//�洢ʵ�����
	VkInstance instance;

	//�洢�ص�������Ϣ
	VkDebugUtilsMessengerEXT callback;

	//�洢ѡ��ʹ�õ��Կ���Ϣ
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

	//�洢�߼��豸�Ķ���
	VkDevice device;

	//�洢�߼��豸�Ķ��о��
	VkQueue graphicsQueue;

	//�洢���ڱ���
	VkSurfaceKHR surface;

	//�������ֶ���
	VkQueue presentQueue;

	//�洢������
	VkSwapchainKHR swapChain;

	//�洢ͼ����
	std::vector<VkImage> swapChainImages;

	//�洢������ͼ��ĸ�ʽ�ͷ�Χ
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;

	//�洢ͼ����ͼ
	std::vector<VkImageView> swapChainImageViews;

	//��Ⱦ����
	VkRenderPass renderPass;

	//��������Ʋ���
	VkDescriptorSetLayout descriptorSetLayout;

	//���߲㼶
	VkPipelineLayout pipelineLayout;

	//�洢����
	VkPipeline graphicsPipeline;

	//�洢���е�֡�������
	std::vector<VkFramebuffer> swapChainFramebuffers;

	//�洢ָ���
	VkCommandPool commandPool;

	//�����
	std::vector<VkCommandBuffer> commandBuffers;

	////ͨ���ź������ָ���Լ��,ͼ���ѻ�ȡ����Ⱦ�����
	//VkSemaphore imageAvilableSemaphore;
	//VkSemaphore renderFinishedSemaphore;
	//Ϊ�˱���ͬ������,Ϊÿһ֡����ר���ź���
	std::vector<VkSemaphore> imageAvilableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	//Ϊÿһ֡����һ��դ������
	std::vector<VkFence> inFlightFences;
	//׷�ٵ�ǰ��֡
	size_t currentFrame = 0;

	//��Ǵ��ڴ�С�Ƿ�ı�
	bool framebufferResized = false;

	//���㻺��
	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	//��������
	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;

	//���������ݵĻ���
	std::vector<VkBuffer> uniformBuffers;
	std::vector<VkDeviceMemory> uniformBuffersMemory;

	//�����������ض���
	VkDescriptorPool descriptorPool;
	std::vector<VkDescriptorSet> descriptorSets;

	//�洢�������ϸ���������
	uint32_t mipLevels;
	//ʹ��Vulkan��ͼ��
	VkImage textureImage;
	VkDeviceMemory textureImageMemory;

	//�洢����ͼ���ͼ����ͼ����
	VkImageView textureImageView;
	VkSampler textureSampler;

	//���ͼ��Ҫ����Դ
	VkImage depthImage;
	VkDeviceMemory depthImageMemory;
	VkImageView depthImageView;
	
};