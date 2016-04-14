cmake_minimum_required(VERSION 3.3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES ../worker.c ../ventilator.c ../sink.c)

# Signal handling
add_executable(worker ../worker.c)
target_link_libraries(worker zmq)

add_executable(ventilator ../ventilator.c)
target_link_libraries(ventilator zmq)

add_executable(sink ../sink.c)
target_link_libraries(sink zmq)
