project(StringHelper VERSION 1.0.0)

add_library(
	string_helper SHARED string_helper.cpp
)
	
set_target_properties(string_helper PROPERTIES
  PREFIX ""
  SUFFIX ".dll"
)
	
set_windows_version_definitions(string_helper ${TARGET_WINDOWS_VERSION} TRUE)
