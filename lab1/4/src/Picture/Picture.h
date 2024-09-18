#ifndef INC_4_PICTURE_H
#define INC_4_PICTURE_H

#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <map>
#include "ShapeType.h"
#include "../Picture/ShapeTypeConverter.h"
#include "../Shape/Shape.h"
#include "../Shape/DrawingStrategy/IDrawingStrategy.h"
#include "../Shape/DrawingStrategy/RectangleDrawingStrategy.h"
#include "../Shape/DrawingStrategy/CircleDrawingStrategy.h"
#include "../Shape/DrawingStrategy/TriangleDrawingStrategy.h"
#include "../Shape/DrawingStrategy/LineDrawingStrategy.h"
#include "../Shape/DrawingStrategy/TextDrawingStrategy.h"

namespace shapes
{
    class Picture
    {
    public:
        void AddShape(const std::string& id, std::unique_ptr<Shape> shape);

        void MoveShape(const std::string& id, double dx, double dy);

        void MovePicture(double dx, double dy);

        void DeleteShape(const std::string &id);

        void List();

        void ChangeColor(const std::string& id, uint32_t color);

        void ChangeShape(const std::string &id, std::unique_ptr<IDrawingStrategy> newDrawingStrategy);

        std::map<std::string, std::unique_ptr<shapes::Shape>> GetShapes()
        {
            return std::move(m_shapes);
        }

        [[nodiscard]] std::vector<std::string> GetShapeIds() const
        {
            return m_shapeIds;
        }

    private:
        std::map<std::string, std::unique_ptr<shapes::Shape>> m_shapes = {};
        std::vector<std::string> m_shapeIds = {};
    };
}

#endif //INC_4_PICTURE_H
