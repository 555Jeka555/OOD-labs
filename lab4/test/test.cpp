#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/Shape/Rectangle.h"
#include "../src/Shape/Ellipse.h"
#include "../src/Shape/Triangle.h"
#include "../src/Shape/RegularPolygon.h"

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

TEST (triangle, create_success) {
    Color color = Color::BLACK;
    Point point1(10, 20);
    Point point2(40, 20);
    Point point3(25, 50);

    Triangle triangle(color, point1, point2, point3);

    EXPECT_EQ(color, triangle.GetColor());
    assertEqualPoint(point1, triangle.GetPoint1());
    assertEqualPoint(point2, triangle.GetPoint2());
    assertEqualPoint(point3, triangle.GetPoint3());
}

TEST(triangle, draw_success) {
    Color color = Color::BLACK;
    Point point1(10, 20);
    Point point2(40, 20);
    Point point3(25, 50);

    Triangle triangle(color, point1, point2, point3);

    MockCanvas mockCanvas;

    EXPECT_CALL(mockCanvas, SetColor(convertColorToHEX(color)))
            .Times(1);

    EXPECT_CALL(mockCanvas, DrawLine(point1.x, point1.y, point2.x, point2.y))
            .Times(1);
    EXPECT_CALL(mockCanvas, DrawLine(point2.x, point2.y, point3.x, point3.y))
            .Times(1);
    EXPECT_CALL(mockCanvas, DrawLine(point3.x, point3.y, point1.x, point1.y))
            .Times(1);

    triangle.Draw(mockCanvas);
}

TEST (regular_polygon, create_success) {
    Color color = Color::BLACK;
    Point center(50, 50);
    int pointsCount = 5;
    double radius = 30.0;

    RegularPolygon polygon(color, center, pointsCount, radius);

    EXPECT_EQ(color, polygon.GetColor());
    assertEqualPoint(center, polygon.GetCenter());
    EXPECT_EQ(pointsCount, polygon.GetPointsCount());
    EXPECT_EQ(radius, polygon.GetRadius());
}

TEST(regular_polygon, draw_success) {
    Color color = Color::BLACK;
    Point center(50, 50);
    int pointsCount = 5;
    double radius = 30.0;

    RegularPolygon polygon(color, center, pointsCount, radius);

    MockCanvas mockCanvas;

    EXPECT_CALL(mockCanvas, SetColor(convertColorToHEX(color)))
            .Times(1);

    double angleStep = 2 * M_PI / pointsCount;

    double startX = center.x + radius * std::cos(0);
    double startY = center.y + radius * std::sin(0);

    double prevX = startX;
    double prevY = startY;

    for (int i = 1; i <= pointsCount; ++i) {
        double angle = i * angleStep;
        double x = center.x + radius * std::cos(angle);
        double y = center.y + radius * std::sin(angle);

        EXPECT_CALL(mockCanvas, DrawLine(prevX, prevY, x, y)).Times(1);

        prevX = x;
        prevY = y;
    }

    EXPECT_CALL(mockCanvas, DrawLine(prevX, prevY, startX, startY)).Times(1);

    polygon.Draw(mockCanvas);
}

GTEST_API_ int main(int argc, char **argv) {
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}