project(Errors VERSION 1.0.0)

add_library(
  errors SHARED interact_box_exceptions.cpp
)

set_target_properties(errors PROPERTIES
  PREFIX ""
  SUFFIX ".dll"
)

target_link_libraries(errors PRIVATE platform_config string_helper)