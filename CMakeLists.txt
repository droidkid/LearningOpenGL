cmake_minimum_required(VERSION 3.20)
project(Learning3DRendering)

set(CMAKE_CXX_STANDARD 14)

# Lessons
add_subdirectory(HelloTriangle)
add_subdirectory(HelloRectangle)
add_subdirectory(HelloCube)

# GLAD
add_library(glad "lib/glad/src/glad.c")
target_include_directories(glad PUBLIC "lib/glad/include")

#GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("lib/glfw")


# TODO(chesetti): automate this.
target_link_libraries(HelloTriangle PUBLIC glad)
target_link_libraries(HelloTriangle PUBLIC glfw)
target_link_libraries(HelloRectangle PUBLIC glad)
target_link_libraries(HelloRectangle PUBLIC glfw)
target_link_libraries(HelloCube PUBLIC glad)
target_link_libraries(HelloCube PUBLIC glfw)
