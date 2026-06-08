cmake_minimum_required( VERSION 3.14 FATAL_ERROR )

project( vivid_examples 
    VERSION 2.0.0
    LANGUAGES CXX
)

add_executable( ${PROJECT_NAME}_basics basics.cpp )
target_link_libraries( ${PROJECT_NAME}_basics PRIVATE vivid )
target_compile_definitions( ${PROJECT_NAME}_basics PRIVATE GLM_ENABLE_EXPERIMENTAL )

add_executable( ${PROJECT_NAME}_strong_types strong_types.cpp )
target_link_libraries( ${PROJECT_NAME}_strong_types PRIVATE vivid )
target_compile_definitions( ${PROJECT_NAME}_strong_types PRIVATE GLM_ENABLE_EXPERIMENTAL )


# examples with qt dependency (QImage, QColor)

add_compile_definitions(QT_DISABLE_DEPRECATED_UP_TO=0x060A00)
find_package( Qt6 COMPONENTS Core Gui QUIET ) 

if ( Qt6_FOUND )

    add_executable( ${PROJECT_NAME}_advanced advanced.cpp )
    target_link_libraries( ${PROJECT_NAME}_advanced PUBLIC Qt::Core Qt::Gui vivid )
    target_compile_definitions( ${PROJECT_NAME}_advanced PRIVATE GLM_ENABLE_EXPERIMENTAL )

    add_executable( ${PROJECT_NAME}_convert_maps convert_maps.cpp )
    target_link_libraries( ${PROJECT_NAME}_convert_maps PUBLIC Qt::Core Qt::Gui vivid )
    target_compile_definitions( ${PROJECT_NAME}_convert_maps PRIVATE GLM_ENABLE_EXPERIMENTAL )

endif()