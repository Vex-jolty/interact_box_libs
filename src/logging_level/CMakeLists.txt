project(logging_level VERSION 1.0.0)

# Logging is a static library to avoid conflicts during linking
add_library(
	${PROJECT_NAME} STATIC ${PROJECT_NAME}.cpp
)

determine_lib_extension(${PROJECT_NAME} TRUE)

link_base_libs(index_helper ${TARGET_WINDOWS_VERSION} TRUE)

target_link_libraries(${PROJECT_NAME} PRIVATE platform_config)