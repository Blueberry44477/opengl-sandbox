add_executable(lab02_textures
    main.cpp
)

add_executable(lab02 ALIAS lab02_textures)

target_link_libraries(lab02_textures
        PRIVATE
        core
)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/shaders")
    add_custom_command(
            TARGET lab02_textures POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/shaders
            $<TARGET_FILE_DIR:lab02_textures>/shaders
            COMMENT "Synchronizing shaders to build directory"
    )
endif()
set_target_properties(lab02_textures PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        XCODE_SCHEME_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)