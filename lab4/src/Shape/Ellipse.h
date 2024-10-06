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
    Ellipse(Color color, Point center, double radius) :
            Shape(color), m_center(center), m_radius(radius) {}

    void Draw(ICanvas &canvas) const override
    {
        canvas.DrawEllipse(m_center.x, m_center.y, m_radius, m_radius);
    }

private:
    Point m_center;
    double m_radius;
};
#endif //INC_4_CIRCLEGEOMETRYTYPESTRATEGY_H