cmake_minimum_required( VERSION 3.14 FATAL_ERROR )
include( FetchContent )


FetchContent_Declare( json
    GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
    GIT_TAG v3.9.1
)

FetchContent_Declare( glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.9.8
)


FetchContent_MakeAvailable( json glm )