cmake_minimum_required(VERSION 3.2)
project(AwesomeEngine)
set(ENGINE_PROJECT_NAME AwesomeEngine PARENT_SCOPE)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

if(ASAN_ENABLED)
	string(REGEX REPLACE "/RTC(su|[1su])" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}\n")
	add_compile_options(-fsanitize=address -fsanitize=fuzzer)
endif()

# set the default path for built libraries to the "lib" directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib/)

# specify my include directory 
include_directories( 
    src/
	generated/
    vendor/glad/include/
	vendor/glfw/include/
	vendor/IconFontCppHeaders/
	vendor/imgui/
	vendor/imgui/misc/cpp/
	vendor/miniaudio/
)

# GLFW options
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)

# include vendors files
file(GLOB VENDORS_SOURCES 
	vendor/glad/src/glad.c
	vendor/imgui/imgui.cpp
	vendor/imgui/imgui_draw.cpp
	vendor/imgui/imgui_tables.cpp
	vendor/imgui/imgui_widgets.cpp
	vendor/imgui/misc/cpp/imgui_stdlib.cpp
	vendor/imgui/backends/imgui_impl_glfw.cpp
	vendor/imgui/backends/imgui_impl_opengl3.cpp
) 	
source_group("Vendors" FILES ${VENDORS_SOURCES})

function(generate_reflection EXECUTABLE SRC_DIR)
message(STATUS "Running reflection compiler: \n${EXECUTABLE}")
	execute_process(
		COMMAND ${EXECUTABLE} ${SRC_DIR} ${ARGV}
		RESULT_VARIABLE CMD_ERROR
		OUTPUT_VARIABLE CMD_OUTPUT
	)
	if(${CMD_ERROR} EQUAL 0)
		message(STATUS "Generated C++ code for ${SRC_DIR}\n${CMD_OUTPUT}")
	else()
		message(STATUS "`${SRC_DIR}` failed to generate C++ code with error: ${CMD_ERROR}\n${CMD_OUTPUT}")
	endif()
endfunction()

function(build_reflection_compiler COMPILER_PROJECT_PATH)
	execute_process(COMMAND ${CMAKE_COMMAND}
		-S ${CMAKE_CURRENT_SOURCE_DIR}${COMPILER_PROJECT_PATH}
		-B ${CMAKE_CURRENT_BINARY_DIR}${COMPILER_PROJECT_PATH}
		-G ${CMAKE_GENERATOR}
		RESULT_VARIABLE CMD_ERROR
		OUTPUT_VARIABLE CMD_OUTPUT
	)
	if(${CMD_ERROR} EQUAL 0)
		message(STATUS "Generated build files for reflection compiler: \n${CMD_OUTPUT}")
	else()
		message(STATUS "Failed to generate build files for reflection compiler: ${CMD_ERROR}\n${CMD_OUTPUT}")
	endif()
	
	execute_process(COMMAND ${CMAKE_COMMAND}
		--build ${CMAKE_CURRENT_BINARY_DIR}${COMPILER_PROJECT_PATH}
		RESULT_VARIABLE CMD_ERROR
		OUTPUT_VARIABLE CMD_OUTPUT
    )
	if(${CMD_ERROR} EQUAL 0)
		set(GENERATOR_EXECUTABLE "${CMAKE_CURRENT_BINARY_DIR}${COMPILER_PROJECT_PATH}/Debug/vdtreflect-compiler.exe" PARENT_SCOPE)
		message(STATUS "Reflection compiler built: \n${CMD_OUTPUT}\npath: ${GENERATOR_EXECUTABLE}")
	else()
		message(STATUS "Failed to build reflection compiler: ${CMD_ERROR}\n${CMD_OUTPUT}")
	endif()
endfunction()

set (COMPILER_PROJECT_PATH "/vendor/vdtreflect/compiler")

# build reflection compiler
build_reflection_compiler(${COMPILER_PROJECT_PATH})

#propagate var to parent scope
set(GENERATOR_EXECUTABLE "${GENERATOR_EXECUTABLE}" PARENT_SCOPE)

# generate reflection data
generate_reflection(${GENERATOR_EXECUTABLE} ${PROJECT_SOURCE_DIR}/src)

# recursively include all source files
file(GLOB_RECURSE PROJECT_SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.h ${PROJECT_SOURCE_DIR}/src/*.cpp)

foreach(_source IN ITEMS ${PROJECT_SOURCE_FILES})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${PROJECT_SOURCE_DIR}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

foreach(_source IN ITEMS ${PROJECT_GENERATED_FILES})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${PROJECT_SOURCE_DIR}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

add_library(
    ${PROJECT_NAME} 
    STATIC
    ${VENDORS_SOURCES}
    ${PROJECT_SOURCE_FILES} 
)

if(MSVC)
	target_compile_options(${PROJECT_NAME} PRIVATE "/MP")
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw EXCLUDE_FROM_ALL)

set(PRECOMPILED_HEADERS "")
if(NOT TARGET vdtmath)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/vdtmath)
	file(GLOB_RECURSE _PRECOMPILED_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/vendor/vdtmath/include/vdtmath/*.h)
	list (APPEND PRECOMPILED_HEADERS ${_PRECOMPILED_HEADERS})
endif()
if(NOT TARGET vdtgraphics)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/vdtgraphics)
	file(GLOB_RECURSE _PRECOMPILED_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/vendor/vdtgraphics/include/vdtgraphics/*.h)
	list (APPEND PRECOMPILED_HEADERS ${_PRECOMPILED_HEADERS})
endif()
if(NOT TARGET vdtjson)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/vdtjson)
	file(GLOB_RECURSE _PRECOMPILED_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/vendor/vdtjson/include/vdtjson/*.h)
	list (APPEND PRECOMPILED_HEADERS ${_PRECOMPILED_HEADERS})
endif()
if(NOT TARGET vdtnet)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/vdtnet)
endif()
if(NOT TARGET vdtreflect)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/vdtreflect)
	file(GLOB_RECURSE _PRECOMPILED_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/vendor/vdtreflect/include/vdtreflect/*.h)
	list (APPEND PRECOMPILED_HEADERS ${_PRECOMPILED_HEADERS})
endif()

target_precompile_headers(${PROJECT_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:${PRECOMPILED_HEADERS}>")

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE ${GLAD_LIBRARIES}
	PRIVATE glfw
	PRIVATE ${GLFW_LIBRARIES}
	PUBLIC vdtgraphics
	PUBLIC vdtjson
	PUBLIC vdtmath
	PUBLIC vdtnet
	PUBLIC vdtreflect
)

target_include_directories(${PROJECT_NAME} PUBLIC 
    src/
)