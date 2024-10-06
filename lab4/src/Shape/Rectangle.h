#ifndef INC_4_RECTANGLEGEOMETRYTYPESTRATEGY_H
#define INC_4_RECTANGLEGEOMETRYTYPESTRATEGY_H

#include <iostream>
#include <string>
#include "Point.h"
#include "Color.h"
#include "Shape.h"

class Rectangle : public Shape
{
public:
    constexpr static std::string type = "rectangle";

    Rectangle(Color color, Point leftTop, double width, double height) :
            Shape(color), m_leftTop(leftTop), m_width(width), m_height(height) {}

    void Draw(gfx::ICanvas &canvas) const override
    {
        canvas.SetColor(convertColorToHEX(GetColor()));
        canvas.MoveTo(m_leftTop.x, m_leftTop.y);
        canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y);
        canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y + m_height);
        canvas.LineTo(m_leftTop.x, m_leftTop.y + m_height);
        canvas.LineTo(m_leftTop.x, m_leftTop.y);
    }

private:
    Point m_leftTop;
    double m_width;
    double m_height;
};

#endif //INC_4_RECTANGLEGEOMETRYTYPESTRATEGY_H