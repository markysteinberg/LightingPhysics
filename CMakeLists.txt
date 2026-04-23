cmake_minimum_required(VERSION 3.20)
project(balls CXX C)

include(FetchContent) 

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

#GLFW 
find_package(glfw3 QUIET) 
if(NOT glfw3_FOUND)
	FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG 3.3.8)
	FetchContent_MakeAvailable(glfw)
	set(GLFW_TARGET glfw)
else() 
	set(GLFW_TARGET glfw) 
endif() 

#GLM
find_package(glm QUIET) 
if(NOT glm_FOUND) 
	FetchContent_Declare(glm GIT_REPOSITORY https://github.com/g-truc/glm.git GIT_TAG 0.9.9.8) 
	FetchContent_MakeAvailable(glm)
	set(GLM_TARGET glm)
else()
	set(GLM_TARGET glm::glm)
endif() 

#Assimp
find_package(assimp QUIET)
if(NOT assimp_FOUND)
	FetchContent_Declare(assimp GIT_REPOSITORY https://github.com/assimp/assimp.git GIT_TAG v5.3.1)
	FetchContent_MakeAvailable(assimp)
	set(ASSIMP_TARGET assimp)
else() 
	set(ASSIMP_TARGET assimp)
endif()

find_package(OpenGL REQUIRED)

set(CPP_SOURCES 
    src/main.cpp 
	src/window.cpp
	src/shader.cpp
	src/mesh.cpp
	src/object.cpp
	src/renderer.cpp
	src/engine.cpp
	src/floor_grid.cpp
	src/camera.cpp
)

add_library(glad STATIC src/glad.c)
target_include_directories(glad PUBLIC includes)

add_executable(balltest ${CPP_SOURCES})

if(MSVC)
	target_compile_options(balltest PRIVATE /W4)
else()
	target_compile_options(balltest PRIVATE -Werror -Wall -Wpedantic -O0 -g)
endif()
target_compile_features(balltest PRIVATE cxx_std_20)

target_include_directories(balltest PRIVATE includes)

if(UNIX)
    target_link_libraries(balltest PRIVATE glad ${GLFW_TARGET} ${ASSIMP_TARGET} ${GLM_TARGET} OpenGL::GL dl) 
elseif(WIN32)
	target_link_libraries(balltest PRIVATE glad ${GLFW_TARGET} ${ASSIMP_TARGET} ${GLM_TARGET} opengl32) 
else() 
    message(FATAL_ERROR "THIS PLATFORM IS UNSUPPORTED")
endif()





