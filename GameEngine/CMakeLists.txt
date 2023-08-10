cmake_minimum_required(VERSION 3.5...3.25)
project(GameEngine)

set(CMAKE_CXX_STANDARD 14)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp") #Not the best solution, however it would be tedious to add these manually.

#add_executable(${PROJECT_NAME} ${SOURCES})
add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME}
    PUBLIC 
        ${SRC_DIR}
)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# GLFW
set(GLFW_DIR ${LIB_DIR}/submodules/glfw/)
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory(${GLFW_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC glfw ${GLFW_LIBRARIES})
target_compile_definitions(${PROJECT_NAME} PUBLIC GLFW_INCLUDE_NONE)

#GLAD
set(GLAD_DIR ${LIB_DIR}/glad/)
add_subdirectory(${GLAD_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC glad ${CMAKE_DL_LIBS})

#GLM
set(GLM_DIR ${LIB_DIR}/submodules/glm/)
add_subdirectory(${GLM_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC glm)


#SPDLOG
set(SPDLOG_DIR ${LIB_DIR}/submodules/spdlog/)
add_subdirectory(${SPDLOG_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog)
