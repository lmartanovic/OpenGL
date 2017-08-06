cmake_minimum_required(VERSION 3.7)
project(OpenGL)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -Wall -Wextra -Werror -pedantic")

#set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules/")
set(SFML_LIB_ROOT "/usr/lib/x86_64-linux-gnu")

#add_definitions("-D_GLIBCXX_USE_CXX11_ABI=0")

#include_directories(../Libs/imgui-master
#                    ../Libs/imgui-sfml-master)

#@todo create a separate target (OBJECT) for imgui stuff
    #                 ../Libs/imgui-master/imgui.cpp
    #             ../Libs/imgui-master/imgui_draw.cpp
    #             ../Libs/imgui-sfml-master/imgui-SFML.cpp)

include_directories(system /usr/include/SFML)

add_subdirectory(src)
