cmake_minimum_required(VERSION 3.16)
project(OpenGLProject CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "/opt/homebrew")

find_package(glfw3 REQUIRED)

find_library(OPENGL_LIB OpenGL REQUIRED)
find_library(COCOA_LIB Cocoa REQUIRED)
find_library(IOKIT_LIB IOKit REQUIRED)
find_library(COREVIDEO_LIB CoreVideo REQUIRED)

add_executable(app 
    main.cpp 
    src/glad.c
)

target_include_directories(app PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(app PRIVATE
    glfw
    ${OPENGL_LIB}
    ${COCOA_LIB}
    ${IOKIT_LIB}
    ${COREVIDEO_LIB}
)
