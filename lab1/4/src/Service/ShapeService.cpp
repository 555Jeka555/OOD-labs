#include "ShapeService.h"

void
ShapeService::AddShape(const std::string& id, uint32_t color, const std::string& type, const std::vector<double>& parameters, const std::string& text)
{
    std::string rectangleString = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::RECTANGLE);

    if (type == rectangleString)
    {
        double leftTopX = parameters[0];
        double leftTopY = parameters[1];
        double width = parameters[2];
        double height = parameters[3];

        auto rectangleDrawingStrategy = std::make_unique<shapes::RectangleDrawingStrategy>(leftTopX, leftTopY, width, height);

        m_shapes.emplace(id, std::make_unique<shapes::Shape>(id, color, std::move(rectangleDrawingStrategy)));
    }
}

void ShapeService::MoveShape(const std::string &id, double dx, double dy)
{
    auto& shape = m_shapes.at(id);
    shape->Move(dx, dy);
}
