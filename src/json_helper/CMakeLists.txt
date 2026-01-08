project(JsonHelper VERSION 1.0.0)

add_library(
  json_helper SHARED
  json_helper.cpp
)

target_include_directories(json_helper PRIVATE ${CMAKE_SOURCE_DIR}/include/errors ${CMAKE_SOURCE_DIR}/src/shared/string_helper)
  
set_target_properties(json_helper PROPERTIES
  PREFIX ""
  SUFFIX ".dll"
)
set_windows_version_definitions(json_helper ${TARGET_WINDOWS_VERSION} TRUE)
  
target_link_libraries(json_helper PRIVATE jsoncpp_static string_helper errors -static)
