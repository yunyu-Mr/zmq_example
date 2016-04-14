cmake_minimum_required(VERSION 3.3)
project(zmq_example)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES interrupt.c)

# Signal handling
add_executable(interrupt interrupt.c)
target_link_libraries(interrupt zmq)

# Pipeline & pipeline2
add_subdirectory(pipeline/cmake-build)

# add Extend Request Reply Pattern
add_subdirectory(extendReqRep/cmake-build)