#ifndef LAB10_ICANVAS_H
#define LAB10_ICANVAS_H

#pragma once

#include <vector>
#include "../Common/Point.h"
#include "../Common/Color.h"
#include "../Common/Rect.h"

class ICanvas
{
public:
    virtual ~ICanvas() = default;

    virtual void DrawLine(const Point& from, const Point& to) = 0;
    virtual void DrawClosedPolyLine(const std::vector<Point>&) = 0;
    virtual void DrawEllipse(RectD) = 0;
    virtual void FillEllipse(RectD) = 0;
    virtual void FillPolygon(const std::vector<Point>&) = 0;
    virtual void SetFillColor(RGBAColor) = 0;
    virtual void SetLineColor(RGBAColor) = 0;
    virtual void SetLineThickness(unsigned int) = 0;
    virtual void DrawText(const std::string&, const Point& position) = 0;
};

#endif //LAB10_ICANVAS_H
