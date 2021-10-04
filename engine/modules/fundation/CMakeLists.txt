cmake_minimum_required(VERSION 3.2)
if(TARGET fundation)
	return()
endif()
project(fundation)

set(CMAKE_CXX_STANDARD 17)

include_directories( 
    src/
)

# recursively include all source files
file(GLOB_RECURSE PROJECT_SOURCES src/*.h src/*.cpp)

foreach(_source IN ITEMS ${PROJECT_SOURCES})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${PROJECT_SOURCE_DIR}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

add_library(
    ${PROJECT_NAME} 
	STATIC
    ${PROJECT_HEADERS}
    ${PROJECT_SOURCES} 
)

target_include_directories(${PROJECT_NAME} PUBLIC src)