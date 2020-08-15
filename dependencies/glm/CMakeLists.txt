cmake_minimum_required( VERSION 3.11 FATAL_ERROR )


include( FetchContent )

FetchContent_Declare( glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.9.8
)

FetchContent_GetProperties( glm )

if ( NOT glm_POPULATED )
    FetchContent_Populate( glm )
    add_subdirectory( 
        ${glm_SOURCE_DIR} 
        ${glm_BINARY_DIR} 
        EXCLUDE_FROM_ALL 
    )
endif()

