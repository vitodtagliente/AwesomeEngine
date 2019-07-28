cmake_minimum_required(VERSION 2.6)
project(amake)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
endif()

include_directories( 
	src/
)

# recursively include all source files
file(GLOB_RECURSE PROJECT_SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.h ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(
    ${PROJECT_NAME} 
    ${PROJECT_SOURCE_FILES} 
)

target_link_libraries(
    ${PROJECT_NAME} 
)
