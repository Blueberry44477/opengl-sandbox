add_executable(lab01_primitives
    main.cpp
)

add_executable(app ALIAS lab01_primitives)
add_executable(lab01 ALIAS lab01_primitives)

# Link against the shared core engine/framework
# 'core' transitively provides GLAD, GLFW, OpenGL, and their respective include paths
target_link_libraries(lab01_primitives
    PRIVATE
        core
)

# Copy shaders directory next to the built binary on post-build (if shaders exist)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/shaders")
    add_custom_command(
        TARGET lab01_primitives POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/shaders
            $<TARGET_FILE_DIR:lab01_primitives>/shaders
        COMMENT "Synchronizing shaders to build directory"
    )
endif()

# Set debugger working directory for IDEs (CLion, Visual Studio, Xcode)
set_target_properties(lab01_primitives PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    XCODE_SCHEME_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)
