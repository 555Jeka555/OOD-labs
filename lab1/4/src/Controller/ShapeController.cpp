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
    }
}

void ShapeController::AddShape(std::istringstream &iss)
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
        std::string leftTopX;
        std::string leftTopY;
        std::string width;
        std::string height;

        iss >> leftTopX >> leftTopY >> width >> height;

        parameters.push_back(std::stod(leftTopX));
        parameters.push_back(std::stod(leftTopY));
        parameters.push_back(std::stod(width));
        parameters.push_back(std::stod(height));

        m_shapeService.AddShape(id, color, rectangleString, parameters, "");
    }
    else if (type == circleString)
    {
        std::string centerX;
        std::string centerY;
        std::string radius;

        iss >> centerX >> centerY >> radius;

        parameters.push_back(std::stod(centerX));
        parameters.push_back(std::stod(centerY));
        parameters.push_back(std::stod(radius));

        m_shapeService.AddShape(id, color, circleString, parameters, "");
    }
    else if (type == triangleString)
    {
        std::string x1;
        std::string y1;
        std::string x2;
        std::string y2;
        std::string x3;
        std::string y3;

        iss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

        parameters.push_back(std::stod(x1));
        parameters.push_back(std::stod(y1));
        parameters.push_back(std::stod(x2));
        parameters.push_back(std::stod(y2));
        parameters.push_back(std::stod(x3));
        parameters.push_back(std::stod(y3));

        m_shapeService.AddShape(id, color, triangleString, parameters, "");
    }
    else if (type == lineString)
    {
        std::string x1;
        std::string y1;
        std::string x2;
        std::string y2;

        iss >> x1 >> y1 >> x2 >> y2;

        parameters.push_back(std::stod(x1));
        parameters.push_back(std::stod(y1));
        parameters.push_back(std::stod(x2));
        parameters.push_back(std::stod(y2));

        m_shapeService.AddShape(id, color, lineString, parameters, "");
    }
    else if (type == textString)
    {
        std::string leftTopX;
        std::string leftTopY;
        std::string size;
        std::string text;

        iss >> leftTopX >> leftTopY >> size;

        std::getline(iss, text);
        if (!text.empty() && text[0] == ' ')
        {
            text.erase(0, 1);
        }

        parameters.push_back(std::stod(leftTopX));
        parameters.push_back(std::stod(leftTopY));
        parameters.push_back(std::stod(size));

        m_shapeService.AddShape(id, color, textString, parameters, text);
    }
}

void ShapeController::MoveShape(std::istringstream &iss)
{
    std::string id;
    std::string dx;
    std::string dy;

    iss >> id >> dx >> dy;

    m_shapeService.MoveShape(id, std::stod(dx), std::stod(dy));
}

void ShapeController::DeleteShape(std::istringstream &iss)
{
    std::string id;

    iss >> id;

    m_shapeService.DeleteShape(id);
}

void ShapeController::ListShape()
{
    m_shapeService.List();
}

void ShapeController::ChangeColor(std::istringstream &iss)
{
    std::string id;
    uint32_t color;

    iss >> id;
    iss >> std::hex >> color;

    m_shapeService.ChangeColor(id, color);
}

void ShapeController::MovePicture(std::istringstream &iss)
{
    std::string dx;
    std::string dy;

    iss >> dx >> dy;
    m_shapeService.MovePicture(std::stod(dx), std::stod(dy));
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
        std::string leftTopX;
        std::string leftTopY;
        std::string width;
        std::string height;

        iss >> leftTopX >> leftTopY >> width >> height;

        parameters.push_back(std::stod(leftTopX));
        parameters.push_back(std::stod(leftTopY));
        parameters.push_back(std::stod(width));
        parameters.push_back(std::stod(height));

        m_shapeService.ChangeShape(id, rectangleString, parameters, "");
    }
    else if (type == circleString)
    {
        std::string centerX;
        std::string centerY;
        std::string radius;

        iss >> centerX >> centerY >> radius;

        parameters.push_back(std::stod(centerX));
        parameters.push_back(std::stod(centerY));
        parameters.push_back(std::stod(radius));

        m_shapeService.ChangeShape(id, circleString, parameters, "");
    }
    else if (type == triangleString)
    {
        std::string x1;
        std::string y1;
        std::string x2;
        std::string y2;
        std::string x3;
        std::string y3;

        iss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

        parameters.push_back(std::stod(x1));
        parameters.push_back(std::stod(y1));
        parameters.push_back(std::stod(x2));
        parameters.push_back(std::stod(y2));
        parameters.push_back(std::stod(x3));
        parameters.push_back(std::stod(y3));

        m_shapeService.ChangeShape(id, triangleString, parameters, "");
    }
    else if (type == lineString)
    {
        std::string x1;
        std::string y1;
        std::string x2;
        std::string y2;

        iss >> x1 >> y1 >> x2 >> y2;

        parameters.push_back(std::stod(x1));
        parameters.push_back(std::stod(y1));
        parameters.push_back(std::stod(x2));
        parameters.push_back(std::stod(y2));

        m_shapeService.ChangeShape(id, lineString, parameters, "");
    }
    else if (type == textString)
    {
        std::string leftTopX;
        std::string leftTopY;
        std::string size;
        std::string text;

        iss >> leftTopX >> leftTopY >> size;

        std::getline(iss, text);
        if (!text.empty() && text[0] == ' ')
        {
            text.erase(0, 1);
        }

        parameters.push_back(std::stod(leftTopX));
        parameters.push_back(std::stod(leftTopY));
        parameters.push_back(std::stod(size));

        m_shapeService.ChangeShape(id, textString, parameters, text);
    }
}
