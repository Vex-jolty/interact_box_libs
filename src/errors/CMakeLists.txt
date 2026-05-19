project(errors VERSION 1.2.1)

add_library(
	${PROJECT_NAME} STATIC interact_box_exceptions.cpp
)

determine_lib_extension(${PROJECT_NAME} TRUE)

target_link_libraries(${PROJECT_NAME} PRIVATE platform_config string_helper)