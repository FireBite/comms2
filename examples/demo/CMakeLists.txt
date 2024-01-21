cmake_minimum_required(VERSION 3.15)

project(demo)

add_executable(serialize serialize.cpp)
target_link_libraries(serialize PUBLIC etl::etl comms2)

add_executable(cobs cobs.cpp)
target_link_libraries(cobs PUBLIC etl::etl comms2)

add_executable(serialize_buffers serialize_buffers.cpp)
target_link_libraries(serialize_buffers PUBLIC etl::etl comms2)