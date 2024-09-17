cmake_minimum_required(VERSION 3.26)
project(4)

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
        src/Controller/ShapeController.h
        src/Service/ShapeService.h
        src/Canvas/ICanvas.h
        src/Shape/Shape.h
        src/Shape/DrawingStrategy/IDrawingStrategy.h
        src/Shape/DrawingStrategy/RectangleDrawingStrategy.h
        src/Service/ShapeType.h
        src/Service/ShapeTypeConverter.h
        src/Service/ShapeService.cpp
        src/Controller/ShapeController.cpp
)

set(TEST_SOURCE_FILES
        test/test.cpp
        src/Service/ShapeService.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_executable(${PROJECT_NAME}_test ${TEST_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}_test gtest_main)
enable_testing()
add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test)
