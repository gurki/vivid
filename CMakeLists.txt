cmake_minimum_required( VERSION 3.14 FATAL_ERROR )

project( vivid
    VERSION 3.1.0
    DESCRIPTION "A simple-to-use cpp color library"
    HOMEPAGE_URL "https://github.com/gurki/vivid"
    LANGUAGES CXX
)

add_compile_definitions( VIVID_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}/" )
add_compile_definitions( GLM_ENABLE_EXPERIMENTAL )

add_subdirectory( dependencies )

add_library( ${PROJECT_NAME} STATIC
    src/adobe.cpp
    src/color.cpp
    src/colormap.cpp
    src/hex.cpp
    src/hsl.cpp
    src/hsv.cpp
    src/index.cpp
    src/interpolation.cpp
    src/lab.cpp
    src/lch.cpp
    src/lrgb.cpp
    src/name.cpp
    src/oklab.cpp
    src/rgb.cpp
    src/rgb32.cpp
    src/rgb8.cpp
    src/srgb.cpp
    src/types.cpp
    src/utility.cpp
    src/xyz.cpp
)

add_library( ${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME} )

target_compile_features( ${PROJECT_NAME} PUBLIC 
    cxx_std_17
)

target_include_directories( ${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries( ${PROJECT_NAME} PUBLIC
    nlohmann_json::nlohmann_json
    glm::glm
)


################################################################################
#  install
################################################################################

install(
    TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)

install( 
    DIRECTORY include
    DESTINATION ${CMAKE_INSTALL_PREFIX}
)


################################################################################
#  examples and tests
################################################################################

add_subdirectory( examples )
add_subdirectory( tests )