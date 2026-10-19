cmake_minimum_required(VERSION 3.20)
project(snake LANGUAGES CXX)
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
 
find_package(SDL2 REQUIRED CONFIG)
 
add_executable(
    snake main.cpp 
    char_letras.cpp 
    scene_manager.cpp 
    menu_scene.cpp 
    playing_scene.cpp
    timer.cpp
)
 
if(TARGET SDL2::SDL2main)
    target_link_libraries(snake PRIVATE SDL2::SDL2main)
endif()
target_link_libraries(snake PRIVATE SDL2::SDL2)
 
if(WIN32)
    add_custom_command(TARGET snake POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:snake>
            $<TARGET_FILE_DIR:snake>
        COMMAND_EXPAND_LISTS
    )
endif()
 
