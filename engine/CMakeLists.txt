cmake_minimum_required(VERSION 3.2)
project(AwesomeEngine)

# enable the C++ 11 standard
set(CMAKE_CXX_STANDARD 17)
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
	vendor/stb/
	vendor/vdtproto/include/
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

set(GENERATOR_EXECUTABLE "${CMAKE_CURRENT_SOURCE_DIR}/tools/compiler/vdtreflect-compiler.exe")

function(generate_reflection EXECUTABLE SRC_FILE)
	execute_process(
		COMMAND ${EXECUTABLE} ${SRC_FILE}
		RESULT_VARIABLE CMD_ERROR
		OUTPUT_FILE CMD_OUTPUT
	)
	if(${CMD_ERROR} EQUAL 0)
		message(STATUS "Generated C++ code for ${SRC_FILE}")
	else()
		message(STATUS "`${SRC_FILE}` failed to generate C++ code with error: ${CMD_ERROR}")
	endif()
endfunction()

# generate proto files
file(GLOB_RECURSE PROJECT_TO_GENERATE_FILES ${PROJECT_SOURCE_DIR}/src/*.h)

message(STATUS "Using generator: ${_src_path} ${GENERATOR_EXECUTABLE}")
 foreach(_source IN ITEMS ${PROJECT_TO_GENERATE_FILES})
 	generate_reflection(${GENERATOR_EXECUTABLE} ${_source})
 endforeach()

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

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw)

if(NOT TARGET vdtmath)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/vdtmath)
endif()
if(NOT TARGET vdtgraphics)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/vdtgraphics)
endif()
if(NOT TARGET vdtjson)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/vdtjson)
endif()
if(NOT TARGET vdtnet)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/vdtnet)
endif()
if(NOT TARGET vdtreflect)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/vdtreflect)
endif()

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

target_include_directories(${PROJECT_NAME} PUBLIC src vendor/vdtproto/include)