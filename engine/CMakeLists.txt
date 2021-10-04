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
	vendor/stb/
	vendor/imgui/
)

# GLFW options
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)

# include vendors files
file(GLOB VENDORS_SOURCES 
	vendor/glad/src/glad.c
	vendor/imgui/examples/imgui_impl_glfw.cpp
	vendor/imgui/examples/imgui_impl_opengl3.cpp
	vendor/imgui/imgui.cpp
	vendor/imgui/imgui_demo.cpp
	vendor/imgui/imgui_draw.cpp
	vendor/imgui/imgui_widgets.cpp
) 	
source_group("Vendors" FILES ${VENDORS_SOURCES})

# recursively include all source files
file(GLOB_RECURSE PROJECT_SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.h ${PROJECT_SOURCE_DIR}/src/*.cpp)
if(WIN32 OR UNIX OR APPLE)
	file(GLOB_RECURSE DESKTOP_SOURCE_FILES ${PROJECT_SOURCE_DIR}/platform/desktop/*.h ${PROJECT_SOURCE_DIR}/platform/desktop/*.cpp)
	list(APPEND PROJECT_SOURCE_FILES ${DESKTOP_SOURCE_FILES})
endif()

foreach(_source IN ITEMS ${PROJECT_SOURCE_FILES})
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

target_link_libraries(
    ${PROJECT_NAME}  
    ${GLAD_LIBRARIES}
	glfw
	${GLFW_LIBRARIES}
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw)