cmake_minimum_required(VERSION 3.5)
project(Dengue)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Agent.cpp Agent.h ImmuneState.cpp ImmuneState.h Population.cpp Population.h)
add_executable(Dengue ${SOURCE_FILES})