cmake_minimum_required(VERSION 2.6)
project(demo)

set(CMAKE_CXX_STANDARD 11)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

include_directories( 
	. 
	include/
    ../engine/include/
)

# recursively include all C++ files
file(GLOB_RECURSE PROJECT_SOURCE_FILES ${PROJECT_SOURCE_DIR}/"include" ${PROJECT_SOURCE_DIR}/"src" "*.h" "*.hpp" "*.cpp")

# I then wrote this Macro, which organize the files in visual studio folders,
# according to the organization in the file systems
macro(GroupSources curdir)
	file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir} ${PROJECT_SOURCE_DIR}/${curdir}/*)
	foreach(child ${children})
		if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})
			GroupSources(${curdir}/${child})
		else()
			string(REPLACE "/" "\\" groupname ${curdir})
			source_group(${groupname} FILES	${PROJECT_SOURCE_DIR}/${curdir}/${child})
		endif()
	endforeach()
endmacro()
   
# Execute the macro
GroupSources("include")
GroupSources("src")

add_executable(
    ${PROJECT_NAME} 
    ${PROJECT_SOURCE_FILES} 
)

target_link_libraries(
    ${PROJECT_NAME} 
    AwesomeEngine
)

SET(CMAKE_DEFAULT_STARTUP_PROJECT demo)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../engine ${CMAKE_CURRENT_BINARY_DIR}/engine)
