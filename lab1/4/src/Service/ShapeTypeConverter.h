#ifndef INC_4_SHAPETYPECONVERTER_H
#define INC_4_SHAPETYPECONVERTER_H


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
            default:
                return "none";
        }
    }
};


#endif //INC_4_SHAPETYPECONVERTER_H
