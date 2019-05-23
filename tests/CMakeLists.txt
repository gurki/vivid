cmake_minimum_required( VERSION 3.8 )
project( vivid_tests VERSION 1.0.0 LANGUAGES CXX )

add_executable( vivid_tests
    main.cpp
    test_conversion_manual.cpp
    test_profiles.cpp
	# test_conversion_fuzzy.cpp	# requires Qt
)

target_include_directories( vivid_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries( vivid_tests
    PRIVATE
        vivid::vivid
)
