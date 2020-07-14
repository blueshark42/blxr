cmake_minimum_required(VERSION 3.15)
project(blxr)

set(CMAKE_CXX_STANDARD 17)

add_executable(blxr src/main.cpp src/keyconst.h src/keyhook.cpp src/keyhook.h src/stream.h src/stream.cpp src/keyconst.cpp
        src/helper.cpp src/helper.h src/screen.cpp src/screen.h src/sys.cpp src/sys.h src/encrypt.cpp src/encrypt.h src/debug.h)