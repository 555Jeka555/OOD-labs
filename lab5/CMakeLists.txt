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
        src/Document/Paragraph/IParagraph.h
        src/Document/Image/IImage.h
        src/Document/ConstDocumentItem.h
        src/Document/DocumentItem.h
        src/Menu/Menu.cpp
        src/Menu/Menu.h
        src/Document/Document/Document.cpp
        src/Document/Document/Document.h
        src/Document/Command/ICommand.h
        src/Document/Command/ICommand_fwd.h
        src/Document/Command/AbstractCommand/AbstractCommand.cpp
        src/Document/Command/AbstractCommand/AbstractCommand.h
        src/CommandHandler.h
        src/Document/History/History.cpp
        src/Document/History/History.h
        src/Document/Command/InsertParagraphCommand/InsertParagraphCommand.cpp
        src/Document/Command/InsertParagraphCommand/InsertParagraphCommand.h
        src/Document/Paragraph/Paragraph.h
        src/Document/Image/Image.h
        src/Document/Command/SetTitleCommand/SetTitleCommand.cpp
        src/Document/Command/SetTitleCommand/SetTitleCommand.h
        src/Document/Command/ReplaceTextCommand/ReplaceTextCommand.cpp
        src/Document/Command/ReplaceTextCommand/ReplaceTextCommand.h
        src/Document/Command/DeleteItemCommand/DeleteItemCommand.cpp
        src/Document/Command/DeleteItemCommand/DeleteItemCommand.h
        src/Document/Command/SaveCommand/SaveCommand.cpp
        src/Document/Command/SaveCommand/SaveCommand.h
        src/Document/Command/InsertImageCommand/InsertImageCommand.cpp
        src/Document/Command/InsertImageCommand/InsertImageCommand.h
        src/Document/Command/ResizeImageCommand/ResizeImageCommand.cpp
        src/Document/Command/ResizeImageCommand/ResizeImageCommand.h
        src/Document/Command/MacroCommand/MacroCommand.cpp
        src/Document/Command/MacroCommand/MacroCommand.h
)

set(TEST_SOURCE_FILES
        test/test.cpp
        src/Document/Document/Document.cpp
        src/Document/Command/AbstractCommand/AbstractCommand.cpp
        src/Document/History/History.cpp
        src/Document/Command/InsertParagraphCommand/InsertParagraphCommand.cpp
        src/Document/Command/InsertImageCommand/InsertImageCommand.cpp
        src/Document/Command/ResizeImageCommand/ResizeImageCommand.cpp
        src/Document/Command/SetTitleCommand/SetTitleCommand.cpp
        src/Document/Command/ReplaceTextCommand/ReplaceTextCommand.cpp
        src/Document/Command/DeleteItemCommand/DeleteItemCommand.cpp
        src/Document/Command/SaveCommand/SaveCommand.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_executable(${PROJECT_NAME}_test ${TEST_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}_test gtest_main gmock gtest)
enable_testing()
add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test)