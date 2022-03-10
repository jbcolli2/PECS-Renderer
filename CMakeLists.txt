cmake_minimum_required(VERSION 3.21)
project(PECS_Renderer)

set(CMAKE_CXX_STANDARD 17)
# tell where to find the find_package files
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")


# find the required packages
set(GLM_ROOT_DIR ./)
find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")
find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")
find_package(ASSIMP REQUIRED)
message(STATUS "Found ASSIMP in ${ASSIMP_INCLUDE_DIR}")

# add glfw to library list
set(LIBS ${LIBS} ${GLFW3_LIBRARY})

#set include directories
include_directories(${GLM_INCLUDE_DIR} ${GLFW3_INCLUDE_DIR} ${ASSIMP_INCLUDE_DIR} src)

# add glad to library list
add_library(GLAD include/glad/glad.c)
set(LIBS ${LIBS} GLAD)

add_executable(PECS_Renderer src/TestRenderer.cpp src/Objects/Object.cpp src/Components/Component.cpp src/Components/ComponentManager.cpp src/Components/ComponentManager.hpp src/Util.hpp src/Components/Renderable.hpp src/Systems/System.cpp src/Systems/System.hpp src/Systems/RenderPipeline.cpp src/Systems/RenderPipeline.hpp src/RenderUtil.hpp src/Engine/Shader.cpp src/Util.cpp src/RenderUtil.cpp)
target_link_libraries(PECS_Renderer ${LIBS})

add_executable(Playground Playground/main.cpp)
