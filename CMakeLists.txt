cmake_minimum_required(VERSION 3.10)

project(RenderDEMO)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

## Dependencies ##

add_subdirectory(external)

## Build App ##

add_subdirectory(src)