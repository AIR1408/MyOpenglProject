cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

project(TestOpenglEngine)

add_executable(${PROJECT_NAME} 
	main.cpp
#	src/resource_manager/stb_image.h
	src/renderer/ShaderProgram.cpp
	src/renderer/Mesh.cpp
	src/resource_manager/ResourceManager.cpp
	src/extra/extra.cpp
	src/objects/Camera.cpp
	src/renderer/Model.cpp
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

include_directories(external/glm)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY $(CMAKE_BINARY_DIR)/bin/)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
					COMMAND ${CMAKE_COMMAND} -E copy_directory 
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)