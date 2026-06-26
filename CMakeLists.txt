cmake_minimum_required(VERSION 4.4)

project(Planetarium)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib/glfw-3.4)

include_directories(${PROJECT_NAME} lib/glad/include/ lib/glfw-3.4/include/ lib/stb_image/ lib/ src/)


file(GLOB_RECURSE MY_SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${MY_SOURCES} lib/glad/src/glad.c lib/stb_image/stb_image.cpp)

target_link_libraries(${PROJECT_NAME} glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)

get_filename_component(MINGW_BIN_DIR ${CMAKE_CXX_COMPILER} DIRECTORY)

set(MINGW_DLLS
    "${MINGW_BIN_DIR}/libgcc_s_seh-1.dll"
    "${MINGW_BIN_DIR}/libstdc++-6.dll"
    "${MINGW_BIN_DIR}/libwinpthread-1.dll"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${MINGW_DLLS}
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)