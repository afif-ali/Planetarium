cmake_minimum_required(VERSION 4.4)

project(Planetarium)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib/glfw-3.4)

include_directories(${PROJECT_NAME} lib/glad/include/ lib/glfw-3.4/include/)

add_executable(${PROJECT_NAME} src/main.cpp lib/glad/src/glad.c)

target_link_libraries(${PROJECT_NAME} glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)