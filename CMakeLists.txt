cmake_minimum_required(VERSION 3.13)
set(CMAKE_SUPPRESS_REGENERATION true)

project(MyProject)
add_subdirectory(external/glfw)


file(GLOB IMGUI_SRC external/imgui/*.cpp)




include_directories(external/glfw/include
                     external/imgui)


link_directories(external/glfw/src)

link_libraries(glfw opengl32)
set(CMAKE_CXX_STANDARD 11)
add_executable(${PROJECT_NAME} main.cpp ${IMGUI_SRC})

file(COPY fonts DESTINATION ${CMAKE_BINARY_DIR})