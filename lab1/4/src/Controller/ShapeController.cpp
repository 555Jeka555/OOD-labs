#include "ShapeController.h"

void ShapeController::ReadCommands()
{
    std::string line;


    while (std::getline(m_in, line))
    {
        if (line.empty())
        {
            break;
        }

        std::istringstream iss(line);
        std::string commandName;
        iss >> commandName;

        if (commandName == "AddShape")
        {
            AddShape(iss);
        }
        else if (commandName == "MoveShape")
        {
            MoveShape(iss);
        }
        else if (commandName == "DeleteShape")
        {
            DeleteShape(iss);
        }
        else if (commandName == "List")
        {
            ListShape();
        }
        else if (commandName == "ChangeColor")
        {
            ChangeColor(iss);
        }
        else if (commandName == "MovePicture")
        {
            MovePicture(iss);
        }
        else if (commandName == "ChangeShape")
        {
            ChangeShape(iss);
        }
        else if (commandName == "DrawShape")
        {
            DrawShape(iss);
        }
        else if (commandName == "DrawPicture")
        {
            DrawPicture();
        }
    }
}

void ShapeController::AddShape(std::istringstream &iss)
{
    std::string id;
    uint32_t color;
    std::string type;

    iss >> id;

    std::string colorStr;
    iss >> colorStr;

    if (colorStr[0] == '#') {
        colorStr.erase(0, 1);
        std::stringstream ss;
        ss << std::hex << colorStr;
        ss >> color;
    }

    iss >> type;

    std::string rectangleString = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::RECTANGLE);
    std::string circleString = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::CIRCLE);
    std::string triangleString = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::TRIANGLE);
    std::string lineString = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::LINE);
    std::string textString = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::TEXT);

    if (type == rectangleString)
    {
        std::string leftTopXStr;
        std::string leftTopYStr;
        std::string widthStr;
        std::string heightStr;

        iss >> leftTopXStr >> leftTopYStr >> widthStr >> heightStr;

        double leftTopX = std::stod(leftTopXStr);
        double leftTopY = std::stod(leftTopYStr);
        double width = std::stod(widthStr);
        double height = std::stod(heightStr);

        auto rectangleDrawingStrategy = std::make_unique<shapes::RectangleGeometryTypeStrategy>(leftTopX, leftTopY, width, height);
        std::unique_ptr<shapes::Shape> shape = make_unique<shapes::Shape>(id, color, std::move(rectangleDrawingStrategy));

        m_picture.AddShape(id, std::move(shape));
    }
    else if (type == circleString)
    {
        std::string centerXStr;
        std::string centerYStr;
        std::string radiusStr;

        iss >> centerXStr >> centerYStr >> radiusStr;

        double centerX = std::stod(centerXStr);
        double centerY = std::stod(centerYStr);
        double radius = std::stod(radiusStr);

        auto circleDrawingStrategy = std::make_unique<shapes::CircleGeometryTypeStrategy>(centerX, centerY, radius);
        std::unique_ptr<shapes::Shape> shape = make_unique<shapes::Shape>(id, color, std::move(circleDrawingStrategy));
        
        m_picture.AddShape(id, std::move(shape));
    }
    else if (type == triangleString)
    {
        std::string x1Str;
        std::string y1Str;
        std::string x2Str;
        std::string y2Str;
        std::string x3Str;
        std::string y3Str;

        iss >> x1Str >> y1Str >> x2Str >> y2Str >> x3Str >> y3Str;

        double x1 = std::stod(x1Str);
        double y1 = std::stod(y1Str);
        double x2 = std::stod(x2Str);
        double y2 = std::stod(y2Str);
        double x3 = std::stod(x3Str);
        double y3 = std::stod(y3Str);

        auto triangleDrawingStrategy = std::make_unique<shapes::TriangleGeometryTypeStrategy>(x1, y1, x2, y2, x3, y3);
        std::unique_ptr<shapes::Shape> shape = make_unique<shapes::Shape>(id, color, std::move(triangleDrawingStrategy));

        m_picture.AddShape(id, std::move(shape));
    }
    else if (type == lineString)
    {
        std::string x1Str;
        std::string y1Str;
        std::string x2Str;
        std::string y2Str;

        iss >> x1Str >> y1Str >> x2Str >> y2Str;

        double x1 = std::stod(x1Str);
        double y1 = std::stod(y1Str);
        double x2 = std::stod(x2Str);
        double y2 = std::stod(y2Str);

        auto lineDrawingStrategy = std::make_unique<shapes::LineGeometryTypeStrategy>(x1, y1, x2, y2);
        std::unique_ptr<shapes::Shape> shape = make_unique<shapes::Shape>(id, color, std::move(lineDrawingStrategy));
        
        m_picture.AddShape(id, std::move(shape));
    }
    else if (type == textString)
    {
        std::string leftTopXStr;
        std::string leftTopYStr;
        std::string sizeStr;
        std::string text;

        iss >> leftTopXStr >> leftTopYStr >> sizeStr;

        std::getline(iss, text);
        if (!text.empty() && text[0] == ' ')
        {
            text.erase(0, 1);
        }

        double leftTopX = std::stod(leftTopXStr);
        double leftTopY = std::stod(leftTopYStr);
        double size = std::stod(sizeStr);

        auto textDrawingStrategy = std::make_unique<shapes::TextGeometryTypeStrategy>(leftTopX, leftTopY, size, text);
        std::unique_ptr<shapes::Shape> shape = make_unique<shapes::Shape>(id, color, std::move(textDrawingStrategy));

        m_picture.AddShape(id, std::move(shape));
    }
}

void ShapeController::MoveShape(std::istringstream &iss)
{
    std::string id;
    std::string dx;
    std::string dy;

    iss >> id >> dx >> dy;

    m_picture.MoveShape(id, std::stod(dx), std::stod(dy));
}

void ShapeController::DeleteShape(std::istringstream &iss)
{
    std::string id;

    iss >> id;

    m_picture.DeleteShape(id);
}

void ShapeController::ListShape()
{
    m_picture.List();
}

void ShapeController::ChangeColor(std::istringstream &iss)
{
    std::string id;
    uint32_t color;

    iss >> id;
    iss >> std::hex >> color;

    m_picture.ChangeColor(id, color);
}

void ShapeController::MovePicture(std::istringstream &iss)
{
    std::string dx;
    std::string dy;

    iss >> dx >> dy;
    m_picture.MovePicture(std::stod(dx), std::stod(dy));
}

void ShapeController::ChangeShape(std::istringstream &iss)
{
    std::vector<double> parameters;
    std::string id;
    uint32_t color;
    std::string type;

    iss >> id;

    std::string colorStr;
    iss >> colorStr;

    if (colorStr[0] == '#') {
        colorStr.erase(0, 1);
        std::stringstream ss;
        ss << std::hex << colorStr;
        ss >> color;
    }

    iss >> type;

    std::string rectangleString = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::RECTANGLE);
    std::string circleString = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::CIRCLE);
    std::string triangleString = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::TRIANGLE);
    std::string lineString = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::LINE);
    std::string textString = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::TEXT);

    if (type == rectangleString)
    {
        std::string leftTopXStr;
        std::string leftTopYStr;
        std::string widthStr;
        std::string heightStr;

        iss >> leftTopXStr >> leftTopYStr >> widthStr >> heightStr;

        double leftTopX = std::stod(leftTopXStr);
        double leftTopY = std::stod(leftTopYStr);
        double width = std::stod(widthStr);
        double height = std::stod(heightStr);

        auto rectangleDrawingStrategy = std::make_unique<shapes::RectangleGeometryTypeStrategy>(leftTopX, leftTopY, width, height);

        m_picture.ChangeShape(id, std::move(rectangleDrawingStrategy));
    }
    else if (type == circleString)
    {
        std::string centerXStr;
        std::string centerYStr;
        std::string radiusStr;

        iss >> centerXStr >> centerYStr >> radiusStr;

        double centerX = std::stod(centerXStr);
        double centerY = std::stod(centerYStr);
        double radius = std::stod(radiusStr);

        auto circleDrawingStrategy = std::make_unique<shapes::CircleGeometryTypeStrategy>(centerX, centerY, radius);

        m_picture.ChangeShape(id, std::move(circleDrawingStrategy));
    }
    else if (type == triangleString)
    {
        std::string x1Str;
        std::string y1Str;
        std::string x2Str;
        std::string y2Str;
        std::string x3Str;
        std::string y3Str;

        iss >> x1Str >> y1Str >> x2Str >> y2Str >> x3Str >> y3Str;

        double x1 = std::stod(x1Str);
        double y1 = std::stod(y1Str);
        double x2 = std::stod(x2Str);
        double y2 = std::stod(y2Str);
        double x3 = std::stod(x3Str);
        double y3 = std::stod(y3Str);

        auto triangleDrawingStrategy = std::make_unique<shapes::TriangleGeometryTypeStrategy>(x1, y1, x2, y2, x3, y3);

        m_picture.ChangeShape(id, std::move(triangleDrawingStrategy));
    }
    else if (type == lineString)
    {
        std::string x1Str;
        std::string y1Str;
        std::string x2Str;
        std::string y2Str;

        iss >> x1Str >> y1Str >> x2Str >> y2Str;

        double x1 = std::stod(x1Str);
        double y1 = std::stod(y1Str);
        double x2 = std::stod(x2Str);
        double y2 = std::stod(y2Str);

        auto lineDrawingStrategy = std::make_unique<shapes::LineGeometryTypeStrategy>(x1, y1, x2, y2);

        m_picture.ChangeShape(id, std::move(lineDrawingStrategy));
    }
    else if (type == textString)
    {
        std::string leftTopXStr;
        std::string leftTopYStr;
        std::string sizeStr;
        std::string text;

        iss >> leftTopXStr >> leftTopYStr >> sizeStr;

        std::getline(iss, text);
        if (!text.empty() && text[0] == ' ')
        {
            text.erase(0, 1);
        }

        double leftTopX = std::stod(leftTopXStr);
        double leftTopY = std::stod(leftTopYStr);
        double size = std::stod(sizeStr);

        auto textDrawingStrategy = std::make_unique<shapes::TextGeometryTypeStrategy>(leftTopX, leftTopY, size, text);

        m_picture.ChangeShape(id, std::move(textDrawingStrategy));
    }
}

void ShapeController::DrawShape(std::istringstream &iss)
{
    std::string id;
    iss >> id;

    m_picture.DrawShape(id, m_canvas);
}

void ShapeController::DrawPicture()
{
    m_picture.DrawPicture(m_canvas);
}
