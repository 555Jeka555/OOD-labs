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
        src/Picture/Picture.h
        src/Canvas/ICanvas.h
        src/Shape/Shape.h
        src/Shape/DrawingStrategy/IGeometryTypeStrategy.h
        src/Shape/DrawingStrategy/RectangleGeometryTypeStrategy.h
        src/Picture/ShapeType.h
        src/Picture/ShapeTypeConverter.h
        src/Picture/Picture.cpp
        src/Controller/ShapeController.cpp
        src/Shape/DrawingStrategy/CircleGeometryTypeStrategy.h
        src/Shape/DrawingStrategy/TriangleGeometryTypeStrategy.h
        src/Shape/DrawingStrategy/LineGeometryTypeStrategy.h
        src/Shape/DrawingStrategy/TextGeometryTypeStrategy.h
)

set(TEST_SOURCE_FILES
        test/test.cpp
        src/Picture/Picture.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_executable(${PROJECT_NAME}_test ${TEST_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}_test gtest_main)
enable_testing()
add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test)
