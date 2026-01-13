project(IndexHelper VERSION 1.0.0)

add_library(
	index_helper STATIC index_helper.cpp
)

determine_lib_extension(index_helper TRUE)

link_base_libs(index_helper ${TARGET_WINDOWS_VERSION} TRUE)

target_link_libraries(index_helper PRIVATE platform_config)