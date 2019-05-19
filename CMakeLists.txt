cmake_minimum_required( VERSION 3.8 )
project( libvivid VERSION 1.0.0 LANGUAGES CXX )

# make sure that custom modules are found
list( INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)

find_package( nlohmann_json REQUIRED )
find_package( glm REQUIRED )

add_library( libvivid SHARED
    src/adobe.cpp
    src/color.cpp
    src/colormap.cpp
    src/colortable.cpp
    src/functions.cpp
    src/hex.cpp
    src/hsl.cpp
    src/hsv.cpp
    src/index.cpp
    src/lab.cpp
    src/lch.cpp
    src/name.cpp
    src/rgb.cpp
    src/rgb32.cpp
    src/rgb8.cpp
    src/xyz.cpp
)

add_library( vivid::library ALIAS libvivid )

target_include_directories( libvivid
    PUBLIC
        $<INSTALL_INTERFACE>:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries( libvivid
    PRIVATE
        nlohmann_json
        glm
)

install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/res/
    DESTINATION res
)
