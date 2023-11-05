#pragma once

#include <iostream>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <vector>

#include "Utilities.h"

#ifndef _DEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif

const std::vector<const char*> validationLayers = {
"VK_LAYER_KHRONOS_validation"
};

class VulkanRenderer
{
public:
  VulkanRenderer();

  int init(GLFWwindow* newWindow);
  void cleanup();

  ~VulkanRenderer();

private:
  GLFWwindow* window;

  // Vulkan Components
  VkInstance instance;
  VkDebugUtilsMessengerEXT debugMessager;

  struct mainDevice {
    VkPhysicalDevice physicalDevice;
    VkDevice logicalDevice;
  } mainDevice;
  VkQueue graphicsQueue;

  // Vulkan Functions
  // - Create Functions
  void createInstance();
  void createLogicalDevice();
  VkResult CreateDebugUtilsMessengerEXT(
    VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugUtilsMessengerEXT* pDebugMessenger
  );

  static void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

  void DestroyDebugUtilsMessengerEXT(
    VkInstance instance,
    VkDebugUtilsMessengerEXT debugMessenger,
    const VkAllocationCallbacks* pAllocator
  );
  // - Setup Functions
  void setupDebugMessenger();

  // - Get Functions
  void getPhysicalDevice();
  std::vector<const char*> getRequiredExtensions();

  // - Support Functions
  // -- Checker Functions
  bool checkInstanceExtensionSupport(std::vector<const char*>* checkExtensions);
  bool checkDeviceSuitable(VkPhysicalDevice device);
  static bool checkValidationLayerSupport();
  // -- Debug callback Functions
  static VKAPI_ATTR VkBool32  VKAPI_CALL debugCallBack(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData
  );

  // -- Getter Functions
  QueueFamilyIndices getQueueFamilies(VkPhysicalDevice device);
};

