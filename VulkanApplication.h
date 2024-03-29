#ifndef VULKANAPPLICATION_H
#define VULKANAPPLICATION_H

#include "Global.h"

#include <boost/format.hpp>
#include <optional>
#include <string>
#include <glm/glm.hpp>
#include <array>

struct Vertex
{
	glm::vec2 pos;
	glm::vec3 color;

	static VkVertexInputBindingDescription getBindingDescription()
	{
		VkVertexInputBindingDescription bindingDescription{};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		return bindingDescription;
	}

	static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions()
	{
		std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);
		return attributeDescriptions;
	}
};

const std::vector<Vertex> vertices = {
	{{0.0F, -0.5F}, {1.0F, 0.0F, 0.0F}},
	{{0.5F, 0.5F}, {0.0F, 1.0F, 0.0F}},
	{{-0.5F, 0.5F}, {0.0F, 0.0F, 1.0F}}
};

struct QueueFamilyIndices
{
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	[[nodiscard]] bool isComplete() const
	{
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

class VulkanApplication
{
  public:
	VulkanApplication(int width, int height, std::string title);
	void run();

  private:
	void initWindow();
	static void frameBufferResizeCallback(GLFWwindow* window, [[maybe_unused]] int width, [[maybe_unused]] int height);
	void initVulkan();
	void pickPhysisicalDevice();
	void createInstance();
	void createLogicalDevice();
	void createSurface();
	void mainLoop();
	void cleanup() const;
	void cleanupSwapChain() const;
	static std::vector<const char *> getRequiredExtensions();
	bool isDeviceSuitable(const VkPhysicalDevice &device) const;
	[[nodiscard]] QueueFamilyIndices findQueueFamilies(const VkPhysicalDevice &device) const;
	static bool checkValidationLayerSupport();
	static bool checkDeviceExtensionSupport(const VkPhysicalDevice &device);
	SwapChainSupportDetails querySwapChainSupport(const VkPhysicalDevice &device) const;
	static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& avaiableFormats);
	static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& avaiablePresentModes);
	[[nodiscard]] VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) const;
	void createSwapChain();
	void createImageViews();
	void createGraphicsPipeline();
	[[nodiscard]] VkShaderModule createShaderModule(const std::vector<char>& code) const;
	void createRenderPass();
	void createFramebuffers();
	void createCommandPool();
	void createCommandBuffers();
	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex) const;
	void createSyncObjects();
	void drawFrame();
	void recreateSwapChain();
	void createVertexBuffer();
	[[nodiscard]] uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) const;
	
	int width;
	int height;
	std::string title;
	GLFWwindow *window = nullptr;
	VkInstance instance;
	VkPhysicalDevice physicalDevice;
	VkDevice device{};
	VkQueue graphicsQueue;
	QueueFamilyIndices indices;
	VkSurfaceKHR surface{};
	VkQueue presentQueue{};
	VkSwapchainKHR swapChain{};
	std::vector<VkImage> swapChainImages;
	std::vector<VkImageView> swapChainImageViews;
	VkFormat swapChainImageFormat{};
	VkExtent2D swapChainExtent{};
	VkRenderPass renderPass{};
	VkPipelineLayout pipelineLayout{};
	VkPipeline graphicsPipeline{};
	std::vector<VkFramebuffer> swapChainFramebuffers;
	VkCommandPool commandPool{};

	std::vector<VkCommandBuffer> commandBuffers;
	std::vector<VkSemaphore> imageAvaiableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;
	uint32_t currentFrame = 0;

	bool framebufferResized = false;

	VkBuffer vertexBuffer{};
	VkDeviceMemory vertexBufferMemory{};
};

#endif // VULKANAPPLICATION_H
