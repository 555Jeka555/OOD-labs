#ifndef INC_4_RECTANGLEGEOMETRYTYPESTRATEGY_H
#define INC_4_RECTANGLEGEOMETRYTYPESTRATEGY_H

#include <iostream>
#include <string>
#include "Point.h"
#include "Color.h"
#include "Shape.h"

// regularPolygon #123456 10 20 8 40
class RegularPolygon : public Shape
{
public:
    RegularPolygon(Color color, Point center, int pointsCount, double radius) :
            Shape(color), m_center(center), m_pointsCount(pointsCount), m_radius(radius) {}

    void Draw(gfx::ICanvas &canvas) const override
    {
        // TODO написать рисовку правильного многоугольника, добавить работу с Color
        canvas.SetColor(convertColorToHEX(GetColor()));
        canvas.MoveTo(m_center.x, m_center.y);
    }

private:
    Point m_center;
    int m_pointsCount;
    double m_radius;
};

#endif //INC_4_RECTANGLEGEOMETRYTYPESTRATEGY_H
