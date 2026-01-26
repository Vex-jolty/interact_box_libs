project(FileHelper VERSION 1.0.0)

add_library(
	file_helper STATIC file_helper.cpp
)

determine_lib_extension(file_helper TRUE)

link_base_libs(string_helper ${TARGET_WINDOWS_VERSION} TRUE)

set(LIBS_TO_LINK platform_config)
if (WIN32)
	list(APPEND LIBS_TO_LINK version)
endif()
list(APPEND LIBS_TO_LINK string_helper)
target_link_libraries(file_helper PRIVATE ${LIBS_TO_LINK})
