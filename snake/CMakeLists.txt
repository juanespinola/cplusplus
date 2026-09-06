cmake_minimum_required(VERSION 3.20)
project(snake LANGUAGES CXX)
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
 
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
 
add_executable(snake main.cpp char_letras.cpp)
 
target_include_directories(snake PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(snake PRIVATE ${SDL2_LIBRARIES})
target_compile_options(snake PRIVATE ${SDL2_CFLAGS_OTHER})
 
if(WIN32)
    add_custom_command(TARGET snake POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:snake>
            $<TARGET_FILE_DIR:snake>
        COMMAND_EXPAND_LISTS
    )
endif()
 
