cmake_minimum_required(VERSION 3.15)
project(blxr)

set(CMAKE_CXX_STANDARD 14)

add_executable(blxr src/main.cpp src/keyconst.h src/keyhook.cpp src/keyhook.h src/stream.h src/stream.cpp src/keyconst.cpp)