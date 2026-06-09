cmake_minimum_required(VERSION 3.13)

project(interact_box_libs VERSION 1.1.0)

if(NOT DEFINED OS_FLAVOR)
  message(FATAL_ERROR 
    "This submodule cannot be built standalone. "
    "Please configure from the root project directory."
  )
endif()

function(set_windows_version_definitions target version)
	string(TOLOWER "${version}" version)
	# Format: "WINVER;_WIN32_WINNT;_WIN32_WINDOWS"
	set(winver_prop_win98   "0x0400;0x0410;0x0410")
	set(winver_prop_winme   "0x0400;0x0490;0x0490")
	set(winver_prop_win2k   "0x0500;0x0500;0x0500")
	set(winver_prop_winxp   "0x0501;0x0501;")
	set(winver_prop_vista   "0x0600;0x0600;")
	set(winver_prop_win7    "0x0601;0x0601;")
	set(winver_prop_win8    "0x0602;0x0602;")
	set(winver_prop_win10   "0x0A00;0x0A00;")
	set(winver_prop_win11   "0x0A00;0x0A00;")

	if(NOT DEFINED winver_prop_${version})
		message(FATAL_ERROR "Unknown TARGET_WINDOWS_VERSION: ${version}")
	endif()
	
	list(GET winver_prop_${version} 0 WINVER_VAL)
  list(GET winver_prop_${version} 1 _WIN32_WINNT_VAL)
  list(GET winver_prop_${version} 2 _WIN32_WINDOWS_VAL)

	get_target_property(TARGET_TYPE ${target} TYPE)
	set(SCOPE "PRIVATE")
	if(TARGET_TYPE STREQUAL "INTERFACE_LIBRARY")
		set(SCOPE "INTERFACE")
	endif()

	target_compile_definitions(${target} ${SCOPE}
		WINVER=${WINVER_VAL}
		_WIN32_WINNT=${_WIN32_WINNT_VAL}
	)

	if(_WIN32_WINDOWS_VAL)
		target_compile_definitions(${target} ${SCOPE} _WIN32_WINDOWS=${_WIN32_WINDOWS_VAL})
	endif()

	# Add unicode support to Windows 2000 and newer
	if(WINVER_VAL STRGREATER "0x0400")
		target_compile_definitions(${target} ${SCOPE} UNICODE _UNICODE)
	
	endif()
endfunction(set_windows_version_definitions)


function(link_base_libs target version requires_additional_libs)
	if (WIN32)
		set(SCOPE "PRIVATE")
		if(TARGET_TYPE STREQUAL "INTERFACE_LIBRARY")
			set(SCOPE "INTERFACE")
		endif()
		string(TOLOWER "${version}" version)

		if (REQ_PTHREAD9X)
			target_link_libraries(${target} ${SCOPE} pthread-9x)
			target_compile_options(${target} ${SCOPE} -m32 -march=i486)
		else()
			target_link_libraries(${target} ${SCOPE} winpthread)
		endif()

		if (REQ_WRAPPERS)
			target_link_libraries(${target} ${SCOPE} corkel32 corusr cornt)
		endif()

		if(requires_additional_libs)
			set(ADDITIONAL_LIBS atomic kernel32 mingw32 shell32 advapi32 mingwex)
			if (REQ_PTHREAD9X)
				list(APPEND ADDITIONAL_LIBS uuid)
			endif()
			target_link_libraries(${target} ${SCOPE} ${ADDITIONAL_LIBS})
		endif()

		if (REQ_MSVCRT40)
			target_link_libraries(${target} ${SCOPE} msvcrt40)
		endif()
	endif()
endfunction()

# This function is for ensuring a cross-compiled library has a proper .dll or .lib extension, and no prefix
# This is not meant to be used on native builds, and thus checks if the compiler is MinGW
function(determine_lib_extension target make_static)
	if(WIN32 AND MINGW)
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
	$<$<CONFIG:Release>:-ffunction-sections -fdata-sections -s>
	$<$<CONFIG:Debug>:-g -gdwarf-4 -O0 -fno-omit-frame-pointer>
)

target_link_options(platform_config INTERFACE
	$<$<CONFIG:Release>:-Wl,--gc-sections>
	$<$<CONFIG:Debug>:-g>
	$<$<PLATFORM_ID:Windows>:-Wl,--subsystem,windows>
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
	NAMESPACE ${PROJECT_NAME}::
	DESTINATION lib/cmake/${PROJECT_NAME}
)

install(
	DIRECTORY include/
	DESTINATION include
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
	cmake/InteractBoxLibsConfig.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/InteractBoxLibsConfig.cmake
	INSTALL_DESTINATION lib/cmake/${PROJECT_NAME}
)

install(
	FILES ${CMAKE_CURRENT_BINARY_DIR}/InteractBoxLibsConfig.cmake
	DESTINATION lib/cmake/${PROJECT_NAME}
)