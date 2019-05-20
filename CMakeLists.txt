cmake_minimum_required( VERSION 3.8 )
project( vivid VERSION 1.0.0 LANGUAGES CXX )

set( VIVID_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
add_compile_definitions( VIVID_ROOT_PATH="${VIVID_DIR}/")

# make sure that custom modules are found
list( INSERT CMAKE_MODULE_PATH 0 ${VIVID_DIR}/cmake )

find_package( nlohmann_json REQUIRED )
find_package( glm REQUIRED )

message( STATUS "nlohmann-json included" )
message( STATUS "glm included" )

add_library( vivid SHARED
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

add_library( vivid::vivid ALIAS vivid )

target_compile_features( vivid
    PUBLIC
        cxx_std_17  #  std::optional, nested namespaces
    PRIVATE
        cxx_auto_type
        cxx_defaulted_functions
        cxx_lambdas
        cxx_range_for
        cxx_trailing_return_types
        cxx_unicode_literals
        cxx_inline_namespaces
)

target_include_directories( vivid
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries( vivid
    PUBLIC
        nlohmann_json::nlohmann_json
        glm
)

install(
    DIRECTORY ${VIVID_DIR}/res/
    DESTINATION res
)

export( TARGETS vivid FILE vividConfig.cmake)


################################################################################
#  examples and tests
################################################################################

add_subdirectory( examples/cmake )
add_subdirectory( tests )