cmake_minimum_required(VERSION 3.20)
project(akairo VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find all source files
file(GLOB_RECURSE SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# Find all header files
file(GLOB_RECURSE HEADERS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
)

# Create the executable target
add_library(akairo ${SOURCES} ${HEADERS})

# Include directories - the most important part
target_include_directories(akairo PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Fetch ImGui
include(FetchContent)
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.91.9b
)
FetchContent_MakeAvailable(imgui)

# ImGui integration
target_include_directories(akairo PRIVATE
        ${imgui_SOURCE_DIR}
)
target_link_libraries(akairo PRIVATE imgui)

# Direct2D integration
target_link_libraries(akairo PRIVATE
        d2d1
        dwrite
        dxgi
)

# Print info for debugging
message(STATUS "Source files: ${SOURCES}")
message(STATUS "Header files: ${HEADERS}")