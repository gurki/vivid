cmake_minimum_required( VERSION 3.14 FATAL_ERROR )

project( vivid_examples 
    VERSION 2.0.0
    LANGUAGES CXX
)

add_executable( ${PROJECT_NAME}_basics basics.cpp )
target_link_libraries( ${PROJECT_NAME}_basics PRIVATE vivid )

add_executable( ${PROJECT_NAME}_strong_types strong_types.cpp )
target_link_libraries( ${PROJECT_NAME}_strong_types PRIVATE vivid )


# examples with qt dependency (QImage, QColor)

find_package( Qt5 COMPONENTS Core Gui QUIET ) 

if ( Qt5_FOUND )

    add_executable( ${PROJECT_NAME}_advanced advanced.cpp )
    target_link_libraries( ${PROJECT_NAME}_advanced PUBLIC Qt5::Core Qt5::Gui vivid )

    add_executable( ${PROJECT_NAME}_convert_maps convert_maps.cpp )
    target_link_libraries( ${PROJECT_NAME}_convert_maps PUBLIC Qt5::Core Qt5::Gui vivid )

endif()