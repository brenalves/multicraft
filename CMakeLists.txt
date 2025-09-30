cmake_minimum_required(VERSION 3.10)

project(multicraft)

add_executable(multicraft
    src/main.cpp

    src/core/app.cpp
    src/core/window.cpp
    src/core/input.cpp
    src/core/resourcemanager.cpp

    src/rendering/renderer.cpp
    src/rendering/shader.cpp
    src/rendering/buffer.cpp
    src/rendering/vertexarray.cpp
    src/rendering/texture.cpp

    src/components/mesh.cpp
    src/components/transform.cpp
    src/components/camera.cpp
    src/components/material.cpp

    src/game/player.cpp
    src/game/quad.cpp
    src/game/cube.cpp
    src/game/world.cpp
    src/game/chunk.cpp

    deps/glad/src/glad.c
    deps/stb_image/src/stb_image.cpp
)

target_include_directories(multicraft PRIVATE
    src
    deps/glad/include
    deps/stb_image/include
)

target_link_libraries(multicraft PRIVATE glfw)

if(WIN32)
    target_link_libraries(multicraft PRIVATE opengl32)
else()
    target_link_libraries(multicraft PRIVATE GL)
endif()

add_custom_command(
    TARGET multicraft
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:multicraft>/assets"
)
