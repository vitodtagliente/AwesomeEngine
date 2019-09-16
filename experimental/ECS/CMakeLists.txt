cmake_minimum_required(VERSION 2.6)
project(ECS)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

file(GLOB PROJECT_HEADERS src/*.h) 
file(GLOB PROJECT_SOURCES src/*.cpp)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})

add_executable(
    ${PROJECT_NAME} 
    ${PROJECT_SOURCES} 
)

target_link_libraries(
    ${PROJECT_NAME} 
)

SET(CMAKE_DEFAULT_STARTUP_PROJECT ECS)