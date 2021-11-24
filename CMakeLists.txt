cmake_minimum_required(VERSION 3.20)
project(Learning3DRendering)

set(CMAKE_CXX_STANDARD 14)

# Lessons
add_subdirectory(HelloTriangle)
add_subdirectory(HelloRectangle)

# GLAD
add_library(glad "deps/glad/src/glad.c")
target_include_directories(glad PUBLIC "deps/glad/include")

#GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("./deps/glfw")


target_link_libraries(HelloTriangle PUBLIC glad)
target_link_libraries(HelloTriangle PUBLIC glfw)
target_link_libraries(HelloRectangle PUBLIC glad)
target_link_libraries(HelloRectangle PUBLIC glfw)
