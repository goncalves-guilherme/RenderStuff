cmake_minimum_required(VERSION 3.10)

project(RenderDEMO)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} src/main.cpp)

add_subdirectory(external/glfw)

target_include_directories(${PROJECT_NAME} 
    PUBLIC 
        #TestLib
        external/glfw/include
)

target_link_directories(${PROJECT_NAME}
    PRIVATE external/glfw/src
)

target_link_libraries(${PROJECT_NAME} glfw)