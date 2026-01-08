project(FileHelper VERSION 1.0.0)

add_library(
  file_helper SHARED file_helper.cpp
)

set_target_properties(file_helper PROPERTIES
  PREFIX ""
  SUFFIX ".dll"
)

set_windows_version_definitions(file_helper ${TARGET_WINDOWS_VERSION} TRUE)

target_link_libraries(file_helper PRIVATE platform_config version string_helper)
