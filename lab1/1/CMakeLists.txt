cmake_minimum_required(VERSION 3.26)
project(1)

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
        src/1_1/Duck/Duck.h
        src/1_1/Duck/MallardDuck.h
        src/1_1/Duck/ModelDuck.h
        src/1_1/Duck/RedheadDuck.h
        src/1_1/Duck/RubberDuck.h
        src/1_1/DuckFunctions.h
        src/1_1/Duck/Fly/IFlyBehavior.h
        src/1_1/Duck/Fly/FlyNoWay.h
        src/1_1/Duck/Fly/FlyWithWings.h
        src/1_1/Duck/Quack/IQuackBehavior.h
        src/1_1/Duck/Quack/MuteQuackBehavior.h
        src/1_1/Duck/Quack/QuackBehavior.h
        src/1_1/Duck/Quack/SqueakBehavior.h
        src/1_1/Duck/Dance/IDanceBehavior.h
        src/1_1/Duck/Dance/DanceWaltzBehavior.h
        src/1_1/Duck/Dance/DanceMinuetBehavior.h
        src/1_1/Duck/Dance/NoDanceBehavior.h
)

set(TEST_SOURCE_FILES
        test/1_1/test.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_executable(${PROJECT_NAME}_test ${TEST_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}_test gtest_main)
enable_testing()
add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test)
