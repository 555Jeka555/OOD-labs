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
    }
}

void ShapeController::AddShape(std::istringstream &iss)
{
    std::vector<double> parameters;
    std::string id;
    uint32_t color;
    std::string type;

    iss >> id;
    iss >> std::hex >> color;
    iss >> type;
    
    std::string rectangleString = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::RECTANGLE);
    std::string circleString = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::CIRCLE);
    std::string triangleString = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::TRIANGLE);
    std::string lineString = ShapeTypeConverter::ConvertShapeTypeToString(ShapeType::Line);

    if (type == rectangleString)
    {
        std::string m_leftTopX;
        std::string m_leftTopY;
        std::string width;
        std::string height;

        iss >> m_leftTopX >> m_leftTopY >> width >> height;

        parameters.push_back(std::stod(m_leftTopX));
        parameters.push_back(std::stod(m_leftTopY));
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

        m_shapeService.AddShape(id, color, rectangleString, parameters, "");
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

        m_shapeService.AddShape(id, color, rectangleString, parameters, "");
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

        m_shapeService.AddShape(id, color, rectangleString, parameters, "");
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
