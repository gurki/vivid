cmake_minimum_required( VERSION 3.14 FATAL_ERROR )

project( vivid_tests 
    VERSION 1.1.0
    LANGUAGES CXX
)

include( FetchContent )

FetchContent_Declare( Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.4.0
)

FetchContent_MakeAvailable( Catch2 )

set( SOURCES 
    # test_main.cpp
    test_conversion_manual.cpp
    test_profiles.cpp
    test_wrapping.cpp
)

set( DEPENDENCIES 
    vivid 
    Catch2::Catch2WithMain
)

find_package( Qt5 COMPONENTS Core Gui QUIET ) 

if ( Qt5_FOUND )
    
    set( SOURCES 
        ${SOURCES}
        test_conversion_fuzzy.cpp
    )

    set( DEPENDENCIES 
        ${DEPENDENCIES}
        Qt5::Core
        Qt5::Gui
    )

endif()


add_executable( ${PROJECT_NAME} ${SOURCES} )

target_include_directories( ${PROJECT_NAME} 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR} 
)

target_link_libraries( ${PROJECT_NAME} 
    PRIVATE 
        ${DEPENDENCIES}
)


include( CTest )
include( Catch )
catch_discover_tests( ${PROJECT_NAME} )