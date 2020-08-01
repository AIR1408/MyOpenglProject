cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

set(proj_name TestOpenglEngine)
project(${proj_name})

set(CMAKE_CXX_STANDARD 17)

add_executable(${proj_name} 
	main.cpp
	src/renderer/shaderProgram.cpp
	src/renderer/shaderProgram.h
	src/renderer/object.cpp
	src/renderer/object.h
	src/extra/extra.h
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${proj_name} glfw)

add_subdirectory(external/glad)
target_link_libraries(${proj_name} glad)