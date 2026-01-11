project(ProcessHelper VERSION 1.0.0)

add_library(
  process_helper STATIC process_helper.cpp
)

determine_lib_extension(process_helper TRUE)

link_base_libs(process_helper ${TARGET_WINDOWS_VERSION} TRUE)

target_link_libraries(process_helper PRIVATE platform_config string_helper)