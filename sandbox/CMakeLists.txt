cmake_minimum_required(VERSION 2.6)
project(Sandbox)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

include_directories( 
	src/
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../engine ${CMAKE_CURRENT_BINARY_DIR}/engine)

# generate proto files
file(GLOB_RECURSE PROJECT_TO_GENERATE_FILES ${PROJECT_SOURCE_DIR}/src/*.h)

 foreach(_source IN ITEMS ${PROJECT_TO_GENERATE_FILES})
 	generate_reflection(${_source})
 endforeach()

# recursively include all source files
file(GLOB_RECURSE PROJECT_SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.h ${PROJECT_SOURCE_DIR}/src/*.cpp)

foreach(_source IN ITEMS ${PROJECT_SOURCE_FILES})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${PROJECT_SOURCE_DIR}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

add_executable(
    ${PROJECT_NAME} 
    ${PROJECT_SOURCE_FILES} 
)

SET(CMAKE_DEFAULT_STARTUP_PROJECT Sandbox)

set_target_properties(${PROJECT_NAME} PROPERTIES 
    LINK_FLAGS "/ENTRY:mainCRTStartup /SUBSYSTEM:WINDOWS")

target_link_libraries(
    ${PROJECT_NAME} 
    AwesomeEngine
)
