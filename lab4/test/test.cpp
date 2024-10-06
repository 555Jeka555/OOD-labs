#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/Shape/Rectangle.h"
#include "../src/Shape/Ellipse.h"

using ::testing::_;
using ::testing::Return;

class MockCanvas : public gfx::ICanvas {
public:
    MOCK_METHOD(void, SetColor, (uint32_t color), (override));
    MOCK_METHOD(void, DrawLine, (double fromX, double fromY, double toX, double toY), (override));
    MOCK_METHOD(void, DrawEllipse, (double cx, double cy, double rx, double ry), (override));
};

void assertEqualPoint(Point expectedPoint, Point actualPoint)
{
    EXPECT_EQ(expectedPoint.x, actualPoint.x);
    EXPECT_EQ(expectedPoint.y, actualPoint.y);
}

TEST (rectangle, create_success)
{
    Color color = Color::BLACK;
    Point leftTop(10, 20);
    double width = 30;
    double height = 50;

    Rectangle rectangle(color, leftTop, width, height);

    EXPECT_EQ(color, rectangle.GetColor());
    assertEqualPoint(leftTop, rectangle.GetLeftTop());
    EXPECT_EQ(width, rectangle.GetWidth());
    EXPECT_EQ(height, rectangle.GetHeight());
}

TEST(rectangle, draw_success) {
    Color color = Color::BLACK;
    Point leftTop(10, 20);
    double width = 30;
    double height = 50;

    Rectangle rectangle(color, leftTop, width, height);

    MockCanvas mockCanvas;

    EXPECT_CALL(mockCanvas, SetColor(convertColorToHEX(color)))
            .Times(1);

    EXPECT_CALL(mockCanvas, DrawLine(10, 20, 40, 20))
            .Times(1);
    EXPECT_CALL(mockCanvas, DrawLine(40, 20, 40, 70))
            .Times(1);
    EXPECT_CALL(mockCanvas, DrawLine(40, 70, 10, 70))
            .Times(1);
    EXPECT_CALL(mockCanvas, DrawLine(10, 70, 10, 20))
            .Times(1);

    rectangle.Draw(mockCanvas);
}

TEST (ellipse, create_success) {
    Color color = Color::BLACK;
    Point center(50, 50);
    double horizontalRadius = 30;
    double verticalRadius = 20;

    Ellipse ellipse(color, center, horizontalRadius, verticalRadius);

    EXPECT_EQ(color, ellipse.GetColor());
    assertEqualPoint(center, ellipse.GetCenter());
    EXPECT_EQ(horizontalRadius, ellipse.GetHorizontalRadius());
    EXPECT_EQ(verticalRadius, ellipse.GetVerticalRadius());
}

TEST(ellipse, draw_success) {
    Color color = Color::BLACK;
    Point center(50, 50);
    double horizontalRadius = 30;
    double verticalRadius = 20;

    Ellipse ellipse(color, center, horizontalRadius, verticalRadius);

    MockCanvas mockCanvas;

    EXPECT_CALL(mockCanvas, SetColor(convertColorToHEX(color)))
            .Times(1);

    EXPECT_CALL(mockCanvas, DrawEllipse(center.x, center.y, horizontalRadius, verticalRadius))
            .Times(1);

    ellipse.Draw(mockCanvas);
}

GTEST_API_ int main(int argc, char **argv) {
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}