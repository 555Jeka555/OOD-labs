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
    auto& rectangle = shapes.at(id);

    std::stringstream buffer;
    std::cout.rdbuf(buffer.rdbuf());
    rectangle->Display();

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
    auto& rectangle = shapes.at(id);

    std::stringstream buffer;
    std::cout.rdbuf(buffer.rdbuf());
    rectangle->Display();

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

GTEST_API_ int main(int argc, char **argv) {
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}