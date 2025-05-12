cmake_minimum_required(VERSION 3.20)
project(akairo VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Include directories
include_directories(${PROJECT_SOURCE_DIR}/src)

file(GLOB_RECURSE AKAIRO_SOURCES
        "src/**/*.cpp"
)

file(GLOB_RECURSE AKAIRO_HEADERS
        "src/**/*.hpp"
)

message(STATUS "Collected source files: ${AKAIRO_HEADERS}")

add_library(akairo STATIC ${AKAIRO_SOURCES}
        src/akairo.hpp)
target_include_directories(akairo PRIVATE "src")


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