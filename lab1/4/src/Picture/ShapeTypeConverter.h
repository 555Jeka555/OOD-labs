#ifndef INC_4_SHAPETYPECONVERTER_H
#define INC_4_SHAPETYPECONVERTER_H

#include <string>
#include "ShapeType.h"

class ShapeTypeConverter
{
public:
    static std::string ConvertShapeTypeToString(ShapeType shapeType)
    {
        switch (shapeType)
        {
            case ShapeType::RECTANGLE:
                return "rectangle";
            case ShapeType::CIRCLE:
                return "circle";
            case ShapeType::TRIANGLE:
                return "triangle";
            case ShapeType::LINE:
                return "line";
            case ShapeType::TEXT:
                return "text";
            default:
                return "none";
        }
    }
};


#endif //INC_4_SHAPETYPECONVERTER_H
