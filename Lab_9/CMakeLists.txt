cmake_minimum_required(VERSION 3.5)
project(Lab_9)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Lab_9/Lab_9.cpp
    Lab_9/stdafx.cpp
    Lab_9/stdafx.h
    Lab_9/targetver.h)

add_executable(Lab_9 ${SOURCE_FILES})