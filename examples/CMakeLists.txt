cmake_minimum_required( VERSION 3.14 FATAL_ERROR )


add_executable( vivid_basics basics.cpp )
target_link_libraries( vivid_basics PRIVATE vivid )

add_executable( vivid_strong_types strong_types.cpp )
target_link_libraries( vivid_strong_types PRIVATE vivid )


find_package( Qt5 COMPONENTS Core Gui REQUIRED ) 

add_executable( vivid_advanced advanced.cpp )
target_link_libraries( vivid_advanced PUBLIC Qt5::Core Qt5::Gui vivid )

add_executable( vivid_convert_maps convert_maps.cpp )
target_link_libraries( vivid_convert_maps PUBLIC Qt5::Core Qt5::Gui vivid )