project(IndexHelper VERSION 1.0.0)

add_library(
  index_helper SHARED index_helper.cpp
)

set_target_properties(index_helper PROPERTIES
  PREFIX ""
  SUFFIX ".dll"
)

target_link_libraries(index_helper PRIVATE platform_config)