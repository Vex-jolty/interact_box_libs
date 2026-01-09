project(IndexHelper VERSION 1.0.0)

add_library(
  index_helper SHARED index_helper.cpp
)

determine_lib_extension(index_helper FALSE)

target_link_libraries(index_helper PRIVATE platform_config)