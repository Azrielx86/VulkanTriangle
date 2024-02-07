#include <iostream>
#include "Global.h"
#include <boost/format.hpp>
#include "VulkanApplication.h"

int main()
{
    const auto app = std::make_unique<VulkanApplication>(800, 600, "Hello Vulkan!");

    try
    {
        app->run();
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
