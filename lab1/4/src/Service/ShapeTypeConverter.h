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
            default:
                return "none";
        }
    }
};


#endif //INC_4_SHAPETYPECONVERTER_H
