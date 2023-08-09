# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug$<$<CONFIG:Debug>:Debug>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")

add_subdirectory("../GameEngine/" "${CMAKE_CURRENT_BINARY_DIR}/libs/GameEngine")

project ("Sandbox")

add_executable(${PROJECT_NAME} Sandbox/Sandbox.cpp Sandbox/Sandbox.h)

target_link_libraries(${PROJECT_NAME} PRIVATE GameEngine)