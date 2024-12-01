cmake_minimum_required(VERSION 3.10)
project(StenenkoPrizm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

# Adding GLFW
add_subdirectory(libs/glfw-3.4)
include_directories(libs/glfw-3.4/include)

# Adding GLAD
add_library(glad STATIC libs/glad/src/glad.c)
target_include_directories(glad PUBLIC libs/glad/include)

add_executable(StenenkoPrizm src/main.cpp)

# Linking GLFW and GLAD
target_link_libraries(StenenkoPrizm glfw glad)

# On Windows adding libraries of OpenGL
if (WIN32)
    target_link_libraries(StenenkoPrizm opengl32)
endif()
