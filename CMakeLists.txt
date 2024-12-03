cmake_minimum_required(VERSION 3.10)
project(StenenkoPrizm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(libs/glfw-3.4)

add_library(glad STATIC libs/glad/src/glad.c)
target_include_directories(glad PUBLIC libs/glad/include)

add_executable(StenenkoPrizm 
    src/main.cpp 
    src/shaderClass.cpp 
    src/VBO.cpp
    src/EBO.cpp
    src/VAO.cpp
)

target_include_directories(StenenkoPrizm PUBLIC 
    ${PROJECT_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/libs/glad/include
    ${CMAKE_SOURCE_DIR}/libs/glfw-3.4/include
)

target_link_libraries(StenenkoPrizm glfw glad)

if (WIN32)
    target_link_libraries(StenenkoPrizm opengl32)
endif()
