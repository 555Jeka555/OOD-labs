#ifndef INC_4_SHAPESERVICE_H
#define INC_4_SHAPESERVICE_H

#include <string>
#include <cstdint>
#include <vector>
#include <map>
#include "ShapeType.h"
#include "../Service/ShapeTypeConverter.h"
#include "../Shape/Shape.h"
#include "../Shape/DrawingStrategy/IDrawingStrategy.h"
#include "../Shape/DrawingStrategy/RectangleDrawingStrategy.h"

class ShapeService
{
public:
    void AddShape(const std::string& id, uint32_t color, const std::string& type, const std::vector<double>& parameters, const std::string& text);

    void MoveShape(const std::string& id, double dx, double dy);

    void MovePicture();

    void DeleteShape(const std::string &id);

    void List();

    void ChangeColor(const std::string& id, uint32_t color);

    void ChangeShape();

    std::map<std::string, std::unique_ptr<shapes::Shape>> GetShapes()
    {
        return std::move(m_shapes);
    }

private:
    std::map<std::string, std::unique_ptr<shapes::Shape>> m_shapes = {};
};


#endif //INC_4_SHAPESERVICE_H
