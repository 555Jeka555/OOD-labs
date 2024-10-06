#ifndef INC_4_RECTANGLEGEOMETRYTYPESTRATEGY_H
#define INC_4_RECTANGLEGEOMETRYTYPESTRATEGY_H

#include <iostream>
#include <string>
#include "IGeometryTypeStrategy.h"
#include "../Point.h"
#include "../Color.h"

class RectangleGeometryTypeStrategy : public IGeometryTypeStrategy
{
public:
    RectangleGeometryTypeStrategy(
            Point leftTop,
            double width,
            double height
    ) :
            m_leftTop(leftTop), m_width(width), m_height(height) {}

    void Draw(ICanvas &canvas, Color color) const override
    {
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
