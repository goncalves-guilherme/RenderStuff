cmake_minimum_required(VERSION 3.10)

project(RH)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(TestLib)

#target_include_directories(${PROJECT_NAME} PUBLIC TestLib)

#target_link_directories(${PROJECT_NAME} PRIVATE TestLib)

target_link_libraries(${PROJECT_NAME} testlib)