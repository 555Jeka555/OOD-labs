cmake_minimum_required(VERSION 3.26)
project(1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./../bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ./../lib)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

set(SOURCE_FILES
        src/1_1/Observer.h
        src/1_1/WeatherData.h
        src/1_2/Observer.h
        src/1_2/WeatherData.h
        src/main.cpp
)

set(TEST_SOURCE_FILES
        test/test.cpp
)

add_executable(1_1 ${SOURCE_FILES})

add_executable(1_1_test ${TEST_SOURCE_FILES})
target_link_libraries(1_1_test gtest_main)
enable_testing()
add_test(NAME 1_1_test COMMAND 1_1_test)
