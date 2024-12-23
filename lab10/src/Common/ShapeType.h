#ifndef LAB10_SHAPETYPE_H
#define LAB10_SHAPETYPE_H

#pragma once

enum class ShapeType
{
    RECTANGLE,
    TRIANGLE,
    ELLIPSE,
};

inline std::ostream& operator<<(std::ostream& os, ShapeType shapeType)
{
    switch (shapeType)
    {
        case ShapeType::RECTANGLE:
            os << "Rectangle";
            break;
        case ShapeType::TRIANGLE:
            os << "Triangle";
            break;
        case ShapeType::ELLIPSE:
            os << "Ellipse";
            break;
        default:
            os << "Unknown Shape";
            break;
    }
    return os;
}

#endif //LAB10_SHAPETYPE_H
