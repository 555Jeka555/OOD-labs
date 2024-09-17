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
        src/1_1/main.cpp
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
        src/3_1/Duck/MallardDuck.h
        src/3_1/Duck/ModelDuck.h
        src/3_1/Duck/RedHeadDuck.h
        src/3_1/Duck/RubberDuck.h
)

set(TEST_SOURCE_FILES
        test/1_1/test.cpp
)

add_executable(1_1 ${SOURCE_FILES})

add_executable(1_1_test ${TEST_SOURCE_FILES})
target_link_libraries(1_1_test gtest_main)
enable_testing()
add_test(NAME 1_1_test COMMAND 1_1_test)


set(SOURCE_FILES_2
        src/2_1/main.cpp
        src/2_1/Duck/Duck.h
        src/2_1/Duck/MallardDuck.h
        src/2_1/Duck/ModelDuck.h
        src/2_1/Duck/RedheadDuck.h
        src/2_1/Duck/RubberDuck.h
        src/2_1/DuckFunctions.h
        src/2_1/Duck/Fly/IFlyBehavior.h
        src/2_1/Duck/Fly/FlyNoWay.h
        src/2_1/Duck/Fly/FlyWithWings.h
        src/2_1/Duck/Quack/IQuackBehavior.h
        src/2_1/Duck/Quack/MuteQuackBehavior.h
        src/2_1/Duck/Quack/QuackBehavior.h
        src/2_1/Duck/Quack/SqueakBehavior.h
        src/2_1/Duck/Dance/IDanceBehavior.h
        src/2_1/Duck/Dance/DanceWaltzBehavior.h
        src/2_1/Duck/Dance/DanceMinuetBehavior.h
        src/2_1/Duck/Dance/NoDanceBehavior.h
)

set(TEST_SOURCE_FILES_2
        test/2_1/test.cpp
)

add_executable(2_1 ${SOURCE_FILES_2})

add_executable(2_1_test ${TEST_SOURCE_FILES_2})
target_link_libraries(2_1_test gtest_main)
enable_testing()
add_test(NAME 2_1_test COMMAND 2_1_test)


set(SOURCE_FILES_3
        src/3_1/main.cpp
        src/3_1/Duck.h
        src/3_1/DuckFunctions.h
        src/3_1/Duck/MallardDuck.h
        src/3_1/Duck/ModelDuck.h
        src/3_1/Duck/RedHeadDuck.h
        src/3_1/Duck/RubberDuck.h
)

set(TEST_SOURCE_FILES_3
        test/3_1/test.cpp
)

add_executable(3_1 ${SOURCE_FILES_3})

add_executable(3_1_test ${TEST_SOURCE_FILES_3})
target_link_libraries(3_1_test gtest_main)
enable_testing()
add_test(NAME 3_1_test COMMAND 3_1_test)
