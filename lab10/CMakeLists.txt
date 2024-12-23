cmake_minimum_required(VERSION 3.26)
project(lab10)

set(CMAKE_CXX_STANDARD 23)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ./../bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY  ./../lib )

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG master
)
FetchContent_MakeAvailable(sfml)

FetchContent_Declare(
        Boost
        URL https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.tar.xz
        URL_MD5 893b5203b862eb9bbd08553e24ff146a
        DOWNLOAD_EXTRACT_TIMESTAMP ON
)

set(BOOST_INCLUDE_LIBRARIES filesystem regex signals2)
FetchContent_MakeAvailable(Boost)


file(GLOB_RECURSE SOURCE_FILES_2 "${CMAKE_SOURCE_DIR}/src/**/*.h" "${CMAKE_SOURCE_DIR}/src/**/*.cpp" )

list(REMOVE_ITEM SOURCE_FILES_2
        "${CMAKE_SOURCE_DIR}/cmd/main.cpp"
        "${CMAKE_SOURCE_DIR}/test/test.cpp"
)

message(STATUS "Found source files: ${SOURCE_FILES_2}")

set(SOURCE_FILES_2
        src/App/App.h
        src/Model/Shape.h
        src/Common/ShapeType.h
        src/Common/Rect.h
        src/Model/LineStyle.h
        src/Model/FillStyle.h
        src/Common/Color.h
        src/Model/PictureDraft.h
        src/Common/UUID.h
        src/App/Model/ShapeAppModel.h
        src/App/History/IHistory.h
        src/App/History/ICommandStorage.h
        src/App/History/CommandHistory.h
        src/App/History/ICommand.h
        src/Common/Point.h
        src/Presenter/PictureDraftViewPresenter.h
        src/View/PictureDraftView.h
        src/Canvas/ICanvas.h
        src/Canvas/CanvasSFML.cpp
        src/Canvas/CanvasSFML.h
        src/App/Model/ShapeSelection.h
        src/View/SelectionFrameView.h
        src/View/ShapeView.h
        src/View/Strategy/IShapeViewStrategy.h
        src/View/Strategy/RectangleViewStrategy.h
        src/App/UseCase/IUseCaseFactory.h
        src/App/UseCase/UseCaseFactory.h
        src/App/UseCase/DeleteShapeUseCase.h
        src/App/UseCase/IDeleteShapeUseCase.h
        src/App/Command/GroupCommand.h
        src/App/History/AbstractCommand.h
        src/App/Command/InsertShapeCommand.h
        src/App/Command/DeleteShapeCommand.h
        src/App/Command/ChangeRectShapeCommand.h
        src/App/UseCase/InsertShapeUseCase.h
        src/App/UseCase/IInsertShapeUseCase.h
        src/App/UseCase/ResizeShapeUseCase.h
        src/App/UseCase/IResizeShapeUseCase.h
        src/App/UseCase/MoveShapeUseCase.h
        src/App/UseCase/IMoveShapeUseCase.h
        src/Presenter/ShapeViewPresenter.h
        src/View/Strategy/EllipseViewStrategy.h
        src/View/Strategy/TriangleViewStrategy.h
        src/View/IShapeViewStrategyFactory.h
        src/View/ShapeViewStrategyFactory.h
)

set(SOURCE_FILES_1
    cmd/main.cpp
)

set(TEST_SOURCE_FILES_1
    test/test.cpp
)

add_executable(1
        src/View/MenuView.h
        src/Presenter/MenuViewPresenter.h
        src/App/Model/IShapeSelection.h
        src/Presenter/IPictureDraftViewPresenter.h
        src/App/UseCase/IMoveShapeUseCase.h
        src/App/UseCase/IResizeShapeUseCase.h
        src/App/UseCase/IInsertShapeUseCase.h
        src/App/UseCase/IDeleteShapeUseCase.h
)
target_sources(1 PRIVATE ${SOURCE_FILES_1} ${SOURCE_FILES_2})

add_executable(1_test)
target_sources(1_test PRIVATE ${TEST_SOURCE_FILES_1} ${SOURCE_FILES_2})

target_link_libraries(1_test gtest_main gmock gtest sfml-system sfml-window sfml-graphics Boost::filesystem Boost::regex Boost::signals2)
target_link_libraries(1 sfml-system sfml-window sfml-graphics Boost::filesystem Boost::regex Boost::signals2)
enable_testing()
add_test(NAME 1_test COMMAND 1_test)