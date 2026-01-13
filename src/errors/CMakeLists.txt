project(Errors VERSION 1.0.0)

add_library(
	errors STATIC interact_box_exceptions.cpp
)

determine_lib_extension(errors TRUE)

target_link_libraries(errors PRIVATE platform_config string_helper)