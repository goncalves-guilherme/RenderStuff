add_subdirectory(ErrorHandling)

add_executable(${PROJECT_NAME} 
    main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    app_external_deps
    error_handling
    )