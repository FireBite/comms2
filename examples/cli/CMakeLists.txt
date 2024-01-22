cmake_minimum_required(VERSION 3.15)

project(cli)

add_executable(cli cli.cpp)
target_link_libraries(cli PRIVATE comms2 etl::etl)