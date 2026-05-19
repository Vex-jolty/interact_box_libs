project(file_helper VERSION 1.2.1)

add_library(
	${PROJECT_NAME} STATIC ${PROJECT_NAME}.cpp
)

determine_lib_extension(${PROJECT_NAME} TRUE)

link_base_libs(string_helper ${TARGET_WINDOWS_VERSION} TRUE)

set(LIBS_TO_LINK platform_config)
if (WIN32)
	list(APPEND LIBS_TO_LINK version)
else()
	if(POLICY CMP0167)
		cmake_policy(SET CMP0167 NEW)
		set(Boost_USE_STATIC_LIBS ON)
	endif()
	find_package(Boost REQUIRED filesystem)
	list(APPEND LIBS_TO_LINK Boost::filesystem)
endif()
list(APPEND LIBS_TO_LINK string_helper)
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS_TO_LINK})