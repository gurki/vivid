cmake_minimum_required( VERSION 3.8 )
project( vivid_example VERSION 1.0.0 LANGUAGES CXX )

add_executable( vivid_example main.cpp )

target_link_libraries( vivid_example
    PRIVATE
        vivid::vivid
)
