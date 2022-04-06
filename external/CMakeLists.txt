## Graphic Dependecies ##

add_library(external_graphics_deps INTERFACE)

add_subdirectory(glad)
add_subdirectory(glfw)

target_include_directories(external_graphics_deps 
    INTERFACE
        glfw/include
        glad/include
)

target_link_directories(external_graphics_deps
    INTERFACE 
        glfw/src
        glad/src
)

target_link_libraries(external_graphics_deps 
    INTERFACE 
        glfw
        glad
)

## Other Dependencies ##

add_subdirectory(glm)

add_library(other_external_deps INTERFACE)

target_link_libraries(other_external_deps 
    INTERFACE
        glm
)


## External Dependencies Library ##

add_library(app_external_deps INTERFACE)

target_link_libraries(app_external_deps INTERFACE 
    external_graphics_deps
    other_external_deps
)