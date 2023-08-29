cmake_minimum_required(VERSION 3.2)
project(Survivalpp)

set(CMAKE_CXX_STANDARD 20)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if(ASAN_ENABLED)
	string(REGEX REPLACE "/RTC(su|[1su])" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}\n")
	add_compile_options(-fsanitize=address -fsanitize=fuzzer)
endif()

include_directories( 
	src/
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/vendor/glad/include/
	${CMAKE_CURRENT_SOURCE_DIR}/../engine/vendor/glfw/include/
)

# include vendors files
file(GLOB VENDORS_SOURCES 
	${CMAKE_CURRENT_SOURCE_DIR}/../engine/vendor/glad/src/glad.c
) 	
source_group("Vendors" FILES ${VENDORS_SOURCES})

# recursively include all source files
file(GLOB_RECURSE PROJECT_SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.h ${PROJECT_SOURCE_DIR}/src/*.hpp ${PROJECT_SOURCE_DIR}/src/*.cpp)

foreach(_source IN ITEMS ${PROJECT_SOURCE_FILES})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${PROJECT_SOURCE_DIR}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

if(NOT TARGET glfw)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../engine/vendor/glfw ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw)
endif()

if(NOT TARGET vdtgraphics)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../engine/vendor/vdtgraphics ${CMAKE_CURRENT_SOURCE_DIR}/vendor/vdtgraphics)
endif()

add_executable(
    ${PROJECT_NAME} 
    ${PROJECT_SOURCE_FILES} 
    ${VENDORS_SOURCES}
)

target_link_libraries(
    ${PROJECT_NAME} 
    PRIVATE ${GLAD_LIBRARIES}
	PRIVATE glfw
	PRIVATE ${GLFW_LIBRARIES}
	PUBLIC vdtgraphics
)

if(MSVC)
	target_compile_options(${PROJECT_NAME} PRIVATE "/MP")
endif()

SET(CMAKE_DEFAULT_STARTUP_PROJECT ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES 
    LINK_FLAGS "/ENTRY:mainCRTStartup /SUBSYSTEM:WINDOWS")