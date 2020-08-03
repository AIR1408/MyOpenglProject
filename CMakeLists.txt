cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

set(proj_name TestOpenglEngine)
project(${proj_name})

add_executable(${proj_name} 
	main.cpp
	src/renderer/shaderProgram.cpp
	src/renderer/shaderProgram.h
	src/renderer/object.cpp
	src/renderer/object.h
	src/resource_manager/ResourceManager.cpp
	src/resource_manager/ResourceManager.h
	src/extra/extra.cpp
	src/extra/extra.h
)

target_compile_features(${proj_name} PUBLIC cxx_std_17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${proj_name} glfw)

add_subdirectory(external/glad)
target_link_libraries(${proj_name} glad)

set_target_properties(${proj_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY $(CMAKE_BINARY_DIR)/bin/)
add_custom_command(TARGET ${proj_name} POST_BUILD 
					COMMAND ${CMAKE_COMMAND} -E copy_directory 
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)