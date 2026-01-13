project(LoggingLevel VERSION 1.0.0)

# Logging is a static library to avoid conflicts during linking
add_library(
	logging_level STATIC logging_level.cpp
)

determine_lib_extension(logging_level TRUE)

link_base_libs(index_helper ${TARGET_WINDOWS_VERSION} TRUE)

target_link_libraries(logging_level PRIVATE platform_config)