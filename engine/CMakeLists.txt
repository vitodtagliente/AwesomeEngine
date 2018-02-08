cmake_minimum_required(VERSION 3.2)
project(AwesomeEngine)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib/)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
 
include_directories( 
    include/ 
    ../vendor/glad/include/
    ../vendor/glfw/include/
	../vendor/glm/
	../vendor/stb
)

file(GLOB VENDORS_SOURCES 
    ../vendor/glad/src/glad.c
) 
file(GLOB PROJECT_HEADERS 
    include/awesome/*.h	
    include/awesome/rendering/*.h	
    include/awesome/rendering/primitives/*.h	
    include/awesome/rendering/gl/*.h		
    include/awesome/rendering/shading/*.h	
    include/awesome/rendering/components/*.h	
    include/awesome/scenegraph/*.h
	include/awesome/utility/*.h
    include/awesome/windowing/*.h 
)
file(GLOB PROJECT_SOURCES 
    src/*.cpp
	src/rendering/*.cpp    
    src/rendering/primitives/*.cpp  
    src/rendering/gl/*.cpp      
    src/rendering/shading/*.cpp 
    src/rendering/components/*.cpp 
    src/scenegraph/*.cpp
	src/utility/*.cpp
    src/windowing/*.cpp
) 

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Vendors" FILES ${VENDORS_SOURCES})

add_library(
    ${PROJECT_NAME} 
    STATIC
    ${PROJECT_HEADERS}
    ${VENDORS_SOURCES}
    ${PROJECT_SOURCES} 
)

target_link_libraries(
    ${PROJECT_NAME}  
    ${GLAD_LIBRARIES}
    glfw 
    ${GLFW_LIBRARIES} 
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../vendor/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)