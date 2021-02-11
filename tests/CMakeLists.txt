cmake_minimum_required( VERSION 3.14 FATAL_ERROR )

project( vivid_tests 
    VERSION 1.1.0
    LANGUAGES CXX
)

find_package( Qt5 COMPONENTS Core Gui QUIET ) 

set( SOURCES 
    test_main.cpp
    test_conversion_manual.cpp
    test_profiles.cpp
)

set( DEPENDENCIES vivid )

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