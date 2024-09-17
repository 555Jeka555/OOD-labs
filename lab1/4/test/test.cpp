#include <gtest/gtest.h>
#include "../src/Service/ShapeService.h"

TEST (test_service_shape, add_rectangle_success)
{
    std::string expectedStr = "rectangle rec #0f0f0f 10.2 20 2.5 5\n";

    std::string id = "rec";
    uint32_t color = 0x0F0F0F;
    double leftTopX = 10.2;
    double leftTopY = 20;
    double width = 2.5;
    double height = 5;
    std::string type = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::RECTANGLE);
    std::vector<double> parameters = {
            leftTopX,
            leftTopY,
            width,
            height
    };

    ShapeService shapeService;
    shapeService.AddShape(id, color, type, parameters, "");

    std::map<std::string, std::unique_ptr<shapes::Shape>> shapes = shapeService.GetShapes();
    auto& shape = shapes.at(id);

    std::stringstream buffer;
    std::cout.rdbuf(buffer.rdbuf());
    shape->Display();

    ASSERT_EQ(buffer.str(), expectedStr);
}

TEST (test_service_shape, move_rectangle_success)
{
    std::string expectedStr = "rectangle rec #0f0f0f 12 19 2.5 5\n";

    std::string id = "rec";
    uint32_t color = 0x0F0F0F;
    double leftTopX = 10;
    double leftTopY = 20;
    double width = 2.5;
    double height = 5;
    std::string type = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::RECTANGLE);
    std::vector<double> parameters = {
            leftTopX,
            leftTopY,
            width,
            height
    };
    double dx = 2;
    double dy = -1;

    ShapeService shapeService;
    shapeService.AddShape(id, color, type, parameters, "");
    shapeService.MoveShape(id, dx, dy);

    std::map<std::string, std::unique_ptr<shapes::Shape>> shapes = shapeService.GetShapes();
    auto& shape = shapes.at(id);

    std::stringstream buffer;
    std::cout.rdbuf(buffer.rdbuf());
    shape->Display();

    ASSERT_EQ(buffer.str(), expectedStr);
}

TEST (test_service_shape, add_circle_success)
{
    std::string expectedStr = "circle cir #0f0f0f 5 20.5 10\n";

    std::string id = "cir";
    uint32_t color = 0x0F0F0F;
    double centerX = 5;
    double centerY = 20.5;
    double radius = 10;
    std::string type = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::CIRCLE);
    std::vector<double> parameters = {
            centerX,
            centerY,
            radius
    };

    ShapeService shapeService;
    shapeService.AddShape(id, color, type, parameters, "");

    std::map<std::string, std::unique_ptr<shapes::Shape>> shapes = shapeService.GetShapes();
    auto& shape = shapes.at(id);

    std::stringstream buffer;
    std::cout.rdbuf(buffer.rdbuf());
    shape->Display();

    ASSERT_EQ(buffer.str(), expectedStr);
}

TEST (test_service_shape, move_circle_success)
{
    std::string expectedStr = "circle cir #0f0f0f 7 19.5 10\n";

    std::string id = "cir";
    uint32_t color = 0x0F0F0F;
    double centerX = 5;
    double centerY = 20.5;
    double radius = 10;
    std::string type = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::CIRCLE);
    std::vector<double> parameters = {
            centerX,
            centerY,
            radius
    };
    double dx = 2;
    double dy = -1;

    ShapeService shapeService;
    shapeService.AddShape(id, color, type, parameters, "");
    shapeService.MoveShape(id, dx, dy);

    std::map<std::string, std::unique_ptr<shapes::Shape>> shapes = shapeService.GetShapes();
    auto& shape = shapes.at(id);

    std::stringstream buffer;
    std::cout.rdbuf(buffer.rdbuf());
    shape->Display();

    ASSERT_EQ(buffer.str(), expectedStr);
}

TEST (test_service_shape, add_triangle_success)
{
    std::string expectedStr = "triangle tri #0f0f0f 10 20 10 50 40 35\n";

    std::string id = "tri";
    uint32_t color = 0x0F0F0F;
    double x1 = 10;
    double y1 = 20;
    double x2 = 10;
    double y2 = 50;
    double x3 = 40;
    double y3 = 35;
    std::string type = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::TRIANGLE);
    std::vector<double> parameters = {
            x1,
            y1,
            x2,
            y2,
            x3,
            y3
    };

    ShapeService shapeService;
    shapeService.AddShape(id, color, type, parameters, "");

    std::map<std::string, std::unique_ptr<shapes::Shape>> shapes = shapeService.GetShapes();
    auto& shape = shapes.at(id);

    std::stringstream buffer;
    std::cout.rdbuf(buffer.rdbuf());
    shape->Display();

    ASSERT_EQ(buffer.str(), expectedStr);
}

TEST (test_service_shape, move_triangle_success)
{
    std::string expectedStr = "triangle tri #0f0f0f 9 22 9 52 39 37\n";

    std::string id = "tri";
    uint32_t color = 0x0F0F0F;
    double x1 = 10;
    double y1 = 20;
    double x2 = 10;
    double y2 = 50;
    double x3 = 40;
    double y3 = 35;
    std::string type = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::TRIANGLE);
    std::vector<double> parameters = {
            x1,
            y1,
            x2,
            y2,
            x3,
            y3
    };
    double dx = -1;
    double dy = 2;

    ShapeService shapeService;
    shapeService.AddShape(id, color, type, parameters, "");
    shapeService.MoveShape(id, dx, dy);

    std::map<std::string, std::unique_ptr<shapes::Shape>> shapes = shapeService.GetShapes();
    auto& shape = shapes.at(id);

    std::stringstream buffer;
    std::cout.rdbuf(buffer.rdbuf());
    shape->Display();

    ASSERT_EQ(buffer.str(), expectedStr);
}

TEST (test_service_shape, add_line_success)
{
    std::string expectedStr = "line li #0f0f0f 10 20 10 50\n";

    std::string id = "li";
    uint32_t color = 0x0F0F0F;
    double x1 = 10;
    double y1 = 20;
    double x2 = 10;
    double y2 = 50;
    std::string type = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::LINE);
    std::vector<double> parameters = {
            x1,
            y1,
            x2,
            y2
    };

    ShapeService shapeService;
    shapeService.AddShape(id, color, type, parameters, "");

    std::map<std::string, std::unique_ptr<shapes::Shape>> shapes = shapeService.GetShapes();
    auto& shape = shapes.at(id);

    std::stringstream buffer;
    std::cout.rdbuf(buffer.rdbuf());
    shape->Display();

    ASSERT_EQ(buffer.str(), expectedStr);
}

TEST (test_service_shape, move_line_success)
{
    std::string expectedStr = "line li #0f0f0f 9 22 9 52\n";

    std::string id = "li";
    uint32_t color = 0x0F0F0F;
    double x1 = 10;
    double y1 = 20;
    double x2 = 10;
    double y2 = 50;
    std::string type = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::LINE);
    std::vector<double> parameters = {
            x1,
            y1,
            x2,
            y2
    };
    double dx = -1;
    double dy = 2;

    ShapeService shapeService;
    shapeService.AddShape(id, color, type, parameters, "");
    shapeService.MoveShape(id, dx, dy);

    std::map<std::string, std::unique_ptr<shapes::Shape>> shapes = shapeService.GetShapes();
    auto& shape = shapes.at(id);

    std::stringstream buffer;
    std::cout.rdbuf(buffer.rdbuf());
    shape->Display();

    ASSERT_EQ(buffer.str(), expectedStr);
}

TEST (test_service_shape, delete_shape_success)
{
    std::string id = "rec";
    uint32_t color = 0x0F0F0F;
    double leftTopX = 10;
    double leftTopY = 20;
    double width = 2.5;
    double height = 5;
    std::string type = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::RECTANGLE);
    std::vector<double> parameters = {
            leftTopX,
            leftTopY,
            width,
            height
    };

    ShapeService shapeService;
    shapeService.AddShape(id, color, type, parameters, "");
    shapeService.DeleteShape(id);

    std::map<std::string, std::unique_ptr<shapes::Shape>> shapes = shapeService.GetShapes();

    EXPECT_TRUE(shapes.empty());
}

TEST (test_service_shape, change_color_shape_success)
{
    std::string expectedStr = "rectangle rec #ffffff 10 20 2.5 5\n";

    std::string id = "rec";
    uint32_t color = 0x0F0F0F;
    uint32_t newColor = 0xFFFFFF;
    double leftTopX = 10;
    double leftTopY = 20;
    double width = 2.5;
    double height = 5;
    std::string type = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::RECTANGLE);
    std::vector<double> parameters = {
            leftTopX,
            leftTopY,
            width,
            height
    };

    ShapeService shapeService;
    shapeService.AddShape(id, color, type, parameters, "");
    shapeService.ChangeColor(id, newColor);

    std::map<std::string, std::unique_ptr<shapes::Shape>> shapes = shapeService.GetShapes();
    auto& rectangle = shapes.at(id);

    std::stringstream buffer;
    std::cout.rdbuf(buffer.rdbuf());
    rectangle->Display();

    ASSERT_EQ(buffer.str(), expectedStr);
}

GTEST_API_ int main(int argc, char **argv) {
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}