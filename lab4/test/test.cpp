#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/Shape/Rectangle.h"
#include "../src/Shape/Ellipse.h"
#include "../src/Shape/Triangle.h"
#include "../src/Shape/RegularPolygon.h"
#include "../src/Shape/Factory/ShapeFactory.h"
#include "../src/Designer/PictureDraft.h"

using ::testing::_;
using ::testing::Return;

class MockCanvas : public gfx::ICanvas {
public:
    MOCK_METHOD(void, SetColor, (uint32_t color), (override));
    MOCK_METHOD(void, DrawLine, (double fromX, double fromY, double toX, double toY), (override));
    MOCK_METHOD(void, DrawEllipse, (double cx, double cy, double rx, double ry), (override));
};

class MockShape : public Shape {
public:
    MOCK_METHOD(void, Draw, (gfx::ICanvas &canvas), (const, override));

    explicit MockShape(Color color) : Shape(color) {}
};

void AssertEqualPoint(Point expectedPoint, Point actualPoint)
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
    AssertEqualPoint(leftTop, rectangle.GetLeftTop());
    EXPECT_EQ(width, rectangle.GetWidth());
    EXPECT_EQ(height, rectangle.GetHeight());
}

TEST(rectangle, draw_success)
{
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

TEST (ellipse, create_success)
{
    Color color = Color::BLACK;
    Point center(50, 50);
    double horizontalRadius = 30;
    double verticalRadius = 20;

    Ellipse ellipse(color, center, horizontalRadius, verticalRadius);

    EXPECT_EQ(color, ellipse.GetColor());
    AssertEqualPoint(center, ellipse.GetCenter());
    EXPECT_EQ(horizontalRadius, ellipse.GetHorizontalRadius());
    EXPECT_EQ(verticalRadius, ellipse.GetVerticalRadius());
}

TEST(ellipse, draw_success)
{
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

TEST (triangle, create_success)
{
    Color color = Color::BLACK;
    Point point1(10, 20);
    Point point2(40, 20);
    Point point3(25, 50);

    Triangle triangle(color, point1, point2, point3);

    EXPECT_EQ(color, triangle.GetColor());
    AssertEqualPoint(point1, triangle.GetPoint1());
    AssertEqualPoint(point2, triangle.GetPoint2());
    AssertEqualPoint(point3, triangle.GetPoint3());
}

TEST(triangle, draw_success)
{
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

TEST (regular_polygon, create_success)
{
    Color color = Color::BLACK;
    Point center(50, 50);
    int pointsCount = 5;
    double radius = 30.0;

    RegularPolygon polygon(color, center, pointsCount, radius);

    EXPECT_EQ(color, polygon.GetColor());
    AssertEqualPoint(center, polygon.GetCenter());
    EXPECT_EQ(pointsCount, polygon.GetPointsCount());
    EXPECT_EQ(radius, polygon.GetRadius());
}

TEST(regular_polygon, draw_success)
{
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

TEST(shape_factory, create_triangle_success)
{
    std::string description = "triangle black 10 20 40 20 25 50";

    ShapeFactory shapeFactory;
    auto shape = shapeFactory.CreateShape(description);

    EXPECT_NE(shape, nullptr);
    EXPECT_EQ(typeid(*shape), typeid(Triangle));

    Triangle* triangle = dynamic_cast<Triangle*>(shape.get());
    ASSERT_NE(triangle, nullptr);

    EXPECT_EQ(triangle->GetColor(), Color::BLACK);
    AssertEqualPoint(triangle->GetPoint1(), Point(10, 20));
    AssertEqualPoint(triangle->GetPoint2(), Point(40, 20));
    AssertEqualPoint(triangle->GetPoint3(), Point(25, 50));
}

TEST(shape_factory, create_ellipse_success)
{
    std::string description = "ellipse red 50 50 30 20";

    ShapeFactory shapeFactory;
    auto shape = shapeFactory.CreateShape(description);

    EXPECT_NE(shape, nullptr);
    EXPECT_EQ(typeid(*shape), typeid(Ellipse));

    Ellipse* ellipse = dynamic_cast<Ellipse*>(shape.get());
    ASSERT_NE(ellipse, nullptr);

    EXPECT_EQ(ellipse->GetColor(), Color::RED);
    AssertEqualPoint(ellipse->GetCenter(), Point(50, 50));
    EXPECT_EQ(ellipse->GetHorizontalRadius(), 30);
    EXPECT_EQ(ellipse->GetVerticalRadius(), 20);
}

TEST(shape_factory, create_rectangle_success)
{
    std::string description = "rectangle green 10 20 30 50";

    ShapeFactory shapeFactory;
    auto shape = shapeFactory.CreateShape(description);

    EXPECT_NE(shape, nullptr);
    EXPECT_EQ(typeid(*shape), typeid(Rectangle));

    Rectangle* rectangle = dynamic_cast<Rectangle*>(shape.get());
    ASSERT_NE(rectangle, nullptr);

    EXPECT_EQ(rectangle->GetColor(), Color::GREEN);
    AssertEqualPoint(rectangle->GetLeftTop(), Point(10, 20));
    EXPECT_EQ(rectangle->GetWidth(), 30);
    EXPECT_EQ(rectangle->GetHeight(), 50);
}

TEST(shape_factory, create_regular_polygon_success)
{
    std::string description = "regularPolygon blue 50 50 5 30";

    ShapeFactory shapeFactory;
    auto shape = shapeFactory.CreateShape(description);

    EXPECT_NE(shape, nullptr);
    EXPECT_EQ(typeid(*shape), typeid(RegularPolygon));

    RegularPolygon* polygon = dynamic_cast<RegularPolygon*>(shape.get());
    ASSERT_NE(polygon, nullptr);

    EXPECT_EQ(polygon->GetColor(), Color::BLUE);
    AssertEqualPoint(polygon->GetCenter(), Point(50, 50));
    EXPECT_EQ(polygon->GetPointsCount(), 5);
    EXPECT_EQ(polygon->GetRadius(), 30);
}

TEST(shape_factory, create_shape_unknown_type_error) {
    std::string description = "unknownShape black";

    ShapeFactory shapeFactory;

    EXPECT_THROW(shapeFactory.CreateShape(description), std::invalid_argument);
}

TEST(picture_draft, add_shape_success) {
    PictureDraft draft;

    auto triangle = std::make_unique<MockShape>(Color::BLACK);
    auto ellipse = std::make_unique<MockShape>(Color::BLACK);
    auto rectangle = std::make_unique<MockShape>(Color::BLACK);

    draft.AddShape(std::move(triangle));
    draft.AddShape(std::move(ellipse));
    draft.AddShape(std::move(rectangle));

    EXPECT_EQ(std::distance(draft.begin(), draft.end()), 3);
}

TEST(picture_draft, iterate_shapes_success) {
    PictureDraft draft;

    auto triangle = std::make_unique<MockShape>(Color::BLACK);
    auto ellipse = std::make_unique<MockShape>(Color::BLACK);

    draft.AddShape(std::move(triangle));
    draft.AddShape(std::move(ellipse));

    int count = 0;
    for (const auto& shape : draft) {
        EXPECT_NE(shape, nullptr);
        count++;
    }

    EXPECT_EQ(count, 2);

    count = 0;
    for (const auto& shape : draft) {
        EXPECT_NE(shape, nullptr);
        count++;
    }

    EXPECT_EQ(count, 2);
}

GTEST_API_ int main(int argc, char **argv) {
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}