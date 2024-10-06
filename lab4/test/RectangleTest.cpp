#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/Shape/Rectangle.h"

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