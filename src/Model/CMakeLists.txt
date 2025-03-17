cmake_minimum_required(VERSION 3.26)
project(3DViewer)

set(CMAKE_CXX_STANDARD 17)

add_executable(3DViewer
        object.cc
        object.h
        ../main_test.cc
        ../Controller/controller.h
        ../Controller/controller.cc
        Transformations/transformations.h
        Transformations/move_object.cc
        Transformations/move_object.h
        Transformations/zoom_object.cc
        Transformations/zoom_object.h
        Transformations/rotate_object.cc
        Transformations/rotate_object.h
        ../View/view.h
        ../View/opengl_view.h
        ../View/opengl_view.cc
        ../View/view.cc
)