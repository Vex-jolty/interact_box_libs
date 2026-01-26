project(JsonHelper VERSION 1.0.0)

add_library(
	json_helper STATIC
	json_helper.cpp
)

target_include_directories(json_helper PRIVATE ${CMAKE_SOURCE_DIR}/include/errors ${CMAKE_SOURCE_DIR}/src/shared/string_helper)
	
determine_lib_extension(json_helper TRUE)

link_base_libs(json_helper ${TARGET_WINDOWS_VERSION} TRUE)

if (WIN32 AND MINGW)
	set(JSONCPP_NAME jsoncpp_static)
else()
	set(JSONCPP_NAME jsoncpp)
endif()
	
target_link_libraries(json_helper PRIVATE platform_config ${JSONCPP_NAME} string_helper errors)
