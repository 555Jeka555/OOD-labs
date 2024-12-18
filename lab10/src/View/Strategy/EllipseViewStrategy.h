#ifndef LAB10_SHAPEVIEWSTRATEGY_H
#define LAB10_SHAPEVIEWSTRATEGY_H

#pragma once
#include "IShapeViewStrategy.h"
#include "../../Model/FillStyle.h"
#include "../../Model/LineStyle.h"

class EllipseViewStrategy : public IShapeViewStrategy
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
        canvas.SetFillColor(fillColor);
        canvas.FillEllipse(frame);

        canvas.SetLineColor(lineColor);

        canvas.SetLineThickness(lineThickness);

        canvas.DrawEllipse(frame);
    }
};

#endif //LAB10_SHAPEVIEWSTRATEGY_H
