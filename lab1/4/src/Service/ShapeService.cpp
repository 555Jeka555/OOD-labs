#include "ShapeService.h"

void
ShapeService::AddShape(const std::string& id, uint32_t color, const std::string& type, const std::vector<double>& parameters, const std::string& text)
{
    std::string rectangleString = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::RECTANGLE);
    std::string circleString = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::CIRCLE);
    std::string triangleString = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::TRIANGLE);
    std::string lineString = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::LINE);
    std::string textString = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::TEXT);

    if (type == rectangleString)
    {
        double leftTopX = parameters[0];
        double leftTopY = parameters[1];
        double width = parameters[2];
        double height = parameters[3];

        auto rectangleDrawingStrategy = std::make_unique<shapes::RectangleDrawingStrategy>(leftTopX, leftTopY, width, height);

        m_shapes.emplace(id, std::make_unique<shapes::Shape>(id, color, std::move(rectangleDrawingStrategy)));
    }
    else if (type == circleString)
    {
        double centerX = parameters[0];
        double centerY = parameters[1];
        double radius = parameters[2];

        auto circleDrawingStrategy = std::make_unique<shapes::CircleDrawingStrategy>(centerX, centerY, radius);

        m_shapes.emplace(id, std::make_unique<shapes::Shape>(id, color, std::move(circleDrawingStrategy)));
    }
    else if (type == triangleString)
    {
        double x1 = parameters[0];
        double y1 = parameters[1];
        double x2 = parameters[2];
        double y2 = parameters[3];
        double x3 = parameters[4];
        double y3 = parameters[5];

        auto triangleDrawingStrategy = std::make_unique<shapes::TriangleDrawingStrategy>(x1, y1, x2, y2, x3, y3);

        m_shapes.emplace(id, std::make_unique<shapes::Shape>(id, color, std::move(triangleDrawingStrategy)));
    }
    else if (type == lineString)
    {
        double x1 = parameters[0];
        double y1 = parameters[1];
        double x2 = parameters[2];
        double y2 = parameters[3];

        auto triangleDrawingStrategy = std::make_unique<shapes::LineDrawingStrategy>(x1, y1, x2, y2);

        m_shapes.emplace(id, std::make_unique<shapes::Shape>(id, color, std::move(triangleDrawingStrategy)));
    }
    else if (type == textString)
    {
        double leftTopX = parameters[0];
        double leftTopY = parameters[1];
        double size = parameters[2];

        auto triangleDrawingStrategy = std::make_unique<shapes::TextDrawingStrategy>(leftTopX, leftTopY, size, text);

        m_shapes.emplace(id, std::make_unique<shapes::Shape>(id, color, std::move(triangleDrawingStrategy)));
    }

    m_shapeIds.push_back(id);
}

void ShapeService::MoveShape(const std::string &id, double dx, double dy)
{
    auto& shape = m_shapes.at(id);
    shape->Move(dx, dy);
}

void ShapeService::DeleteShape(const std::string &id)
{
    m_shapes.erase(id);
    std::erase(m_shapeIds, id);
}

void ShapeService::List()
{
    int count = 1;
    for (const auto& id : m_shapeIds) {
        auto& shape = m_shapes.at(id);

        std::cout << count << " ";
        shape->Display();

        count++;
    }
}

void ShapeService::ChangeColor(const std::string &id, uint32_t color)
{
    auto& shape = m_shapes.at(id);
    shape->SetColor(color);
}

void ShapeService::MovePicture(double dx, double dy)
{
    for (const auto& pair : m_shapes)
    {
        pair.second->Move(dx, dy);
    }
}
