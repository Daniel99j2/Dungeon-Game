cmake_minimum_required(VERSION 3.31)
set(USERPROFILE_DIR $ENV{USERPROFILE})
set(CMAKE_TOOLCHAIN_FILE "${USERPROFILE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
set(VCPKG_TARGET_TRIPLET "x64-windows-static" CACHE STRING "")
set(CMAKE_CXX_FLAGS_RELEASE "/O2 /Ob2 /DNDEBUG")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CGAL_DO_NOT_WARN_ABOUT_CMAKE_BUILD_TYPE TRUE)
project(Dungeon)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(libs/packer)

find_package(OpenGL REQUIRED)
find_package(assimp REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(CGAL CONFIG REQUIRED)

add_executable(
        Dungeon
        src/c/Main.cpp
        src/c/PreImports.cpp
        src/c/PreImports.h
        src/c/util/model/RenderUtil.cpp
        src/c/util/model/RenderUtil.h
        src/c/util/GenericUtil.cpp
        src/c/util/GenericUtil.h
        libs/json.hpp
        src/c/objects/GameObject.cpp
        src/c/objects/GameObject.h
        src/c/objects/type/Player.cpp
        src/c/objects/type/Player.h
        src/c/world/World.cpp
        src/c/world/World.h
        src/c/util/GameConstants.h
        src/c/util/GameConstants.cpp
        src/c/objects/type/MapPartObject.cpp
        src/c/objects/type/MapPartObject.h
        src/c/misc/Keybind.h
        src/c/util/Keybinds.h
        src/c/misc/Keybind.cpp
        libs/imgui/backends/imgui_impl_glfw.cpp
        libs/imgui/backends/imgui_impl_opengl3.cpp
        libs/imgui/imgui.cpp
        libs/imgui/imgui_demo.cpp
        libs/imgui/imgui_draw.cpp
        libs/imgui/imgui_tables.cpp
        libs/imgui/imgui_widgets.cpp
        libs/imgui/backends/imgui_impl_glfw.cpp
        libs/imgui/backends/imgui_impl_opengl3.cpp
        src/c/util/Profiler.h
        src/c/util/Logger.h
        src/c/util/Profiler.cpp
        src/c/ui/WorldEditorGui.h
        src/c/world/CollisionUtil.h
        src/c/world/CollisionLoader.cpp
        src/c/world/CollisionLoader.h
        src/c/misc/Config.h
        src/c/misc/Config.cpp
)

include_directories(
        libs/imgui
        libs/imgui/backends
)

file(COPY src/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/src)

add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/src/resources
        ${CMAKE_CURRENT_BINARY_DIR}/src/resources
        COMMENT "Copying sources"
)

target_sources(Dungeon PRIVATE
        libs/imgui/backends/imgui_impl_glfw.cpp
        libs/imgui/backends/imgui_impl_opengl3.cpp
        libs/imgui/imgui.cpp
        libs/imgui/imgui_demo.cpp
        libs/imgui/imgui_draw.cpp
        libs/imgui/imgui_tables.cpp
        libs/imgui/imgui_widgets.cpp
        libs/imgui/backends/imgui_impl_glfw.cpp
        libs/imgui/backends/imgui_impl_opengl3.cpp
        src/resources/textures/ui/icon.rc
)

target_link_libraries(Dungeon PRIVATE
        GLEW::GLEW
        glfw
        OpenGL::GL
        assimp::assimp
        glm::glm
        rectpack2D
        CGAL::CGAL
)

target_precompile_headers(Dungeon PRIVATE src/c/PreImports.h)
