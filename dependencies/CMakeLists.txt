cmake_minimum_required( VERSION 3.11 FATAL_ERROR )

#-------------------------------------------------------------------------------

set( MODULE_NAME json )
set( MODULE_URL https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent )
set( MODULE_VERSION v3.9.1 )

include ( FetchModule.cmake )

#-------------------------------------------------------------------------------

set( MODULE_NAME glm )
set( MODULE_URL https://github.com/g-truc/glm.git )
set( MODULE_VERSION 0.9.9.8 )

include ( FetchModule.cmake )