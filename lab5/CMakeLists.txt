cmake_minimum_required(VERSION 3.26)
project(lab5)

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
        src/Document/IDocument.h
        src/IParagraph.h
        src/IImage.h
        src/Document/ConstDocumentItem.h
        src/Document/DocumentItem.h
        src/Menu/Menu.cpp
        src/Menu/Menu.h
        src/Document/Document.cpp
        src/Document/Document.h
)

set(TEST_SOURCE_FILES
        test/test.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_executable(${PROJECT_NAME}_test ${TEST_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}_test gtest_main gmock gtest)
enable_testing()
add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test)