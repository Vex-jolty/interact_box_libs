project(LoggingLevel VERSION 1.0.0)

add_library(
  logging_level SHARED logging_level.cpp
)

set_target_properties(logging_level PROPERTIES
  PREFIX ""
  SUFFIX ".dll"
)

target_link_libraries(logging_level PRIVATE platform_config)