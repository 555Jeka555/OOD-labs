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
}
