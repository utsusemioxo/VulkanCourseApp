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

  struct mainDevice {
    VkPhysicalDevice physicalDevice;
    VkDevice logicalDevice;
  } mainDevice;
  VkQueue graphicsQueue;

  // Vulkan Functions
  // - Create Functions
  void createInstance();
  void createLogicalDevice();

  // - Get Functions
  void getPhysicalDevice();

  // - Support Functions
  // -- Checker Functions
  bool checkInstanceExtensionSupport(std::vector<const char*>* checkExtensions);
  bool checkDeviceSuitable(VkPhysicalDevice device);
  static bool checkValidationLayerSupport();

  // -- Getter Functions
  QueueFamilyIndices getQueueFamilies(VkPhysicalDevice device);
};

