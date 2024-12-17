#ifndef LAB10_FILLSTYLE_H
#define LAB10_FILLSTYLE_H

#pragma once
#include "../Common/Color.h"

class FillStyle
{
public:
    FillStyle() : m_color(DEFAULT_COLOR) {}

    RGBAColor GetColor() const
    {
        return m_color;
    }

private:
    static constexpr RGBAColor DEFAULT_COLOR = 0x2F528FFF;

    RGBAColor m_color;
};

#endif //LAB10_FILLSTYLE_H
