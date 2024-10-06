#ifndef INC_4_RECTANGLEGEOMETRYTYPESTRATEGY_H
#define INC_4_RECTANGLEGEOMETRYTYPESTRATEGY_H

#include <iostream>
#include <string>
#include "IGeometryTypeStrategy.h"
#include "../Point.h"
#include "../Color.h"


class RegularPolygonGeometryTypeStrategy : public IGeometryTypeStrategy
{
public:
    RegularPolygonGeometryTypeStrategy(
        Point center,
        int pointsCount,
        double radius
    ) :
        m_center(center), m_pointsCount(pointsCount), m_radius(radius) {}

    void Draw(ICanvas &canvas, Color color) const override
    {
        // TODO написать рисовку правильного многоугольника, добавить работу с Color
        canvas.MoveTo(m_center.x, m_center.y);
    }

private:
    Point m_center;
    int m_pointsCount;
    double m_radius;
};

#endif //INC_4_RECTANGLEGEOMETRYTYPESTRATEGY_H
