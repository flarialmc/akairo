cmake_minimum_required(VERSION 3.20)
project(akairo VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Include directories
include_directories(${PROJECT_SOURCE_DIR}/src)

file(GLOB_RECURSE AKAIRO_SOURCES
        "src/**/*.cpp"
        "src/*.cpp"
        "src/**/*.hpp"
        "src/*.hpp"
)

add_library(akairo STATIC ${AKAIRO_SOURCES})

# a function to get all header files recursively
function(get_all_subdirs base_dir result)
    file(GLOB_RECURSE subdirs LIST_DIRECTORIES true "${base_dir}/*")
    set(dir_list "")
    foreach(subdir ${subdirs})
        if(IS_DIRECTORY ${subdir})
            list(APPEND dir_list ${subdir})
        endif()
    endforeach()
    set(${result} "${dir_list}" PARENT_SCOPE)
endfunction()

get_all_subdirs("${CMAKE_CURRENT_SOURCE_DIR}/src" ALL_SRC_DIRS)

target_include_directories(akairo PRIVATE ${ALL_SRC_DIRS})
# end


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