add_library(core STATIC
    src/glad.c
    src/Shader.cpp
    src/Application.cpp
)

add_library(core::core ALIAS core)

# Configure include directories
# PUBLIC ensures any target linking 'core' automatically receives these include paths
target_include_directories(core
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

# Link platform-agnostic dependencies
target_link_libraries(core
    PUBLIC
        OpenGL::GL
        glfw
)

# macOS system framework dependencies
if(APPLE)
    target_link_libraries(core
        PUBLIC
            "-framework Cocoa"
            "-framework IOKit"
            "-framework CoreVideo"
    )
endif()
