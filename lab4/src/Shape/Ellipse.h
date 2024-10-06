#ifndef INC_4_CIRCLEGEOMETRYTYPESTRATEGY_H
#define INC_4_CIRCLEGEOMETRYTYPESTRATEGY_H

#include <iostream>
#include <string>
#include "Point.h"
#include "Color.h"
#include "Shape.h"

class Ellipse : public Shape
{
public:
    constexpr static std::string type = "ellipse";

    Ellipse(Color color, Point center, double horizontalRadius, double verticalRadius) :
            Shape(color), m_center(center), m_horizontalRadius(horizontalRadius), m_verticalRadius(verticalRadius) {}

    void Draw(gfx::ICanvas &canvas) const override
    {
        canvas.SetColor(convertColorToHEX(GetColor()));
        canvas.DrawEllipse(m_center.x, m_center.y, m_horizontalRadius, m_verticalRadius);
    }

private:
    Point m_center;
    double m_horizontalRadius;
    double m_verticalRadius;
};
#endif //INC_4_CIRCLEGEOMETRYTYPESTRATEGY_H