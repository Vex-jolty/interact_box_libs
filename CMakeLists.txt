cmake_minimum_required(VERSION 3.13)

project(InteractBoxLibs VERSION 1.1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_SYSTEM_NAME Windows)

if (NOT MINGW)
	message(FATAL_ERROR "${CMAKE_CXX_COMPILER_ID} is not a currently supported compiler")
endif()

set(TARGET_WINDOWS_VERSION "win98" CACHE STRING "The version of Windows to target (win98, winme, win2k, winxp, vista, win7, win8, win10, win11)")

set_property(CACHE TARGET_WINDOWS_VERSION PROPERTY STRINGS
	win98 winme win2k winxp vista win7 win8 win10 win11
)

set(VERSIONS_THAT_REQUIRE_PTHREAD9X win98 winme win2k winxp)
set(VERSIONS_THAT_REQUIRE_MSVCRT40 win98 winme win2k)
set(VERSIONS_THAT_REQUIRE_WRAPPERS win98 winme)

if(NOT DEFINED TARGET_WINDOWS_VERSION)
	set(TARGET_WINDOWS_VERSION "win98"
		CACHE STRING "Target Windows version"
	)
endif()

function(set_windows_version_definitions target version)
	string(TOLOWER "${version}" version)

	if(version STREQUAL "win98")
		set(WINVER_VAL			0x0400)
		set(_WIN32_WINDOWS_VAL   0x0410)
		set(_WIN32_WINNT_VAL	 0x0400)

	elseif(version STREQUAL "winme")
		set(WINVER_VAL			0x0400)
		set(_WIN32_WINDOWS_VAL   0x0490)
		set(_WIN32_WINNT_VAL	 0x0400)

	elseif(version STREQUAL "win2k")
		set(WINVER_VAL			0x0500)
		set(_WIN32_WINDOWS_VAL   0x0500)
		set(_WIN32_WINNT_VAL	 0x0500)

	elseif(version STREQUAL "winxp")
		set(WINVER_VAL			0x0501)
		set(_WIN32_WINDOWS_VAL   0x0501)
		set(_WIN32_WINNT_VAL	 0x0501)

	elseif(version STREQUAL "vista")
		set(WINVER_VAL			0x0600)
		set(_WIN32_WINNT_VAL	 0x0600)

	elseif(version STREQUAL "win7")
		set(WINVER_VAL			0x0601)
		set(_WIN32_WINNT_VAL	 0x0601)

	elseif(version STREQUAL "win8")
		set(WINVER_VAL			0x0602)
		set(_WIN32_WINNT_VAL	 0x0602)

	elseif(version STREQUAL "win10")
		set(WINVER_VAL			0x0A00)
		set(_WIN32_WINNT_VAL	 0x0A00)

	elseif(version STREQUAL "win11")
		set(WINVER_VAL			0x0A00)
		set(_WIN32_WINNT_VAL	 0x0A00)

	else()
		message(FATAL_ERROR "Unknown TARGET_WINDOWS_VERSION: ${version}")
	endif()

	target_compile_definitions(${target} INTERFACE
		WINVER=${WINVER_VAL}
		_WIN32_WINNT=${_WIN32_WINNT_VAL}
		_WIN32_WINDOWS=${_WIN32_WINDOWS_VAL}
	)
endfunction(set_windows_version_definitions)


function(link_base_libs target version requires_additional_libs)
	string(TOLOWER "${version}" version)

	if (version IN_LIST VERSIONS_THAT_REQUIRE_PTHREAD9X)
		target_link_libraries(${target} INTERFACE pthread-9x)
		target_compile_options(${target} INTERFACE -m32 -march=i486)
	else()
		target_link_libraries(${target} INTERFACE winpthread)
	endif()

	if (version IN_LIST VERSIONS_THAT_REQUIRE_WRAPPERS)
		target_link_libraries(${target} INTERFACE corkel32 corusr cornt)
	endif()

	if(requires_additional_libs)
		set(ADDITIONAL_LIBS atomic kernel32 mingw32 gcc gcc_eh stdc++ shell32 advapi32 mingwex)
		if (NOT version IN_LIST VERSIONS_THAT_REQUIRE_MSVCRT40)
			list(APPEND ADDITIONAL_LIBS uuid)
		endif()
		target_link_libraries(${target} INTERFACE ${ADDITIONAL_LIBS})
	endif()

	if (version IN_LIST VERSIONS_THAT_REQUIRE_MSVCRT40)
		target_link_libraries(${target} INTERFACE msvcrt40)
	endif()
endfunction()

# This function is for ensuring a cross-compiled library has a proper .dll or .lib extension, and no prefix
# This is not meant to be used on native builds, and thus checks if the compiler is MinGW
function(determine_lib_extension target make_static)
	if(MINGW)
		if(make_static)
			set(LIB_SUFFIX ".lib")
		else()
			set(LIB_SUFFIX ".dll")
		endif()

		set_target_properties(${target} PROPERTIES
			PREFIX ""
			SUFFIX ${LIB_SUFFIX}
		)
	endif()
endfunction()

add_library(platform_config INTERFACE)

target_include_directories(platform_config INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

set_windows_version_definitions(platform_config ${TARGET_WINDOWS_VERSION})

target_compile_options(platform_config INTERFACE
	-fcf-protection=none
)

target_compile_options(platform_config INTERFACE
	$<$<CONFIG:Release>:-ffunction-sections -fdata-sections -s>
)

target_link_options(platform_config INTERFACE
	$<$<CONFIG:Release>:-Wl,--gc-sections>
)

target_link_options(platform_config INTERFACE
	-Wl,--subsystem,windows
	-static
)

add_subdirectory(src/errors)
add_subdirectory(src/index_helper)
add_subdirectory(src/string_helper)
add_subdirectory(src/json_helper)
add_subdirectory(src/process_helper)
add_subdirectory(src/file_helper)
add_subdirectory(src/logging_level)

install(
	TARGETS
		platform_config
		errors
		index_helper
		string_helper
		json_helper
		process_helper
		file_helper
		logging_level
	EXPORT InteractBoxLibsTargets
)

install(
	EXPORT InteractBoxLibsTargets
	NAMESPACE InteractBoxLibs::
	DESTINATION lib/cmake/InteractBoxLibs
)

install(
	DIRECTORY include/
	DESTINATION include
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
	cmake/InteractBoxLibsConfig.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/InteractBoxLibsConfig.cmake
	INSTALL_DESTINATION lib/cmake/InteractBoxLibs
)

install(
	FILES ${CMAKE_CURRENT_BINARY_DIR}/InteractBoxLibsConfig.cmake
	DESTINATION lib/cmake/InteractBoxLibs
)
