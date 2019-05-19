cmake_minimum_required( VERSION 3.8 )
project( vivid-example VERSION 1.0.0 LANGUAGES CXX )

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
find_package( vivid REQUIRED )

add_executable ( vivid-example main.cpp )

target_link_library( vivid-example-binary
    PRIVATE
        vivid::library
)
