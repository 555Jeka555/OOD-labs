#ifndef INC_4_TRIANGLEGEOMETRYTYPESTRATEGY_H
#define INC_4_TRIANGLEGEOMETRYTYPESTRATEGY_H

#include <iostream>
#include <string>
#include "Point.h"
#include "Color.h"
#include "Shape.h"

class Triangle : public Shape
{
public:
    constexpr static std::string type = "triangle";

    Triangle(Color color, Point point1, Point point2, Point point3) :
            Shape(color), m_point1(point1), m_point2(point2), m_point3(point3) {}

    void Draw(gfx::ICanvas &canvas) const override
    {
        canvas.SetColor(convertColorToHEX(GetColor()));
        canvas.MoveTo(m_point1.x, m_point1.y);
        canvas.LineTo(m_point2.x, m_point2.y);
        canvas.LineTo(m_point3.x, m_point3.y);
        canvas.LineTo(m_point1.x, m_point1.y);
    }

private:
    Point m_point1;
    Point m_point2;
    Point m_point3;
};

#endif //INC_4_TRIANGLEGEOMETRYTYPESTRATEGY_H
