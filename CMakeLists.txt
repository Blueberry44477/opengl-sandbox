cmake_minimum_required(VERSION 3.20)

project(OpenGLSandbox
    VERSION 1.0.0
    DESCRIPTION "OpenGL (Core Profile) Learning Sandbox"
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(APPLE)
    list(PREPEND CMAKE_PREFIX_PATH "/opt/homebrew" "/usr/local")
endif()

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_subdirectory(core)
add_subdirectory(labs)
