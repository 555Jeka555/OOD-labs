#ifndef LAB10_RECTANGLEVIEWSTRATEGY_H
#define LAB10_RECTANGLEVIEWSTRATEGY_H

#pragma once
#include "IShapeViewStrategy.h"
#include "../../Model/FillStyle.h"
#include "../../Model/LineStyle.h"

class RectangleViewStrategy : public IShapeViewStrategy
{
public:
    void Draw(
            ICanvas &canvas,
            RectD frame,
            RGBAColor fillColor,
            RGBAColor lineColor,
            unsigned lineThickness
    ) override
    {
        Point leftTop = { frame.left, frame.top };
        Point rightBottom = { frame.left + frame.width, frame.top + frame.height };
        Point rightTop = { rightBottom.m_x, frame.top };
        Point leftBottom = { frame.left, rightBottom.m_y };

        canvas.SetLineColor(lineColor);
        int thickness = lineThickness;
        canvas.SetLineThickness(lineThickness);

        std::vector<Point> points{ leftTop, rightTop, rightBottom, leftBottom };
        canvas.FillPolygon(points);

        canvas.SetFillColor(fillColor);

        canvas.DrawLine({ leftTop.m_x - thickness, leftTop.m_y }, { rightTop.m_x + thickness, rightTop.m_y });
        canvas.DrawLine(rightTop, rightBottom);
        canvas.DrawLine({ rightBottom.m_x + thickness, rightBottom.m_y + thickness }, { leftBottom.m_x - thickness, leftBottom.m_y + thickness });
        canvas.DrawLine(leftBottom, leftTop);
    }
};

#endif //LAB10_RECTANGLEVIEWSTRATEGY_H
