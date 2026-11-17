add_executable(lab03_transformations
    main.cpp
)

add_executable(lab03 ALIAS lab03_transformations)

target_link_libraries(lab03_transformations
        PRIVATE
        core
)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/shaders")
    add_custom_command(
            TARGET lab03_transformations POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/shaders
            $<TARGET_FILE_DIR:lab03_transformations>/shaders
            COMMENT "Synchronizing shaders to build directory"
    )
endif()
set_target_properties(lab03_transformations PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        XCODE_SCHEME_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)