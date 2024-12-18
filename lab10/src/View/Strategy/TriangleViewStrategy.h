#ifndef LAB10_TRIANGLEVIEWSTRATEGY_H
#define LAB10_TRIANGLEVIEWSTRATEGY_H

#pragma once
#include "IShapeViewStrategy.h"
#include "../../Model/FillStyle.h"
#include "../../Model/LineStyle.h"

class TriangleViewStrategy : public IShapeViewStrategy
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
        Point p1 = { frame.left, frame.top + frame.height };
        Point p2 = { frame.left + frame.width / 2, frame.top };
        Point p3 = { frame.left + frame.width, frame.top + frame.height };

        auto points = std::vector<Point>{ p1, p2, p3 };

        canvas.SetFillColor(fillColor);

        canvas.FillPolygon(points);

        canvas.SetLineColor(lineColor);

        canvas.SetLineThickness(lineThickness);

        canvas.DrawClosedPolyLine(points);
    }

};

#endif //LAB10_TRIANGLEVIEWSTRATEGY_H
