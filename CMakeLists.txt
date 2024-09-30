cmake_minimum_required(VERSION 3.26)
project(3DViewer)

set(CMAKE_CXX_STANDARD 14)

add_executable(3DViewer
        src/Model/object.cc
        src/Model/main.cc)
