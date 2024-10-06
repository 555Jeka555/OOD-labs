#ifndef INC_4_SHAPE_H
#define INC_4_SHAPE_H

#include <iostream>
#include <string>
#include <cstdint>
#include <memory>
#include <utility>
#include "../Canvas/ICanvas.h"

#include "Color.h"

class Shape
{
public:
    explicit Shape(Color color) :
            m_color(color)
    {}

    virtual void Draw(gfx::ICanvas& canvas) const = 0;

    [[nodiscard]] Color GetColor() const
    {
        return m_color;
    }

    ~Shape() = default;
private:
    Color m_color;
};

#endif //INC_4_SHAPE_H
