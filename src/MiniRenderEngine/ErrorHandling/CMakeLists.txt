add_library(error_handling OBJECT error_handling.cpp)

# Superior targets can import this file without the relative path
# target_include_directories(cars PUBLIC .)