# Prepare GTest library
cmake_policy(SET CMP0135 NEW) #DOWNLOAD_EXTRACT_TIMESTAMP

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Build tests
enable_testing()

add_executable(
  libcomms2_tests
  tests/FTPFrame.cpp
)
target_link_libraries(
  libcomms2_tests
  GTest::gtest_main
  comms2
  etl::etl
)

include(GoogleTest)
gtest_discover_tests(libcomms2_tests)
