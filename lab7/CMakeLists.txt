cmake_minimum_required(VERSION 3.26)
project(lab7)

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
        src/Canvas/PNGCanvas/PNGCanvas.h
        src/Canvas/PNGCanvas/PNGCanvas.cpp
        src/Canvas/PNGCanvas/stb_image_write.h
        src/Canvas/PNGCanvas/stb_truetype.h
        src/Client.h
        src/ShapeFactory/IShapeFactory.h
        src/ShapeFactory/ShapeFactory.h
        src/Shape/Triangle.h
        src/Shape/Rectangle.h
        src/Shape/Ellipse.h
        src/Shape/Shape.h
        src/Shape/Style/IStyle.h
        src/Shape/Style/Style.h
        src/Shape/IShape.h
        src/IDrawable.h
        src/Shape/IGroupShape.h
        src/Shape/GroupShape.h
        src/Shape/IShapes.h
        src/Slide/ISlide.h
        src/Slide/Slide.h
        src/Slide/SlideService.h
        src/CommonTypes.h
        src/Shape/Style/ProxyStyle.h
)

set(TEST_SOURCE_FILES
        test/test.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_executable(${PROJECT_NAME}_test ${TEST_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}_test gtest_main gmock gtest)
enable_testing()
add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test)
