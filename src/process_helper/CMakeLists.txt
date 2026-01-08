project(ProcessHelper VERSION 1.0.0)

add_library(
  process_helper SHARED process_helper.cpp
)

set_target_properties(process_helper PROPERTIES
  PREFIX ""
  SUFFIX ".dll"
)

set_windows_version_definitions(process_helper ${TARGET_WINDOWS_VERSION} TRUE)

target_link_libraries(process_helper PRIVATE platform_config string_helper)