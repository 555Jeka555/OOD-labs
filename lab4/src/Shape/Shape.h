#ifndef INC_4_SHAPE_H
#define INC_4_SHAPE_H

#include <iostream>
#include <string>
#include <cstdint>
#include <memory>
#include <utility>
#include "../Canvas/ICanvas.h"
#include "../Shape/GeometryTypeStrategy/IGeometryTypeStrategy.h"
#include "Color.h"

class Shape
{
public:
    Shape(std::string id, Color color, std::unique_ptr<IGeometryTypeStrategy> geometryTypeStrategy) :
            m_id(std::move(id)), m_color(color), m_geometryTypeStrategy(std::move(geometryTypeStrategy))
    {}

    void Draw(ICanvas& canvas)
    {
        m_geometryTypeStrategy->Draw(canvas, m_color);
    }

    [[nodiscard]] std::string GetId() const
    {
        return m_id;
    }

    [[nodiscard]] Color GetColor() const
    {
        return m_color;
    }

    ~Shape() = default;
private:
    std::string m_id;
    Color m_color;
    std::unique_ptr<IGeometryTypeStrategy> m_geometryTypeStrategy;
};

#endif //INC_4_SHAPE_H
