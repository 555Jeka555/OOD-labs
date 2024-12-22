#ifndef LAB10_LINESTYLE_H
#define LAB10_LINESTYLE_H

#pragma once

#include "../Common/Color.h"

class LineStyle
{
public:

    LineStyle() : m_color(DEFAULT_COLOR), m_thickness(DEFAULT_THICKNESS) {}

    [[nodiscard]] RGBAColor GetColor() const
    {
        return m_color;
    }

    int GetThickness() const
    {
        return m_thickness;
    }

private:
    static constexpr RGBAColor DEFAULT_COLOR = 0xFFFFFFFF;
    static constexpr int DEFAULT_THICKNESS = 1;

    RGBAColor m_color;
    int m_thickness;
};

#endif //LAB10_LINESTYLE_H
