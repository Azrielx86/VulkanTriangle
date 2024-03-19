cmake_minimum_required(VERSION 3.27)
project(VulkanTriangle)

set(CMAKE_CXX_STANDARD 17)
set(GLSL_COMPILER "glslc")

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Boost REQUIRED)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(__DEBUG__)
endif ()

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/shaders")
message(STATUS "Compiling vertex shader")
execute_process(COMMAND bash -c "${GLSL_COMPILER} ${CMAKE_CURRENT_SOURCE_DIR}/shaders/shader.vert -o ${CMAKE_CURRENT_BINARY_DIR}/shaders/vert.spv"
                WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
                RESULT_VARIABLE GLSL_COMPILE)
if (NOT ${GLSL_COMPILE} MATCHES 0)
    message(FATAL_ERROR "Error compiling vertex shader")
endif ()

execute_process(COMMAND bash -c "${GLSL_COMPILER} ${CMAKE_CURRENT_SOURCE_DIR}/shaders/shader.frag -o ${CMAKE_CURRENT_BINARY_DIR}/shaders/frag.spv"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        RESULT_VARIABLE GLSL_COMPILE)
if (NOT ${GLSL_COMPILE} MATCHES 0)
    message(FATAL_ERROR "Error compiling fragment shader")
endif ()

add_executable(VulkanTriangle main.cpp
        VulkanApplication.cpp
        VulkanApplication.h
        Global.h
        Shader.cpp
        Shader.h)
target_link_libraries(VulkanTriangle Vulkan::Vulkan)
target_link_libraries(VulkanTriangle glfw)
target_link_libraries(VulkanTriangle Boost::boost)
