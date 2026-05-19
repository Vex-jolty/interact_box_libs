project(index_helper VERSION 1.2.1)

add_library(
	${PROJECT_NAME} STATIC ${PROJECT_NAME}.cpp
)

determine_lib_extension(${PROJECT_NAME} TRUE)

link_base_libs(${PROJECT_NAME} ${TARGET_WINDOWS_VERSION} TRUE)

target_link_libraries(${PROJECT_NAME} PRIVATE platform_config)