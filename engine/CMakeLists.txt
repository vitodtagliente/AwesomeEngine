cmake_minimum_required(VERSION 3.2)
project(AwesomeEngine)

# enable the C++ 11 standard
set(CMAKE_CXX_STANDARD 17)
# set the default path for built libraries to the "lib" directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib/)

# specify my include directory 
include_directories( 
    src/
    vendor/glad/include/
	vendor/glfw/include/
	vendor/IconFontCppHeaders/
	vendor/imgui/
	vendor/imgui/misc/cpp/
	vendor/miniaudio/
	vendor/stb/
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

set(FLATC_CMD "${CMAKE_CURRENT_SOURCE_DIR}/vendor/flatc/flatc.exe")
function(compile_fbs SRC_FBS)
	get_filename_component(_fbs_path "${SRC_FBS}" PATH)
	message(STATUS "`${SRC_FBS}`: add generation of C++ code in ${_fbs_path}")
	execute_process(
		COMMAND ${FLATC_CMD} --cpp -o ${_fbs_path} ${SRC_FBS} --no-includes --gen-compare --gen-name-strings
		RESULT_VARIABLE CMD_ERROR
		OUTPUT_FILE CMD_OUTPUT
	)
	message(STATUS "flatc_error:" ${CMD_ERROR})
	message(STATUS "flatc_output:" ${CMD_OUTPUT})
endfunction()

# generate flatbuffers files
file(GLOB_RECURSE PROJECT_FBS_FILES ${PROJECT_SOURCE_DIR}/src/*.fbs)

 foreach(_source IN ITEMS ${PROJECT_FBS_FILES})
 	compile_fbs(${_source})
 endforeach()

# recursively include all source files
file(GLOB_RECURSE PROJECT_SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.h ${PROJECT_SOURCE_DIR}/src/*.cpp)

foreach(_source IN ITEMS ${PROJECT_SOURCE_FILES})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${PROJECT_SOURCE_DIR}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

foreach(_source IN ITEMS ${PROJECT_FBS_FILES})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${PROJECT_SOURCE_DIR}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

add_library(
    ${PROJECT_NAME} 
    STATIC
	${PROJECT_FBS_FILES}
    ${VENDORS_SOURCES}
    ${PROJECT_SOURCE_FILES} 
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw)

# include flatbuffers
if(NOT TARGET flatbuffers)
	add_subdirectory(vendor/flatbuffers ${CMAKE_CURRENT_BINARY_DIR}/flatbuffers-build EXCLUDE_FROM_ALL)
endif()
if(NOT TARGET vdtecs)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/vdtecs)
endif()
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
	PRIVATE flatbuffers
    PRIVATE ${GLAD_LIBRARIES}
	PRIVATE glfw
	PRIVATE ${GLFW_LIBRARIES}
	PUBLIC vdtecs
	PUBLIC vdtgraphics
	PUBLIC vdtjson
	PUBLIC vdtmath
	PUBLIC vdtnet
	PUBLIC vdtreflect
)