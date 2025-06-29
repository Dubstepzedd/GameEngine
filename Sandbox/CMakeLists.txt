# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug$<$<CONFIG:Debug>:Debug>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
message(STATUS=${CMAKE_CURRENT_BINARY_DIR})
add_subdirectory("../GameEngine/" "${CMAKE_CURRENT_BINARY_DIR}/libs/GameEngine")

project ("Sandbox")

add_executable(${PROJECT_NAME} "Sandbox/Sandbox.cpp" "Sandbox/Sandbox.h" "Sandbox/TestLayer.cpp" "Sandbox/TestLayer.h")

target_link_libraries(${PROJECT_NAME} PRIVATE GameEngine)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/res
            ${CMAKE_CURRENT_BINARY_DIR}/res
)
