#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <iostream>
#include "../src/Model/Shape.h"
#include "../src/Model/PictureDraft.h"
#include "../src/App/Model/ShapeSelection.h"
#include "../src/App/History/ICommandStorage.h"
#include "../src/App/Command/DeleteShapeCommand.h"
#include "../src/App/Command/ChangeRectShapeCommand.h"
#include "../src/App/Command/InsertShapeCommand.h"
#include "../src/App/Command/GroupCommand.h"
#include "../src/App/UseCase/DeleteShapeUseCase.h"
#include "../src/App/UseCase/InsertShapeUseCase.h"
#include "../src/App/UseCase/MoveShapeUseCase.h"
#include "../src/App/UseCase/ResizeShapeUseCase.h"
#include "../src/Canvas/ICanvas.h"
#include "../src/View/Strategy/EllipseViewStrategy.h"
#include "../src/View/Strategy/RectangleViewStrategy.h"
#include "../src/View/Strategy/TriangleViewStrategy.h"
#include "../src/View/MenuView.h"
#include "../src/View/SelectionFrameView.h"
#include "../src/View/ShapeView.h"
#include "../src/View/PictureDraftView.h"
#include "../src/Presenter/PictureDraftViewPresenter.h"
#include "../src/Presenter/MenuViewPresenter.h"

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

class MockShapeSelection : public ::testing::NiceMock<IShapeSelection>
{
public:
    MOCK_METHOD(std::vector<std::shared_ptr<ShapeAppModel>>, GetSelectedShapes, (), (const, override));
    MOCK_METHOD(void, SetSelectedShapes, (const std::vector<std::shared_ptr<ShapeAppModel>>& shapes), (override));
    MOCK_METHOD(void, DoOnSelectionChanged, (const std::function<void(const std::vector<std::shared_ptr<ShapeAppModel>>&)>& handler), (override));
};

class MockCommandStorage : public ICommandStorage
{
public:
    MOCK_METHOD(void, AddAndExecuteCommand, (ICommandPtr&& command), (override));
};

class MockHistory : public IHistory
{
public:
    MOCK_METHOD(bool, CanUndo, (), (const, override));
    MOCK_METHOD(bool, CanRedo, (), (const, override));
    MOCK_METHOD(void, Undo, (), (override));
    MOCK_METHOD(void, Redo, (), (override));
};

class MockCommand : public ICommand
{
public:
    explicit MockCommand(int & count) : m_count(count) {}

    void Execute() override
    {
        ++m_count;
    }

    void Unexecute() override
    {
        --m_count;
    }

private:
    int & m_count;
};

class MockCanvas : public ::testing::NiceMock<ICanvas> {
public:
    MOCK_METHOD(void, DrawLine, (const Point& from, const Point& to), (override));
    MOCK_METHOD(void, DrawClosedPolyLine, (const std::vector<Point>& points), (override));
    MOCK_METHOD(void, DrawEllipse, (RectD rect), (override));
    MOCK_METHOD(void, FillEllipse, (RectD rect), (override));
    MOCK_METHOD(void, FillPolygon, (const std::vector<Point>& points), (override));
    MOCK_METHOD(void, SetFillColor, (RGBAColor color), (override));
    MOCK_METHOD(void, SetLineColor, (RGBAColor color), (override));
    MOCK_METHOD(void, SetLineThickness, (unsigned int thickness), (override));
    MOCK_METHOD(void, DrawText, (const std::string& text, const Point& position), (override));
    MOCK_METHOD(void, SaveToFile, (const std::string &outputFileName), (override));
};

class MockShapeViewStrategy : public IShapeViewStrategy
{
public:
    void Draw(
            ICanvas &canvas,
            RectD frame,
            RGBAColor fillColor,
            RGBAColor lineColor,
            unsigned lineThickness
    ) override
    {
        std::cout << "Draw" << std::endl;
    }
};

class MockShapeViewStrategySelected : public IShapeViewStrategy
{
public:
    void Draw(
            ICanvas &canvas,
            RectD frame,
            RGBAColor fillColor,
            RGBAColor lineColor,
            unsigned lineThickness
    ) override
    {
    std::cout << "Draw selected" << std::endl;
    }
};

class MockPictureDraftViewPresenter : public IPictureDraftViewPresenter
{
public:
    MOCK_METHOD(void, OnMouseDown, (const Point& point), (override));
    MOCK_METHOD(void, OnDrag, (const Point& offset, const Point& point), (override));
    MOCK_METHOD(void, OnMouseUp, (const Point& point), (override));
    MOCK_METHOD(void, InsertShape, (ShapeType type), (override));
    MOCK_METHOD(void, DeleteShape, (), (override));
    MOCK_METHOD(void, Undo, (), (override));
    MOCK_METHOD(void, Redo, (), (override));
};

class MockUseCaseFactory : public IUseCaseFactory
{
public:
    MOCK_METHOD(std::unique_ptr<IMoveShapeUseCase>, CreateMoveShapeUseCase, (), (override));
    MOCK_METHOD(std::unique_ptr<IResizeShapeUseCase>, CreateResizeShapeUseCase, (), (override));
    MOCK_METHOD(std::unique_ptr<IInsertShapeUseCase>, CreateInsertShapeUseCase, (PictureDraftAppModel& pictureDraftApp), (override));
    MOCK_METHOD(std::unique_ptr<IDeleteShapeUseCase>, CreateDeleteShapeUseCase, (PictureDraftAppModel& pictureDraftApp), (override));
};

class MockShapeViewStrategyFactory : public IShapeViewStrategyFactory {
public:
    MOCK_METHOD(std::shared_ptr<IShapeViewStrategy>, Create, (ShapeType shapeType), (override));
};

class MockResizeShapeUseCase : public IResizeShapeUseCase
{
public:
    void Resize(const Point& offset, DirectionPoint directionPoint) override
    {}

    void Execute() override
    {}
};

class MockMoveShapeUseCase : public IMoveShapeUseCase
{
public:
    virtual void Move(const Point & offset) override
    {}

    virtual void Execute() override
    {}
};

class MockInsertShapeUseCase : public IInsertShapeUseCase
{
public:
    void Execute(size_t index, ShapeType shapeType) override
    {}
};

class MockDeleteShapeUseCase : public IDeleteShapeUseCase
{
public:
    void Execute() override
    {}
};

class ShapeTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(ShapeTest, DefaultConstructor)
{
    Shape shape(ShapeType::RECTANGLE);

    EXPECT_FALSE(shape.GetId().empty());
    EXPECT_EQ(shape.GetType(), ShapeType::RECTANGLE);
    EXPECT_TRUE((shape.GetFrame() == Shape::DEFAULT_FRAME));
}

TEST_F(ShapeTest, CustomFrameConstructor)
{
    RectD customFrame = { 50, 50, 200, 200 };
    Shape shape(ShapeType::ELLIPSE, customFrame);

    EXPECT_EQ(shape.GetFrame(), customFrame);
}

TEST_F(ShapeTest, SetFrame)
{
    Shape shape(ShapeType::ELLIPSE);
    RectD newFrame = { 10, 10, 150, 150 };

    shape.SetFrame(newFrame);
    EXPECT_EQ(shape.GetFrame(), newFrame);
}

TEST_F(ShapeTest, FrameChangedSignal)
{
    Shape shape(ShapeType::RECTANGLE);
    bool frameChangedCalled = false;

    shape.DoOnFrameChanged([&](const RectD&) {
        frameChangedCalled = true;
    });

    RectD newFrame = { 20, 20, 100, 100 };
    shape.SetFrame(newFrame);

    EXPECT_TRUE(frameChangedCalled);
}

TEST_F(ShapeTest, GetLineStyle)
{
    Shape shape(ShapeType::RECTANGLE);

    auto lineStyle = shape.GetLineStyle();
    EXPECT_NE(lineStyle, nullptr);
}

TEST_F(ShapeTest, GetFillStyle)
{
    Shape shape(ShapeType::RECTANGLE);

    auto fillStyle = shape.GetFillStyle();
    EXPECT_NE(fillStyle, nullptr);
}


class PictureDraftTest : public ::testing::Test {
protected:
    void SetUp() override {
        pictureDraft = std::make_shared<PictureDraft>();
    }

    std::shared_ptr<PictureDraft> pictureDraft;
};

TEST_F(PictureDraftTest, InsertShapeAtEnd)
{
    auto shape = std::make_shared<Shape>(ShapeType::RECTANGLE);
    pictureDraft->InsertShape(shape, 0);

    EXPECT_EQ(pictureDraft->GetShapeCount(), 1);
    EXPECT_EQ(pictureDraft->GetShape(0), shape);
}

TEST_F(PictureDraftTest, InsertShapeAtSpecificIndex)
{
    auto shape1 = std::make_shared<Shape>(ShapeType::RECTANGLE);
    auto shape2 = std::make_shared<Shape>(ShapeType::ELLIPSE);

    pictureDraft->InsertShape(shape1, 0);
    pictureDraft->InsertShape(shape2, 0);

    EXPECT_EQ(pictureDraft->GetShapeCount(), 2);
    EXPECT_EQ(pictureDraft->GetShape(0), shape2);
    EXPECT_EQ(pictureDraft->GetShape(1), shape1);
}

TEST_F(PictureDraftTest, InsertShapeOutOfRange)
{
    auto shape = std::make_shared<Shape>(ShapeType::RECTANGLE);

    EXPECT_THROW(pictureDraft->InsertShape(shape, 1), std::out_of_range);
}

TEST_F(PictureDraftTest, DeleteShape)
{
    auto shape = std::make_shared<Shape>(ShapeType::RECTANGLE);
    pictureDraft->InsertShape(shape, 0);

    auto deletedShape = pictureDraft->DeleteShape(0);

    EXPECT_EQ(pictureDraft->GetShapeCount(), 0);
    EXPECT_EQ(deletedShape, shape);
}

TEST_F(PictureDraftTest, DeleteNonExistentShape)
{
    EXPECT_THROW(pictureDraft->DeleteShape(0), std::out_of_range);
}

TEST_F(PictureDraftTest, ShapeAddedSignal)
{
    bool signalCalled = false;
    size_t addedIndex = 0;

    pictureDraft->DoOnShapeAdded([&](size_t index) {
        signalCalled = true;
        addedIndex = index;
    });

    auto shape = std::make_shared<Shape>(ShapeType::RECTANGLE);
    pictureDraft->InsertShape(shape, 0);

    EXPECT_TRUE(signalCalled);
    EXPECT_EQ(addedIndex, 0);
}

TEST_F(PictureDraftTest, ShapeDeletedSignal)
{
    bool signalCalled = false;
    size_t deletedIndex = 0;

    pictureDraft->DoOnShapeDeleted([&](size_t index, const std::shared_ptr<Shape>& shape) {
        signalCalled = true;
        deletedIndex = index;
    });

    auto shape = std::make_shared<Shape>(ShapeType::RECTANGLE);
    pictureDraft->InsertShape(shape, 0);

    pictureDraft->DeleteShape(0);

    EXPECT_TRUE(signalCalled);
    EXPECT_EQ(deletedIndex, 0);
}


class DeleteShapeCommandTest : public ::testing::Test {
protected:
    std::shared_ptr<MockShapeSelection> mockSelection;
    std::shared_ptr<PictureDraft> pictureDraft;
    std::shared_ptr<Shape> shape;

    void SetUp() override {
        mockSelection = std::make_shared<MockShapeSelection>();
        pictureDraft = std::make_shared<PictureDraft>();
        shape = std::make_shared<Shape>(ShapeType::RECTANGLE);
        pictureDraft->InsertShape(shape, 0);
    }
};

TEST_F(DeleteShapeCommandTest, ExecuteRemovesShape) {
    EXPECT_CALL(*mockSelection, GetSelectedShapes())
            .WillOnce(Return(std::vector<std::shared_ptr<ShapeAppModel>>{}));

    DeleteShapeCommand command(shape, pictureDraft, *mockSelection);

    command.Execute();

    EXPECT_EQ(pictureDraft->GetShapeCount(), 0);
}

TEST_F(DeleteShapeCommandTest, UnexecuteRestoresShape) {
    EXPECT_CALL(*mockSelection, GetSelectedShapes())
            .WillOnce(Return(std::vector<std::shared_ptr<ShapeAppModel>>{}));

    DeleteShapeCommand command(shape, pictureDraft, *mockSelection);

    command.Execute();
    EXPECT_EQ(pictureDraft->GetShapeCount(), 0);

    command.Unexecute();

    EXPECT_EQ(pictureDraft->GetShapeCount(), 1);
}

TEST_F(DeleteShapeCommandTest, UnexecuteRestoresSelectedShapes)
{
    auto selectedShape = std::make_shared<ShapeAppModel>(shape);

    EXPECT_CALL(*mockSelection, GetSelectedShapes())
            .WillOnce(Return(std::vector<std::shared_ptr<ShapeAppModel>>{selectedShape}));

    DeleteShapeCommand command(shape, pictureDraft, *mockSelection);

    command.Execute();

    EXPECT_CALL(*mockSelection, SetSelectedShapes(_))
            .Times(1);
    command.Unexecute();
}


class ChangeRectShapeCommandTest : public ::testing::Test {
protected:
    std::shared_ptr<MockShapeSelection> mockSelection;
    std::shared_ptr<ShapeAppModel> shapeAppModel;

    void SetUp() override {
        mockSelection = std::make_shared<MockShapeSelection>();

        auto shape = std::make_shared<Shape>(ShapeType::RECTANGLE);
        RectD originalFrame = { 10, 10, 100, 100 };
        shape->SetFrame(originalFrame);
        shapeAppModel = std::make_shared<ShapeAppModel>(shape);
    }
};

TEST_F(ChangeRectShapeCommandTest, ExecuteChangesFrame) {
    RectD newFrame = { 20, 20, 200, 200 };

    shapeAppModel->GetShape()->SetFrame(newFrame);

    EXPECT_CALL(*mockSelection, SetSelectedShapes(std::vector<std::shared_ptr<ShapeAppModel>>{shapeAppModel})).Times(1);

    ChangeRectShapeCommand command(shapeAppModel, *mockSelection);

    command.Execute();

    EXPECT_EQ(shapeAppModel->GetFrame(), newFrame);
}

TEST_F(ChangeRectShapeCommandTest, UnexecuteRestoresOriginalFrame)
{
    RectD newFrame = { 20, 20, 200, 200 };

    shapeAppModel->GetShape()->SetFrame(newFrame);

    EXPECT_CALL(*mockSelection, SetSelectedShapes(std::vector<std::shared_ptr<ShapeAppModel>>{shapeAppModel})).Times(1);

    ChangeRectShapeCommand command(shapeAppModel, *mockSelection);

    command.Execute();

    EXPECT_EQ(shapeAppModel->GetFrame(), newFrame);
    EXPECT_CALL(*mockSelection, SetSelectedShapes(std::vector<std::shared_ptr<ShapeAppModel>>{shapeAppModel})).Times(1);

    command.Unexecute();

    EXPECT_EQ(shapeAppModel->GetFrame(), newFrame);
}


class InsertShapeCommandTest : public ::testing::Test {
protected:
    std::shared_ptr<MockShapeSelection> mockSelection;
    std::shared_ptr<PictureDraft> pictureDraft;
    std::shared_ptr<Shape> shape;

    void SetUp() override {
        mockSelection = std::make_shared<MockShapeSelection>();
        pictureDraft = std::make_shared<PictureDraft>();
        shape = std::make_shared<Shape>(ShapeType::RECTANGLE);
    }
};

TEST_F(InsertShapeCommandTest, ExecuteInsertsShape)
{
    size_t index = 0;

    EXPECT_CALL(*mockSelection, GetSelectedShapes())
            .WillOnce(Return(std::vector<std::shared_ptr<ShapeAppModel>>{}));

    InsertShapeCommand command(index, shape, pictureDraft, *mockSelection);

    command.Execute();

    EXPECT_EQ(pictureDraft->GetShapeCount(), 1);
    EXPECT_EQ(pictureDraft->GetShape(0), shape);
}

TEST_F(InsertShapeCommandTest, UnexecuteRemovesInsertedShape)
{
    size_t index = 0;

    EXPECT_CALL(*mockSelection, GetSelectedShapes())
            .WillOnce(Return(std::vector<std::shared_ptr<ShapeAppModel>>{})); // Возвращаем пустой вектор выбранных фигур

    InsertShapeCommand command(index, shape, pictureDraft, *mockSelection);

    command.Execute();
    EXPECT_EQ(pictureDraft->GetShapeCount(), 1);

    command.Unexecute();

    EXPECT_EQ(pictureDraft->GetShapeCount(), 0);
}

TEST_F(InsertShapeCommandTest, UnexecuteRestoresSelectedShapes)
{
    size_t index = 0;

    auto selectedShape = std::make_shared<ShapeAppModel>(shape);
    EXPECT_CALL(*mockSelection, GetSelectedShapes())
            .WillOnce(Return(std::vector<std::shared_ptr<ShapeAppModel>>{selectedShape}));

    InsertShapeCommand command(index, shape, pictureDraft, *mockSelection);

    command.Execute();

    EXPECT_CALL(*mockSelection, SetSelectedShapes(_)).Times(1);
    command.Unexecute();
}

class GroupCommandTest : public ::testing::Test
{
public:
    std::shared_ptr<GroupCommand> groupCommand;
    int counter{};

    void SetUp() override
    {
        counter = 0;
        groupCommand = std::make_shared<GroupCommand>();
        std::unique_ptr<MockCommand> mockCommand1 = std::make_unique<MockCommand>(counter);
        std::unique_ptr<MockCommand> mockCommand2 = std::make_unique<MockCommand>(counter);

        groupCommand->AddCommand(std::move(mockCommand1));
        groupCommand->AddCommand(std::move(mockCommand2));
    }
};

TEST_F(GroupCommandTest, ExecuteAndUnexecuteGroupCommand)
{
    groupCommand->Execute();
    EXPECT_EQ(2, counter);

    groupCommand->Unexecute();
    EXPECT_EQ(0, counter);
}

class DeleteShapeUseCaseTest : public ::testing::Test {
protected:
    std::shared_ptr<MockShapeSelection> mockSelection;
    std::shared_ptr<MockCommandStorage> mockCommandStorage;
    std::shared_ptr<PictureDraftAppModel> pictureAppDraftModel;
    std::shared_ptr<Shape> shape;
    std::shared_ptr<ShapeAppModel> shapeAppModel;

    void SetUp() override {
        mockSelection = std::make_shared<MockShapeSelection>();
        mockCommandStorage = std::make_shared<MockCommandStorage>();

        shape = std::make_shared<Shape>(ShapeType::RECTANGLE);
        shapeAppModel = std::make_shared<ShapeAppModel>(shape);

        auto pictureDraft = std::make_shared<PictureDraft>();
        auto mockHistory = std::make_shared<MockHistory>();

        pictureAppDraftModel = std::make_shared<PictureDraftAppModel>(pictureDraft, mockHistory);
        pictureAppDraftModel->GetPictureDraft()->InsertShape(shape, 0);
    }
};

TEST_F(DeleteShapeUseCaseTest, ExecuteDeletesSelectedShapes)
{
    EXPECT_CALL(*mockSelection, GetSelectedShapes())
            .WillOnce(Return(std::vector<std::shared_ptr<ShapeAppModel>>{shapeAppModel}));

    auto mockDomainPictureDraft = pictureAppDraftModel->GetPictureDraft();

    EXPECT_CALL(*mockCommandStorage, AddAndExecuteCommand(_)).Times(1);

    DeleteShapeUseCase deleteUseCase(*pictureAppDraftModel, *mockSelection, *mockCommandStorage);

    deleteUseCase.Execute();
}

class InsertShapeUseCaseTest : public ::testing::Test {
protected:
    std::shared_ptr<MockShapeSelection> mockSelection;
    std::shared_ptr<MockCommandStorage> mockCommandStorage;
    std::shared_ptr<PictureDraftAppModel> pictureAppDraftModel;
    std::shared_ptr<Shape> shape;
    std::shared_ptr<ShapeAppModel> shapeAppModel;

    void SetUp() override {
        mockSelection = std::make_shared<MockShapeSelection>();
        mockCommandStorage = std::make_shared<MockCommandStorage>();

        shape = std::make_shared<Shape>(ShapeType::RECTANGLE);
        shapeAppModel = std::make_shared<ShapeAppModel>(shape);

        auto pictureDraft = std::make_shared<PictureDraft>();
        auto mockHistory = std::make_shared<MockHistory>();

        pictureAppDraftModel = std::make_shared<PictureDraftAppModel>(pictureDraft, mockHistory);
        pictureAppDraftModel->GetPictureDraft()->InsertShape(shape, 0);
    }
};

TEST_F(InsertShapeUseCaseTest, ExecuteInsertsShape) {
    size_t index = 0;

    EXPECT_CALL(*mockCommandStorage, AddAndExecuteCommand(_)).Times(1);

    InsertShapeUseCase insertUseCase(*pictureAppDraftModel, *mockSelection, *mockCommandStorage);

    insertUseCase.Execute(index, ShapeType::RECTANGLE);
}


class MoveShapeUseCaseTest : public ::testing::Test {
protected:
    std::shared_ptr<ShapeSelection> shapeSelection;
    std::shared_ptr<MockCommandStorage> mockCommandStorage;
    std::shared_ptr<PictureDraftAppModel> pictureAppDraftModel;
    std::shared_ptr<Shape> shape;
    std::shared_ptr<ShapeAppModel> shapeAppModel;

    void SetUp() override {
        shapeSelection = std::make_shared<ShapeSelection>();
        mockCommandStorage = std::make_shared<MockCommandStorage>();

        shape = std::make_shared<Shape>(ShapeType::RECTANGLE);
        shapeAppModel = std::make_shared<ShapeAppModel>(shape);

        shapeSelection->SetSelectedShapes({shapeAppModel});

        auto pictureDraft = std::make_shared<PictureDraft>();
        auto mockHistory = std::make_shared<MockHistory>();

        pictureAppDraftModel = std::make_shared<PictureDraftAppModel>(pictureDraft, mockHistory);
        pictureAppDraftModel->GetPictureDraft()->InsertShape(shape, 0);
    }
};

TEST_F(MoveShapeUseCaseTest, MoveUpdatesFrame) {
    Point offset{ 10, 15 };

    RectD originalFrame{ 0, 0, 100, 100 };
    shapeAppModel->SetFrame(originalFrame);

    MoveShapeUseCase moveUseCase(*shapeSelection, *mockCommandStorage);

    moveUseCase.Move(offset);

    RectD expectedFrame{ 10, 15, 100, 100 };
    EXPECT_EQ(shapeAppModel->GetFrame(), expectedFrame);
}

TEST_F(MoveShapeUseCaseTest, ExecuteCreatesCorrectChangeRectCommands) {
    EXPECT_CALL(*mockCommandStorage, AddAndExecuteCommand(_)).Times(1);

    MoveShapeUseCase moveUseCase(*shapeSelection, *mockCommandStorage);

    moveUseCase.Execute();
}


class ResizeShapeUseCaseTest : public ::testing::Test {
protected:
    std::shared_ptr<ShapeSelection> shapeSelection;
    std::shared_ptr<MockCommandStorage> mockCommandStorage;
    std::shared_ptr<Shape> shape;
    std::shared_ptr<ShapeAppModel> shapeAppModel;

    void SetUp() override
    {
        shapeSelection = std::make_shared<ShapeSelection>();
        mockCommandStorage = std::make_shared<MockCommandStorage>();

        shape = std::make_shared<Shape>(ShapeType::RECTANGLE);
        shapeAppModel = std::make_shared<ShapeAppModel>(shape);

        shapeSelection->SetSelectedShapes({shapeAppModel});
    }
};

TEST_F(ResizeShapeUseCaseTest, ResizeUpdatesFrameLeftTop) {
    RectD originalFrame{ 100, 100, 200, 200 };
    shapeAppModel->SetFrame(originalFrame);

    Point offset{ -10, -15 };
    ResizeShapeUseCase resizeUseCase(*shapeSelection, *mockCommandStorage);
    resizeUseCase.Resize(offset, DirectionPoint::LEFT_TOP);

    RectD expectedFrame{ 100, 100, 190, 185 };
    EXPECT_EQ(shapeAppModel->GetFrame(), expectedFrame);
}

TEST_F(ResizeShapeUseCaseTest, ResizeUpdatesFrameRightBottom)
{
    RectD originalFrame{ 100, 100, 200, 200 };
    shapeAppModel->SetFrame(originalFrame);

    Point offset{ -10, -15 };
    ResizeShapeUseCase resizeUseCase(*shapeSelection, *mockCommandStorage);
    resizeUseCase.Resize(offset, DirectionPoint::RIGHT_BOTTOM);

    RectD expectedFrame{ 90, 85, 210, 215 };
    EXPECT_EQ(shapeAppModel->GetFrame(), expectedFrame);
}

TEST_F(ResizeShapeUseCaseTest, ResizeUpdatesFrameRightTop) {
    RectD originalFrame{ 100, 100, 200, 200 };
    shapeAppModel->SetFrame(originalFrame);

    Point offset{ -10, -15 };
    ResizeShapeUseCase resizeUseCase(*shapeSelection, *mockCommandStorage);
    resizeUseCase.Resize(offset, DirectionPoint::RIGHT_TOP);

    RectD expectedFrame{ 90, 100, 210, 185 };
    EXPECT_EQ(shapeAppModel->GetFrame(), expectedFrame);
}

TEST_F(ResizeShapeUseCaseTest, ResizeUpdatesFrameLeftBottom)
{
    RectD originalFrame{ 100, 100, 200, 200 };
    shapeAppModel->SetFrame(originalFrame);

    Point offset{ -10, -15 };
    ResizeShapeUseCase resizeUseCase(*shapeSelection, *mockCommandStorage);
    resizeUseCase.Resize(offset, DirectionPoint::LEFT_BOTTOM);

    RectD expectedFrame{ 100, 85, 190, 215 };
    EXPECT_EQ(shapeAppModel->GetFrame(), expectedFrame);
}

TEST_F(ResizeShapeUseCaseTest, ExecuteCreatesCorrectChangeRectCommands)
{
    EXPECT_CALL(*mockCommandStorage, AddAndExecuteCommand(_)).Times(1);

    ResizeShapeUseCase resizeUseCase(*shapeSelection, *mockCommandStorage);

    resizeUseCase.Execute();
}


class EllipseViewStrategyTest : public ::testing::Test {
protected:
    MockCanvas mockCanvas;
    EllipseViewStrategy ellipseViewStrategy;
};

TEST_F(EllipseViewStrategyTest, DrawCallsCanvasMethods) {
    RectD frame{ 10, 10, 100, 50 };
    RGBAColor fillColor = 0xFFFFFFFF;
    RGBAColor lineColor = 0x000000FF;
    unsigned lineThickness = 2;

    EXPECT_CALL(mockCanvas, SetFillColor(fillColor)).Times(1);
    EXPECT_CALL(mockCanvas, FillEllipse(frame)).Times(1);
    EXPECT_CALL(mockCanvas, SetLineColor(lineColor)).Times(1);
    EXPECT_CALL(mockCanvas, SetLineThickness(lineThickness)).Times(1);
    EXPECT_CALL(mockCanvas, DrawEllipse(frame)).Times(1);

    ellipseViewStrategy.Draw(mockCanvas, frame, fillColor, lineColor, lineThickness);
}


class RectangleViewStrategyTest : public ::testing::Test {
protected:
    MockCanvas mockCanvas;
    RectangleViewStrategy rectangleViewStrategy;
};

TEST_F(RectangleViewStrategyTest, DrawCallsCanvasMethods) {
    RectD frame{ 10, 20, 100, 50 };
    RGBAColor fillColor = 0xFFFFFFFF;
    RGBAColor lineColor = 0x000000FF;
    unsigned lineThickness = 2;

    EXPECT_CALL(mockCanvas, SetLineColor(lineColor)).Times(1);
    EXPECT_CALL(mockCanvas, SetLineThickness(lineThickness)).Times(1);

    Point leftTop = { frame.left, frame.top };
    Point rightBottom = { frame.left + frame.width, frame.top + frame.height };
    Point rightTop = { rightBottom.m_x, frame.top };
    Point leftBottom = { frame.left, rightBottom.m_y };
    std::vector<Point> expectedPoints{ leftTop, rightTop, rightBottom, leftBottom };

    EXPECT_CALL(mockCanvas, FillPolygon(expectedPoints)).Times(1);

    EXPECT_CALL(mockCanvas, DrawLine(_, _)).Times(4);

    rectangleViewStrategy.Draw(mockCanvas, frame, fillColor, lineColor, lineThickness);
}


class TriangleViewStrategyTest : public ::testing::Test {
protected:
    MockCanvas mockCanvas;
    TriangleViewStrategy triangleViewStrategy;
};

TEST_F(TriangleViewStrategyTest, DrawCallsCanvasMethods) {
    RectD frame{ 10, 20, 100, 50 };
    RGBAColor fillColor = 0xFFFFFFFF;
    RGBAColor lineColor = 0x000000FF;
    unsigned lineThickness = 2;

    EXPECT_CALL(mockCanvas, SetFillColor(fillColor)).Times(1);

    std::vector<Point> expectedPoints = {
            {frame.left, frame.top + frame.height},
            {frame.left + frame.width / 2, frame.top},
            {frame.left + frame.width, frame.top + frame.height}
    };

    EXPECT_CALL(mockCanvas, FillPolygon(expectedPoints)).Times(1);

    EXPECT_CALL(mockCanvas, SetLineColor(lineColor)).Times(1);
    EXPECT_CALL(mockCanvas, SetLineThickness(lineThickness)).Times(1);

    EXPECT_CALL(mockCanvas, DrawClosedPolyLine(expectedPoints)).Times(1);

    triangleViewStrategy.Draw(mockCanvas, frame, fillColor, lineColor, lineThickness);
}


class MenuViewTest : public ::testing::Test
{
protected:
    MockCanvas mockCanvas;
    MenuView menuView{800.0, 600.0};
};

TEST_F(MenuViewTest, ShowCallsCanvasMethods)
{
    EXPECT_CALL(mockCanvas, SetFillColor(0x000000FF)).Times(4);

    EXPECT_CALL(mockCanvas, DrawLine(_, _)).Times(16);

    EXPECT_CALL(mockCanvas, DrawText(_, _)).Times(4);

    menuView.Draw(mockCanvas);
}

TEST_F(MenuViewTest, GetCountButtonsReturnsCorrectCount)
{
    EXPECT_EQ(menuView.GetCountButtons(), 4);
}

TEST_F(MenuViewTest, GetWidthReturnsCorrectWidth) {
    EXPECT_EQ(menuView.GetWidth(), 800.0);
}


class SelectionFrameViewTest : public ::testing::Test {
protected:
    MockCanvas mockCanvas;
    std::shared_ptr<ShapeAppModel> shapeAppModel;

    std::shared_ptr<SelectionFrameView> selectionFrameView;

    void SetUp() override {
        RectD frame{ 10.0, 20.0, 100.0, 50.0 };

        auto shape = std::make_shared<Shape>(ShapeType::RECTANGLE, frame);
        shapeAppModel = std::make_shared<ShapeAppModel>(shape);

        selectionFrameView = std::make_shared<SelectionFrameView>(*shapeAppModel);
    }
};

TEST_F(SelectionFrameViewTest, DrawCallsCanvasMethods) {
    EXPECT_CALL(mockCanvas, SetFillColor(0x000000FF)).Times(5);
    EXPECT_CALL(mockCanvas, SetLineThickness(1)).Times(1);

    EXPECT_CALL(mockCanvas, DrawLine(_, _)).Times(4);

    EXPECT_CALL(mockCanvas, FillPolygon(_)).Times(4);

    selectionFrameView->Draw(mockCanvas);
}


class ShapeViewTest : public ::testing::Test {
protected:
    MockCanvas mockCanvas;
    std::shared_ptr<MockShapeViewStrategy> mockShapeViewStrategy = std::make_shared<MockShapeViewStrategy>();
    ShapeView shapeView{"shape1", mockShapeViewStrategy,
                        RectD{10.0, 20.0, 100.0, 50.0}, ShapeType::RECTANGLE,
                        0xFFFFFFFF, 0x000000FF, 2};
};

TEST_F(ShapeViewTest, GetIdReturnsCorrectId) {
    EXPECT_EQ(shapeView.GetId(), "shape1");
}

TEST_F(ShapeViewTest, GetFrameReturnsCorrectFrame) {
    RectD expectedFrame{10.0, 20.0, 100.0, 50.0};
    EXPECT_EQ(shapeView.GetFrame(), expectedFrame);
}

TEST_F(ShapeViewTest, DrawCallsShapeViewStrategyDraw) {
    std::ostringstream buffer;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());

    shapeView.Draw(mockCanvas);

    std::cout.rdbuf(oldCoutBuffer);

    EXPECT_EQ(buffer.str(), "Draw\n");
}


class PictureDraftViewTest : public ::testing::Test {
protected:
    MockCanvas mockCanvas;
    std::shared_ptr<ShapeSelection> shapeSelection;
    std::shared_ptr<PictureDraftView> pictureDraftView;

    void SetUp() override {
        shapeSelection = std::make_shared<ShapeSelection>();
        pictureDraftView = std::make_shared<PictureDraftView>(*shapeSelection, 800, 600);
    }
};

TEST_F(PictureDraftViewTest, GetWidthReturnsCorrectWidth) {
    EXPECT_EQ(pictureDraftView->GetWidth(), 800);
}

TEST_F(PictureDraftViewTest, GetHeightReturnsCorrectHeight) {
    EXPECT_EQ(pictureDraftView->GetHeight(), 600);
}

TEST_F(PictureDraftViewTest, InsertShapeViewAddsShape) {
    auto shapeView = std::make_shared<ShapeView>("shape1", nullptr,
                                                     RectD{10.0, 20.0, 100.0, 50.0},
                                                     ShapeType::RECTANGLE,
                                                     0xFFFFFFFF,
                                                     0x000000FF,
                                                     2);

    pictureDraftView->InsertShapeView(0, std::move(shapeView));

    EXPECT_EQ(pictureDraftView->GetShapeViewCount(), 1);
}

TEST_F(PictureDraftViewTest, DeleteShapeViewRemovesShape) {
    auto shapeView = std::make_shared<ShapeView>("shape1", nullptr,
                                                     RectD{10.0, 20.0, 100.0, 50.0},
                                                     ShapeType::RECTANGLE,
                                                     0xFFFFFFFF,
                                                     0x000000FF,
                                                     2);

    pictureDraftView->InsertShapeView(0, std::move(shapeView));
    EXPECT_EQ(pictureDraftView->GetShapeViewCount(), 1);

    pictureDraftView->DeleteShapeView(0);

    EXPECT_EQ(pictureDraftView->GetShapeViewCount(), 0);
}

TEST_F(PictureDraftViewTest, DrawCallsDrawForAllShapes)
{
    RectD frame{50.0, 60.0, 150.0, 75.0};

    auto shape1 = std::make_shared<ShapeView>("shape1", std::make_shared<MockShapeViewStrategy>(),
                                                  RectD{10.0, 20.0, 100.0, 50.0},
                                                  ShapeType::RECTANGLE,
                                                  0xFFFFFFFF,
                                                  0x000000FF,
                                                  2);

    auto shape2 = std::make_shared<ShapeView>("shape2", std::make_shared<MockShapeViewStrategySelected>(),
                                              frame,
                                                  ShapeType::ELLIPSE,
                                              0xFFFFFFFF,
                                              0x000000FF,
                                                  3);

    pictureDraftView->InsertShapeView(0,std::move(shape1));
    pictureDraftView->InsertShapeView(1,std::move(shape2));

    auto shape = std::make_shared<Shape>(ShapeType::ELLIPSE, frame);
    auto shapeAppModel = std::make_shared<ShapeAppModel>(shape);
    shapeSelection->SetSelectedShapes({shapeAppModel});


    std::ostringstream buffer;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());

    pictureDraftView->Draw(mockCanvas);

    std::cout.rdbuf(oldCoutBuffer);

    EXPECT_EQ(buffer.str(), "Draw\nDraw selected\n");
}


//class PictureDraftViewPresenterTest : public ::testing::Test {
//protected:
//    MockShapeSelection mockShapeSelection;
//    MockPictureDraftAppModel mockPictureDraftApp;
//    MockUseCaseFactory mockUseCaseFactory;
//    MockShapeViewStrategyFactory mockShapeViewStrategyFactory;
//
//    PictureDraftView mockPictureDraftView{mockShapeSelection};
//    PictureDraftViewPresenter presenter{mockShapeSelection,
//                                        mockPictureDraftView,
//                                        mockPictureDraftApp,
//                                        mockUseCaseFactory,
//                                        mockShapeViewStrategyFactory};
//};
//
//TEST_F(PictureDraftViewPresenterTest, OnMouseDownSelectsShape)
//{
//    EXPECT_CALL(mockPictureDraftApp, GetShapeCount()).WillOnce(Return(1));
//    EXPECT_CALL(mockPictureDraftApp, GetShape(0)).WillOnce(Return(std::make_shared<MockShapeAppModel>()));
//
//    Point clickPoint{15.0f, 25.0f};
//    presenter.OnMouseDown(clickPoint);
//}
//
//TEST_F(PictureDraftViewPresenterTest, InsertShapeCallsUseCase)
//{
//    EXPECT_CALL(mockUseCaseFactory,
//                CreateInsertShapeUseCase(mockPictureDraftApp))
//            .WillOnce([](PictureDraftAppModel&) {
//                return std::make_unique<MockInsertShapeUseCase>();
//            });
//
//    EXPECT_CALL(mockPictureDraftApp,
//                GetShapeCount()).WillOnce(Return(0));
//
//    presenter.InsertShape(ShapeType::TRIANGLE);
//}
//
//TEST_F(PictureDraftViewPresenterTest, DeleteShapeCallsUseCase)
//{
//    EXPECT_CALL(mockUseCaseFactory,
//                CreateDeleteShapeUseCase(mockPictureDraftApp))
//            .WillOnce([](PictureDraftAppModel&) {
//                return std::make_unique<MockDeleteShapeUseCase>();
//            });
//
//    presenter.DeleteShape();
//}


//class ShapeViewPresenterTest : public ::testing::Test {
//protected:
//    std::shared_ptr<Shape> shape;
//    std::shared_ptr<ShapeAppModel> shapeAppModel;
//    MockUseCaseFactory mockUseCaseFactory{};
//    std::shared_ptr<ShapeSelection> shapeSelection;
//    std::shared_ptr<ShapeView> mockShapeView = std::make_shared<ShapeView>("shape1", nullptr,
//                                                                           RectD{10.0, 20.0, 100.0, 50.0}, ShapeType::RECTANGLE,
//                                                                           0xFFFFFFFF, 0x000000FF, 2);
//
//    std::shared_ptr<ShapeViewPresenter> presenter;
//
//    void SetUp() override {
//        shapeSelection = std::make_shared<ShapeSelection>();
//        shape = std::make_shared<Shape>(ShapeType::RECTANGLE);
//        shapeAppModel = std::make_shared<ShapeAppModel>(shape);
//        presenter = std::make_shared<ShapeViewPresenter>(shapeAppModel,
//                                                         mockUseCaseFactory,
//                                                         *shapeSelection,
//                                                         mockShapeView);
//    }
//};
//
//TEST_F(ShapeViewPresenterTest, OnMouseDown_SelectsShape)
//{
//    Point clickPoint = {60.0, 40.0};
//    presenter->OnMouseDown(clickPoint);
//
//    auto selectedShapes = shapeSelection->GetSelectedShapes();
//    EXPECT_EQ(selectedShapes.size(), 1);
//    EXPECT_EQ(selectedShapes[0]->GetId(), shapeAppModel->GetId());
//}
//
//TEST_F(ShapeViewPresenterTest, OnDrag_ResizesShape)
//{
//    Point dragOffset = {10.0, 10.0};
//    Point dragPoint = {110.0, 70.0};
//
//    EXPECT_CALL(mockUseCaseFactory, CreateResizeShapeUseCase())
//            .WillOnce(::testing::Return(std::make_unique<MockResizeShapeUseCase>()));
//
//    presenter->OnDrag(dragOffset, dragPoint);
//}
//
//TEST_F(ShapeViewPresenterTest, OnMouseUp_ExecutesMove)
//{
//    Point releasePoint = {60.0, 40.0};
//
//    EXPECT_CALL(mockUseCaseFactory, CreateMoveShapeUseCase())
//            .WillOnce(::testing::Return(std::make_unique<MockMoveShapeUseCase>()));
//
//    presenter->OnMouseUp(releasePoint);
//}
//
//TEST_F(ShapeViewPresenterTest, SetCorectFrameBorders_CorrectsBorders)
//{
//    size_t expectedWidth = 200;
//    size_t expectedHeight = 200;
//
//    presenter->SetCorrectFrameBorders(expectedWidth, expectedHeight);
//
//    EXPECT_EQ(expectedWidth, presenter->GetRespectFrameWidth());
//    EXPECT_EQ(expectedHeight, presenter->GetRespectFrameHeight());
//}


//class MenuViewPresenterTest : public ::testing::Test {
//protected:
//    MenuView mockMenuView = {800, 100};
//    MockPictureDraftViewPresenter mockPictureDraftViewPresenter;
//    std::shared_ptr<MenuViewPresenter> menuViewPresenter;
//
//    void SetUp() override
//    {
//        EXPECT_EQ(800, mockMenuView.GetWidth());
//        EXPECT_EQ(4, mockMenuView.GetCountButtons());
//
//        menuViewPresenter = std::make_shared<MenuViewPresenter>(mockMenuView, mockPictureDraftViewPresenter);
//    }
//};
//
//TEST_F(MenuViewPresenterTest, OnMouseDownInTriangleButtonCallsInsertShape)
//{
//    EXPECT_CALL(mockPictureDraftViewPresenter, InsertShape(ShapeType::TRIANGLE)).Times(1);
//
//    Point clickPoint{100.0f, 10.0f};
//    MockCanvas mockCanvas;
//
//    menuViewPresenter->OnMouseDown(clickPoint, mockCanvas);
//}
//
//TEST_F(MenuViewPresenterTest, OnMouseDownInRectangleButtonCallsInsertShape)
//{
//    EXPECT_CALL(mockPictureDraftViewPresenter, InsertShape(ShapeType::RECTANGLE)).Times(1);
//
//    Point clickPoint{300.0f, 10.0f};
//    MockCanvas mockCanvas;
//
//    menuViewPresenter->OnMouseDown(clickPoint, mockCanvas);
//}
//
//TEST_F(MenuViewPresenterTest, OnMouseDownInEllipseButtonCallsInsertShape)
//{
//    EXPECT_CALL(mockPictureDraftViewPresenter, InsertShape(ShapeType::ELLIPSE)).Times(1);
//
//    Point clickPoint{500.0f, 10.0f};
//    MockCanvas mockCanvas;
//
//    menuViewPresenter->OnMouseDown(clickPoint, mockCanvas);
//}
//
//TEST_F(MenuViewPresenterTest, OnMouseDownInSaveButtonCallsSaveToFile)
//{
//    MockCanvas mockCanvas;
//
//    EXPECT_CALL(mockCanvas, SaveToFile("foto.png")).Times(1);
//
//    Point clickPoint{700.0f, 10.0f};
//    menuViewPresenter->OnMouseDown(clickPoint, mockCanvas);
//}

GTEST_API_ int main(int argc, char **argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}