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
#include "../Shape/DrawingStrategy/IGeometryTypeStrategy.h"
#include "../Shape/DrawingStrategy/RectangleGeometryTypeStrategy.h"
#include "../Shape/DrawingStrategy/CircleGeometryTypeStrategy.h"
#include "../Shape/DrawingStrategy/TriangleGeometryTypeStrategy.h"
#include "../Shape/DrawingStrategy/LineGeometryTypeStrategy.h"
#include "../Shape/DrawingStrategy/TextGeometryTypeStrategy.h"
#include "../Canvas/ICanvas.h"

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

        void ChangeShape(const std::string &id, std::unique_ptr<IGeometryTypeStrategy> newDrawingStrategy);

        void DrawShape(const std::string& id, gfx::ICanvas &canvas);

        void DrawPicture(gfx::ICanvas &canvas);

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
