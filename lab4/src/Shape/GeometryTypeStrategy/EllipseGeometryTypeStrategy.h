#ifndef INC_4_CIRCLEGEOMETRYTYPESTRATEGY_H
#define INC_4_CIRCLEGEOMETRYTYPESTRATEGY_H

#include <iostream>
#include <string>
#include "IGeometryTypeStrategy.h"
#include "../Point.h"
#include "../Color.h"

class EllipseGeometryTypeStrategy : public IGeometryTypeStrategy
{
public:
    EllipseGeometryTypeStrategy(
            Point center,
            double radius
    ) :
            m_center(center), m_radius(radius) {}

    void Draw(ICanvas &canvas, Color color) const override
    {
        canvas.DrawEllipse(m_center.x, m_center.y, m_radius, m_radius);
    }

private:
    Point m_center;
    double m_radius;
};
#endif //INC_4_CIRCLEGEOMETRYTYPESTRATEGY_H