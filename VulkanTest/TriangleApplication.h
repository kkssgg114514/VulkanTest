#pragma once
#include "common.h"

//将程序包装成类
class TriangleApplication
{
public:
	void run();

private:
	//初始化GLFW
	void initWindow();

	//所有资源的初始化
	void initVulkan();

	void mainLoop();

	//所有资源的清理
	void cleanup();

	//创建实例
	void createInstance();

	//检验获取的扩展是否在扩展支持列表中
	bool isExtensionSupport(std::vector<const char*> glfwExtensions);

	//请求所有可用的校验层
	bool checkValidationLayerSupport();

	//根据是否启用校验层返回所需扩展
	std::vector<const char*> getRequiredExtensions();

	//以vkDebugUtilsMessengerCallbackEXT为原型的静态函数
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData);

	//设置调试回调函数
	void setupDebugCallback();

	//查询系统中的显卡设备,选择一个支持所需的设备使用
	void pickPhysicalDevice();

	//检查获取的设备是否符合需求
	bool isDeviceSuitable(VkPhysicalDevice device);

	//给设备加权打分
	int rateDeviceSuitability(VkPhysicalDevice device);

	//查找需要的队列族
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

	//创建逻辑设备
	void createLogicalDevice();

	//创建窗口表面
	void createSurface();

	//检测设备扩展支持
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);

	//填写交换链信息
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

	//选择合适的表面格式
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

	//选择合适的呈现模式
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);

	//选择合适的交换范围
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	//利用以上几个辅助函数创建交换链
	void createSwapChain();

	//创建图像视图
	void createImageViews();
	//简化创建
	VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);

	//创建图形管线
	void createGraphicsPipeline();

	//载入二进制文件
	static std::vector<char> readFile(const std::string& filename);

	//创建着色器模块
	VkShaderModule createShaderModule(const std::vector<char>& code);

	//渲染配置
	void createRenderPass();

	//所有帧缓冲对象的创建
	void createFramebuffers();

	//创建指令池
	void createCommandPool();

	//记录指令
	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

	//为交换链中的每一个图像创建指令缓冲对象
	void createCommandBuffers();

	//绘制函数
	void drawFrame();

	//创建信号量对象
	void createSyncObjects();

	//重建交换链.整合一堆函数
	void recreateSwapChain();

	//清除交换链相关指令,方便重建,通常在窗口大小改变时
	void cleanupSwapChain();

	//窗口大小改变时的函数
	static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

	//创建顶点缓冲
	void createVertexBuffer();

	//创建索引缓冲
	void createIndexBuffer();

	//查询最合适的内存种类
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

	//创建缓冲的辅助函数
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties,
					  VkBuffer& buffer, VkDeviceMemory& bufferMemory);

	//在缓冲之间复制数据
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	//设计两个辅助函数,用来帮助指令记录到指令缓冲
	VkCommandBuffer beginSingleTimeCommands();
	void endSingleTimeCommands(VkCommandBuffer commandBuffer);

	//提供着色器实用的每一个描述符绑定类型
	void createDescriptorSetLayout();

	void createUniformBuffers();

	//更新uniform的数据
	void updateUniformBuffer(uint32_t currentImage);

	//创建描述符池
	void createDescriptorPool();
	//创建描述符集
	void createDescriptorSets();

	//加载纹理图像
	void createTextureImage();

	//简化图像对象的操作
	void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkFormat format, VkImageTiling tiling,
					 VkImageUsageFlagBits usage, VkMemoryPropertyFlags properties,
					 VkImage& image, VkDeviceMemory& imageMemory);

	//进行图像布局变换
	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);

	//复制缓冲到图像
	void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

	//创建图像视图对象
	void createTextureImageView();

	//使用采样器对纹理数据进行采样
	void createTextureSampler();

	//配置深度图像需要的资源
	void createDepthResources();

	//查找既符合需要,设备又支持的图像格式
	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	//查找适合作为深度附着的图像数据格式
	VkFormat findDepthFormat();

	//加载模型
	void loadModel();

	//生成原石纹理图像不同细化级别
	void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);
private:
	//窗口句柄
	GLFWwindow* window;

	//存储实例句柄
	VkInstance instance;

	//存储回调函数信息
	VkDebugUtilsMessengerEXT callback;

	//存储选择使用的显卡信息
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

	//存储逻辑设备的对象
	VkDevice device;

	//存储逻辑设备的队列句柄
	VkQueue graphicsQueue;

	//存储窗口表面
	VkSurfaceKHR surface;

	//创建呈现队列
	VkQueue presentQueue;

	//存储交换链
	VkSwapchainKHR swapChain;

	//存储图像句柄
	std::vector<VkImage> swapChainImages;

	//存储交换链图像的格式和范围
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;

	//存储图像视图
	std::vector<VkImageView> swapChainImageViews;

	//渲染设置
	VkRenderPass renderPass;

	//描述符设计布局
	VkDescriptorSetLayout descriptorSetLayout;

	//管线层级
	VkPipelineLayout pipelineLayout;

	//存储管线
	VkPipeline graphicsPipeline;

	//存储所有的帧缓冲对象
	std::vector<VkFramebuffer> swapChainFramebuffers;

	//存储指令池
	VkCommandPool commandPool;

	//命令缓冲
	std::vector<VkCommandBuffer> commandBuffers;

	////通过信号量完成指令的约束,图像已获取和渲染已完成
	//VkSemaphore imageAvilableSemaphore;
	//VkSemaphore renderFinishedSemaphore;
	//为了避免同步干扰,为每一帧创建专属信号量
	std::vector<VkSemaphore> imageAvilableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	//为每一帧创建一个栅栏对象
	std::vector<VkFence> inFlightFences;
	//追踪当前的帧
	size_t currentFrame = 0;

	//标记窗口大小是否改变
	bool framebufferResized = false;

	//顶点缓冲
	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	//索引缓冲
	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;

	//描述符数据的缓冲
	std::vector<VkBuffer> uniformBuffers;
	std::vector<VkDeviceMemory> uniformBuffersMemory;

	//保存描述符池对象
	VkDescriptorPool descriptorPool;
	std::vector<VkDescriptorSet> descriptorSets;

	//存储计算出的细化级别个数
	uint32_t mipLevels;
	//使用Vulkan的图像
	VkImage textureImage;
	VkDeviceMemory textureImageMemory;

	//存储纹理图像的图像视图对象
	VkImageView textureImageView;
	VkSampler textureSampler;

	//深度图需要的资源
	VkImage depthImage;
	VkDeviceMemory depthImageMemory;
	VkImageView depthImageView;
	
};