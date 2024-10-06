#ifndef INC_4_REGULARPOLYGONGEOMETRYTYPESTRATEGY_H
#define INC_4_REGULARPOLYGONGEOMETRYTYPESTRATEGY_H

#include <iostream>
#include <string>
#include "Point.h"
#include "Color.h"
#include "Shape.h"

class RegularPolygon : public Shape
{
public:
    constexpr static std::string type = "regularPolygon";

    RegularPolygon(Color color, Point center, int pointsCount, double radius) :
            Shape(color), m_center(center), m_pointsCount(pointsCount), m_radius(radius) {}

    void Draw(gfx::ICanvas &canvas) const override
    {
        canvas.SetColor(convertColorToHEX(GetColor()));

        double angleStep = 2 * M_PI / m_pointsCount;

        double startX = m_center.x + m_radius * std::cos(0);
        double startY = m_center.y + m_radius * std::sin(0);

        double prevX = startX;
        double prevY = startY;

        for (int i = 1; i <= m_pointsCount; ++i) {
            double angle = i * angleStep;
            double x = m_center.x + m_radius * std::cos(angle);
            double y = m_center.y + m_radius * std::sin(angle);

            canvas.DrawLine(prevX, prevY, x, y);

            prevX = x;
            prevY = y;
        }

        canvas.DrawLine(prevX, prevY, startX, startY);
    }

private:
    Point m_center;
    int m_pointsCount;
    double m_radius;
};

#endif //INC_4_REGULARPOLYGONGEOMETRYTYPESTRATEGY_H
