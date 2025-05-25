cmake_minimum_required(VERSION 3.20)
project(akairo VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find actual OpenGL library
find_package(OpenGL REQUIRED)

# Fetch ImGui
include(FetchContent)
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.91.9b
)
FetchContent_MakeAvailable(imgui)

# Create ImGui library with required backends
set(IMGUI_SOURCES
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_win32.cpp
        # Add other backends you need
)

add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
)
target_link_libraries(imgui PUBLIC OpenGL::GL)

# Find all akairo source files
file(GLOB_RECURSE SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# Find all header files (for IDE only)
file(GLOB_RECURSE HEADERS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
)

# Create the akairo library
add_library(akairo STATIC ${SOURCES})

# Include directories
target_include_directories(akairo PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
)

# Link libraries
target_link_libraries(akairo PUBLIC
        imgui
        OpenGL::GL
        d2d1
        dwrite
        dxgi
)

# Installation rules
install(TARGETS akairo
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)
install(DIRECTORY src/
        DESTINATION include/akairo
        FILES_MATCHING PATTERN "*.hpp")

# Print info for debugging
message(STATUS "Source files: ${SOURCES}")
message(STATUS "Header files: ${HEADERS}")
message(STATUS "ImGui sources: ${IMGUI_SOURCES}")