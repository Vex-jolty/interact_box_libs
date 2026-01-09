project(FileHelper VERSION 1.0.0)

add_library(
  file_helper SHARED file_helper.cpp
)

determine_lib_extension(file_helper FALSE)

link_base_libs(string_helper ${TARGET_WINDOWS_VERSION} TRUE)

target_link_libraries(file_helper PRIVATE platform_config version string_helper)
