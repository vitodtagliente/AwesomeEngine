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
    ../vendor/glad/include/
	../vendor/glm/
)

file(GLOB VENDORS_SOURCES 

)
file(GLOB PROJECT_HEADERS *.h include/*.h) 
file(GLOB PROJECT_SOURCES *.cpp)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Vendors" FILES ${VENDORS_SOURCES})

add_executable(
    ${PROJECT_NAME} 
    ${PROJECT_SOURCES} 
    ${PROJECT_HEADERS}
    ${VENDORS_SOURCES}
)

target_link_libraries(
    ${PROJECT_NAME} 
    AwesomeEngine
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../engine ${CMAKE_CURRENT_BINARY_DIR}/engine)
