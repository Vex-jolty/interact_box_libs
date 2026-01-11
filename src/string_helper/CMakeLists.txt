project(StringHelper VERSION 1.0.0)

add_library(
	string_helper STATIC string_helper.cpp
)
	
determine_lib_extension(string_helper TRUE)

link_base_libs(string_helper ${TARGET_WINDOWS_VERSION} TRUE)

target_link_libraries(string_helper PRIVATE platform_config)