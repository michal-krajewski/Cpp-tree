cmake_minimum_required(VERSION 3.8)
project(Lab3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp CNode.cpp CNode.h CTree.cpp CTree.h CVariable.cpp CVariable.h)
add_executable(Lab3 ${SOURCE_FILES})