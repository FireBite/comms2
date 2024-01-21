cmake_minimum_required(VERSION 3.15)

project(libcomms2)

# Library uses features from C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

# Build library
file(GLOB_RECURSE comms2_SRC "src/*.cpp")
add_library(comms2 STATIC ${comms2_SRC})
include_directories(include)

Include(FetchContent)
FetchContent_Declare(
  etl
  GIT_REPOSITORY https://github.com/ETLCPP/etl
  GIT_TAG        20.38.10
)
FetchContent_MakeAvailable(etl)
target_link_libraries(comms2 PRIVATE etl::etl)

# Build tests
if(NOT DEFINED LIBCOMMS2_NO_TESTS)
  message(STATUS "Building tests")
  include(tests/testing.cmake)
else()
  message(STATUS "Skipping tests")
endif()

# Build examples
add_subdirectory(examples/demo)