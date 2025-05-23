cmake_minimum_required( VERSION 3.14 FATAL_ERROR )
include( FetchContent )


FetchContent_Declare( json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0
)

FetchContent_Declare( glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
)


FetchContent_MakeAvailable( json glm )