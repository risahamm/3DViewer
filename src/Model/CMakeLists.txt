cmake_minimum_required(VERSION 3.26)
project(3DViewer)

set(CMAKE_CXX_STANDARD 17)

add_executable(3DViewer
        object.cc
        object.h
        main_test.cc
        ../Controller/controller.h
        ../Controller/controller.cc
        transformations.cc
        transformations.h
        move_object.cc
        move_object.h
        zoom_object.cc
        zoom_object.h
)