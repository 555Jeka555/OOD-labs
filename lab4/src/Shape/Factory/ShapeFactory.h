#ifndef LAB4_SHAPEFACTORY_H
#define LAB4_SHAPEFACTORY_H

#include <memory>
#include <algorithm>
#include <cctype>
#include "IShapeFactory.h"
#include "../Triangle.h"
#include "../Ellipse.h"
#include "../Rectangle.h"
#include "../RegularPolygon.h"

class ShapeFactory : public IShapeFactory
{
public:
    std::unique_ptr<Shape> CreateShape(const std::string & description) override
    {
        std::istringstream iss(description);

        std::string shapeType;
        iss >> shapeType;

        std::string colorStr;
        iss >> colorStr;
        std::transform(colorStr.begin(), colorStr.end(), colorStr.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        Color color = convertToColor(colorStr);

        if (shapeType == Triangle::type)
        {
            std::string pointX1Str;
            std::string pointY1Str;
            std::string pointX2Str;
            std::string pointY2Str;
            std::string pointX3Str;
            std::string pointY3Str;

            iss >> pointX1Str >> pointY1Str >> pointX2Str >> pointY2Str >> pointX3Str >> pointY3Str;

            Point point1(std::stod(pointX1Str), std::stod(pointY1Str));
            Point point2(std::stod(pointX2Str), std::stod(pointY2Str));
            Point point3(std::stod(pointX3Str), std::stod(pointY3Str));

            return std::make_unique<Triangle>(color, point1, point2, point3);
        }
        else if (shapeType == Ellipse::type)
        {
            std::string centerX1Str;
            std::string centerY1Str;
            std::string horizontalRadiusStr;
            std::string verticalRadiusStr;

            iss >> centerX1Str >> centerY1Str >> horizontalRadiusStr >> verticalRadiusStr;

            Point center(std::stod(centerX1Str), std::stod(centerY1Str));

            return std::make_unique<Ellipse>(
                    color,
                    center,
                    std::stod(horizontalRadiusStr),
                    std::stod(verticalRadiusStr)
            );
        }
        else if (shapeType == Rectangle::type)
        {
            std::string leftTopX1Str;
            std::string leftTopY1Str;
            std::string widthStr;
            std::string heightStr;

            iss >> leftTopX1Str >> leftTopY1Str >> widthStr >> heightStr;

            Point leftTop(std::stod(leftTopX1Str), std::stod(leftTopY1Str));

            return std::make_unique<Rectangle>(
                    color,
                    leftTop,
                    std::stod(widthStr),
                    std::stod(heightStr)
            );
        }
        else if (shapeType == RegularPolygon::type)
        {
            std::string centerX1Str;
            std::string centerY1Str;
            std::string pointsCountStr;
            std::string radiusStr;

            iss >> centerX1Str >> centerY1Str >> pointsCountStr >> radiusStr;

            Point center(std::stod(centerX1Str), std::stod(centerY1Str));

            return std::make_unique<RegularPolygon>(
                    color,
                    center,
                    std::stoi(pointsCountStr),
                    std::stod(radiusStr)
            );
        }

        throw std::invalid_argument("Unknown shape type");
    }
};

#endif //LAB4_SHAPEFACTORY_H
