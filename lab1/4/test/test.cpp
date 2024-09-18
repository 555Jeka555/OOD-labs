#include <gtest/gtest.h>
#include "../src/Picture/Picture.h"

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

    shapes::Picture shapeService;
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

    shapes::Picture shapeService;
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

    shapes::Picture shapeService;
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

    shapes::Picture shapeService;
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

    shapes::Picture shapeService;
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

    shapes::Picture shapeService;
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

    shapes::Picture shapeService;
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

    shapes::Picture shapeService;
    shapeService.AddShape(id, color, type, parameters, "");
    shapeService.MoveShape(id, dx, dy);

    std::map<std::string, std::unique_ptr<shapes::Shape>> shapes = shapeService.GetShapes();
    auto& shape = shapes.at(id);

    std::stringstream buffer;
    std::cout.rdbuf(buffer.rdbuf());
    shape->Display();

    ASSERT_EQ(buffer.str(), expectedStr);
}

TEST (test_service_shape, add_text_success)
{
    std::string expectedStr = "text txt #0f0f0f 100.3 200.2 35 Hello world\n";

    std::string id = "txt";
    uint32_t color = 0x0F0F0F;
    double leftTopX = 100.3;
    double leftTopY = 200.2;
    double size = 35;
    std::string text = "Hello world";
    std::string type = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::TEXT);
    std::vector<double> parameters = {
            leftTopX,
            leftTopY,
            size
    };

    shapes::Picture shapeService;
    shapeService.AddShape(id, color, type, parameters, text);

    std::map<std::string, std::unique_ptr<shapes::Shape>> shapes = shapeService.GetShapes();
    auto& shape = shapes.at(id);

    std::stringstream buffer;
    std::cout.rdbuf(buffer.rdbuf());
    shape->Display();

    ASSERT_EQ(buffer.str(), expectedStr);
}

TEST (test_service_shape, move_text_success)
{
    std::string expectedStr = "text txt #0f0f0f 99.3 202.2 35 Hello world\n";

    std::string id = "txt";
    uint32_t color = 0x0F0F0F;
    double leftTopX = 100.3;
    double leftTopY = 200.2;
    double size = 35;
    std::string text = "Hello world";
    std::string type = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::TEXT);
    std::vector<double> parameters = {
            leftTopX,
            leftTopY,
            size
    };
    double dx = -1;
    double dy = 2;

    shapes::Picture shapeService;
    shapeService.AddShape(id, color, type, parameters, text);
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

    shapes::Picture shapeService;
    shapeService.AddShape(id, color, type, parameters, "");
    shapeService.DeleteShape(id);

    std::map<std::string, std::unique_ptr<shapes::Shape>> shapes = shapeService.GetShapes();
    std::vector<std::string> shapeIds = shapeService.GetShapeIds();

    EXPECT_TRUE(shapes.empty());
    EXPECT_TRUE(shapeIds.empty());
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

    shapes::Picture shapeService;
    shapeService.AddShape(id, color, type, parameters, "");
    shapeService.ChangeColor(id, newColor);

    std::map<std::string, std::unique_ptr<shapes::Shape>> shapes = shapeService.GetShapes();
    auto& shape = shapes.at(id);

    std::stringstream buffer;
    std::cout.rdbuf(buffer.rdbuf());
    shape->Display();

    ASSERT_EQ(buffer.str(), expectedStr);
}

TEST (test_service_shape, list_shape_success)
{
    std::string expectedStr = "1 rectangle rec #0f0f0f 10.2 20 2.5 5\n"
                              "2 circle cir #0f0f0f 5 20.5 10\n"
                              "3 triangle tri #0f0f0f 10 20 10 50 40 35\n"
                              "4 line li #0f0f0f 10 20 10 50\n"
                              "5 text txt #0f0f0f 100.3 200.2 35 Hello world\n";

    shapes::Picture shapeService;
    
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

    shapeService.AddShape(id, color, type, parameters, "");

    id = "cir";
    color = 0x0F0F0F;
    double centerX = 5;
    double centerY = 20.5;
    double radius = 10;
    type = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::CIRCLE);
    parameters = {
            centerX,
            centerY,
            radius
    };

    shapeService.AddShape(id, color, type, parameters, "");

    id = "tri";
    color = 0x0F0F0F;
    double x1 = 10;
    double y1 = 20;
    double x2 = 10;
    double y2 = 50;
    double x3 = 40;
    double y3 = 35;
    type = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::TRIANGLE);
    parameters = {
            x1,
            y1,
            x2,
            y2,
            x3,
            y3
    };

    shapeService.AddShape(id, color, type, parameters, "");

    id = "li";
    color = 0x0F0F0F;
    x1 = 10;
    y1 = 20;
    x2 = 10;
    y2 = 50;
    type = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::LINE);
    parameters = {
            x1,
            y1,
            x2,
            y2
    };

    shapeService.AddShape(id, color, type, parameters, "");

    id = "txt";
    color = 0x0F0F0F;
    leftTopX = 100.3;
    leftTopY = 200.2;
    double size = 35;
    std::string text = "Hello world";
    type = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::TEXT);
    parameters = {
            leftTopX,
            leftTopY,
            size
    };

    shapeService.AddShape(id, color, type, parameters, text);


    std::stringstream buffer;
    std::cout.rdbuf(buffer.rdbuf());
    shapeService.List();
    ASSERT_EQ(buffer.str(), expectedStr);
}

TEST (test_service_shape, move_all_shape_success)
{
    std::string expectedStr = "1 rectangle rec #0f0f0f 11.2 18 2.5 5\n"
                              "2 circle cir #0f0f0f 6 18.5 10\n"
                              "3 triangle tri #0f0f0f 11 18 11 48 41 33\n"
                              "4 line li #0f0f0f 11 18 11 48\n"
                              "5 text txt #0f0f0f 101.3 198.2 35 Hello world\n";

    shapes::Picture shapeService;

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

    shapeService.AddShape(id, color, type, parameters, "");

    id = "cir";
    color = 0x0F0F0F;
    double centerX = 5;
    double centerY = 20.5;
    double radius = 10;
    type = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::CIRCLE);
    parameters = {
            centerX,
            centerY,
            radius
    };

    shapeService.AddShape(id, color, type, parameters, "");

    id = "tri";
    color = 0x0F0F0F;
    double x1 = 10;
    double y1 = 20;
    double x2 = 10;
    double y2 = 50;
    double x3 = 40;
    double y3 = 35;
    type = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::TRIANGLE);
    parameters = {
            x1,
            y1,
            x2,
            y2,
            x3,
            y3
    };

    shapeService.AddShape(id, color, type, parameters, "");

    id = "li";
    color = 0x0F0F0F;
    x1 = 10;
    y1 = 20;
    x2 = 10;
    y2 = 50;
    type = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::LINE);
    parameters = {
            x1,
            y1,
            x2,
            y2
    };

    shapeService.AddShape(id, color, type, parameters, "");

    id = "txt";
    color = 0x0F0F0F;
    leftTopX = 100.3;
    leftTopY = 200.2;
    double size = 35;
    std::string text = "Hello world";
    type = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::TEXT);
    parameters = {
            leftTopX,
            leftTopY,
            size
    };

    shapeService.AddShape(id, color, type, parameters, text);

    double dx = 1;
    double dy = -2;
    shapeService.MovePicture(dx, dy);

    std::stringstream buffer;
    std::cout.rdbuf(buffer.rdbuf());
    shapeService.List();
    ASSERT_EQ(buffer.str(), expectedStr);
}

TEST (test_service_shape, change_rectangle_to_circle_success)
{
    std::string expectedStr = "circle rec #0f0f0f 5 20.5 10\n";

    shapes::Picture shapeService;

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

    shapeService.AddShape(id, color, type, parameters, "");

    double centerX = 5;
    double centerY = 20.5;
    double radius = 10;
    type = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::CIRCLE);
    parameters = {
            centerX,
            centerY,
            radius
    };

    shapeService.ChangeShape(id, type, parameters, "");

    std::map<std::string, std::unique_ptr<shapes::Shape>> shapes = shapeService.GetShapes();
    auto& shape = shapes.at(id);

    std::stringstream buffer;
    std::cout.rdbuf(buffer.rdbuf());
    shape->Display();

    ASSERT_EQ(buffer.str(), expectedStr);
}

TEST (test_service_shape, add_shape_already_exist_id_failed)
{
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

    shapes::Picture shapeService;
    shapeService.AddShape(id, color, type, parameters, "");

    EXPECT_THROW(shapeService.AddShape(id, color, type, parameters, ""), std::invalid_argument);
}

TEST (test_service_shape, move_shape_not_exist_id_failed)
{
    shapes::Picture shapeService;
    EXPECT_THROW(shapeService.MoveShape("rec", 5, 10), std::invalid_argument);
}

TEST (test_service_shape, delete_shape_not_exist_id_failed)
{
    shapes::Picture shapeService;
    EXPECT_THROW(shapeService.DeleteShape("rec"), std::invalid_argument);
}

TEST (test_service_shape, change_color_shape_not_exist_id_failed)
{
    shapes::Picture shapeService;
    EXPECT_THROW(shapeService.ChangeColor("rec", 0x0F0F0F), std::invalid_argument);
}

TEST (test_service_shape, change_shape_not_exist_id_failed)
{
    std::string id = "rec";
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

    shapes::Picture shapeService;
    EXPECT_THROW(shapeService.ChangeShape(id, type, parameters, ""), std::invalid_argument);
}


GTEST_API_ int main(int argc, char **argv) {
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}