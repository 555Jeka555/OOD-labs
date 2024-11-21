cmake_minimum_required(VERSION 3.26)
project(lab8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./../bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ./../lib)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

set(SOURCE_FILES
        src/main.cpp
        src/Naive/GumballMachine.h
        src/Naive/GumballMachine.h
        src/WithState/State/IState.h
        src/WithState/IGumballMachine.h
        src/WithState/State/SoldState.h
        src/WithState/State/HasQuarterState.h
        src/WithState/State/SoldOutState.h
        src/WithState/State/NoQuarterState.h
        src/WithState/GumballMachine.h
        src/MultiGumballMachine/MultiGumballMachine.h
        src/MultiGumballMachine/IMultiGumballMachine.h
        src/MultiGumballMachine/State/HasQuarterState.h
        src/MultiGumballMachine/State/IState.h
        src/MultiGumballMachine/State/NoQuarterState.h
        src/MultiGumballMachine/State/SoldOutState.h
        src/MultiGumballMachine/State/SoldState.h
        src/Menu/Menu.cpp
)

set(TEST_SOURCE_FILES
        test/test.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_executable(${PROJECT_NAME}_test ${TEST_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}_test gtest_main gmock gtest)
enable_testing()
add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test)
