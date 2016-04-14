cmake_minimum_required (VERSION 2.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES ../rrbroker.c ../rrclient.c ../rrworker.c)

# Worker
add_executable(rrworker ../rrworker.c)
target_link_libraries(rrworker zmq)

# Client
add_executable(rrclient ../rrclient.c)
target_link_libraries(rrclient zmq)

# Broker
add_executable(rrbroker ../rrbroker.c)
target_link_libraries(rrbroker zmq)