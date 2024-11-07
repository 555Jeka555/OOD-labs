#include <gtest/gtest.h>
#include <memory>
#include "../src/Shape/GroupShape.h"
#include "../src/Shape/Rectangle.h"
#include "../src/Shape/Triangle.h"

void AssertFrame(RectD actualFrame, RectD expectedFrame)
{
    EXPECT_EQ(actualFrame.top, expectedFrame.top);
    EXPECT_EQ(actualFrame.width, expectedFrame.width);
    EXPECT_EQ(actualFrame.height, expectedFrame.height);
    EXPECT_EQ(actualFrame.left, expectedFrame.left);
}

class GroupShapeTest : public ::testing::Test {
protected:
    void SetUp() override {
        groupShape = std::make_shared<GroupShape>();
    }

    std::shared_ptr<GroupShape> groupShape;
};

TEST_F(GroupShapeTest, AddShape) {
    auto rect = RectD{0, 0, 100, 100};
    auto rectangle = std::make_shared<Rectangle>(
            rect,
            std::make_unique<Style>(0xFF0000FF),
            std::make_unique<Style>(0x00FF00FF)
    );

    groupShape->InsertShape(rectangle);
    size_t actualCount = groupShape->GetShapesCount();
    EXPECT_EQ(actualCount, 1);
}

TEST_F(GroupShapeTest, RemoveShape) {
    auto rectangle = std::make_shared<Rectangle>(
            RectD{0, 0, 100, 100},
            std::make_unique<Style>(0xFF0000FF),
            std::make_unique<Style>(0x00FF00FF)
    );

    groupShape->InsertShape(rectangle, 0);
    EXPECT_EQ(groupShape->GetShapesCount(), 1);

    groupShape->RemoveShapeAtIndex(0);
    EXPECT_EQ(groupShape->GetShapesCount(), 0);
}

TEST_F(GroupShapeTest, GetFrame) {
    auto rectangle1 = std::make_shared<Rectangle>(
            RectD{100, 100, 200, 200},
            std::make_unique<Style>(0xFF0000FF),
            std::make_unique<Style>(0x00FF00FF)
    );

    auto rectangle2 = std::make_shared<Rectangle>(
            RectD{150, 150, 100, 100},
            std::make_unique<Style>(0x00FF00FF),
            std::make_unique<Style>(0x0000FFFF)
    );

    groupShape->InsertShape(rectangle1);
    groupShape->InsertShape(rectangle2);

    RectD expectedFrame = {100, 100, 200, 200};
    auto actualFrame = groupShape->GetFrame();
    AssertFrame(actualFrame, expectedFrame);
}

TEST_F(GroupShapeTest, GetShapeAtIndex) {
    auto triangle = std::make_shared<Triangle>(
            RectD{200, 200, 100, 100},
            std::make_unique<Style>(0x0000FFFF),
            std::make_unique<Style>(0xFFFF00FF)
    );

    groupShape->InsertShape(triangle, 0);

    auto retrievedShape = groupShape->GetShapeAtIndex(0);

    EXPECT_NE(retrievedShape, nullptr);
}

TEST_F(GroupShapeTest, GetShapesCountEmpty) {
    EXPECT_EQ(groupShape->GetShapesCount(), 0);
}

GTEST_API_ int main(int argc, char **argv) {
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}