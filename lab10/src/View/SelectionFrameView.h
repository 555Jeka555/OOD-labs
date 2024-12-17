#ifndef LAB10_SELECTIONFRAMEVIEW_H
#define LAB10_SELECTIONFRAMEVIEW_H

#pragma once
#include "../App/Model/ShapeApp.h"
#include "../Common/Point.h"
#include "../Canvas/ICanvas.h"

class SelectionFrameView {
public:
    SelectionFrameView(ShapeApp &shape)
            : m_shapeApp(shape) {
    }

    void Show(ICanvas &canvas) {
        auto thickness = DEFAULT_SELECTION_THICKNESS;
        RectD frame = m_shapeApp.GetFrame();
        Point leftTop = {frame.left, frame.top};
        Point rightBottom = {frame.left + frame.width, frame.top + frame.height};
        Point rightTop = {rightBottom.m_x, frame.top};
        Point leftBottom = {frame.left, rightBottom.m_y};

        canvas.SetFillColor(DEFAULT_SELECTION_COLOR);

        canvas.SetLineThickness(thickness);

        canvas.DrawLine({leftTop.m_x - thickness, leftTop.m_y}, {rightTop.m_x + thickness, rightTop.m_y});
        canvas.DrawLine(rightTop, rightBottom);
        canvas.DrawLine({rightBottom.m_x + thickness, rightBottom.m_y + thickness},
                        {leftBottom.m_x - thickness, leftBottom.m_y + thickness});
        canvas.DrawLine(leftBottom, leftTop);

        ShowCorner(canvas, leftTop);
        ShowCorner(canvas, {rightTop.m_x - DEFAULT_SELECTION_CORNER_SIZE, rightTop.m_y});
        ShowCorner(canvas,
                   {rightBottom.m_x - DEFAULT_SELECTION_CORNER_SIZE, rightBottom.m_y - DEFAULT_SELECTION_CORNER_SIZE});
        ShowCorner(canvas, {leftBottom.m_x, leftBottom.m_y - DEFAULT_SELECTION_CORNER_SIZE});
    }

private:
    constexpr static uint32_t DEFAULT_SELECTION_COLOR = 0x000000FF;
    constexpr static unsigned int DEFAULT_SELECTION_THICKNESS = 1;
    constexpr static size_t DEFAULT_SELECTION_CORNER_SIZE = 10;

    ShapeApp& m_shapeApp;
    
    void ShowCorner(ICanvas &canvas, const Point &leftTop) {
        Point rightTop = {leftTop.m_x + DEFAULT_SELECTION_CORNER_SIZE, leftTop.m_y};
        Point rightBottom = {leftTop.m_x + DEFAULT_SELECTION_CORNER_SIZE, leftTop.m_y + DEFAULT_SELECTION_CORNER_SIZE};
        Point leftBottom = {leftTop.m_x, leftTop.m_y + DEFAULT_SELECTION_CORNER_SIZE};

        canvas.SetFillColor(DEFAULT_SELECTION_COLOR);

        std::vector<Point> points{leftTop, rightTop, rightBottom, leftBottom};
        canvas.FillPolygon(points);
    }
};

#endif //LAB10_SELECTIONFRAMEVIEW_H
