project(json_helper VERSION 1.2.1)

add_library(
	${PROJECT_NAME} STATIC
	${PROJECT_NAME}.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include/errors ${CMAKE_SOURCE_DIR}/src/shared/string_helper)
	
determine_lib_extension(${PROJECT_NAME} TRUE)

link_base_libs(${PROJECT_NAME} ${TARGET_WINDOWS_VERSION} TRUE)

if (WIN32 AND MINGW)
	set(JSONCPP_NAME jsoncpp_static)
else()
	set(JSONCPP_NAME jsoncpp)
endif()
	
target_link_libraries(${PROJECT_NAME} PRIVATE platform_config ${JSONCPP_NAME} string_helper errors)