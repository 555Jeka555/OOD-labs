#ifndef LAB10_SHAPEVIEW_H
#define LAB10_SHAPEVIEW_H

#pragma once
#include <iostream>
#include <memory>
#include "Strategy/IShapeViewStrategy.h"

class ShapeView
{
public:
    ShapeView(
            const std::string& id,
            std::shared_ptr<IShapeViewStrategy> shapeViewStrategy,
            RectD frame,
            ShapeType type,
            RGBAColor fillColor,
            RGBAColor lineColor,
            unsigned int thickness)
            :   m_id(id),
                m_shapeViewStrategy(std::move(shapeViewStrategy)),
                m_frame(frame),
                m_shapeType(type),
                m_fillColor(fillColor),
                m_lineColor(lineColor),
                m_thickness(thickness)
    {}

    [[nodiscard]] std::string GetId() const
    {
        return m_id;
    }

    void SetFrame(const RectD& frame)
    {
        m_frame = frame;
    }

    [[nodiscard]] RectD GetFrame() const
    {
        return m_frame;
    }

    [[nodiscard]] ShapeType GetShapeType() const
    {
        return m_shapeType;
    }

    RGBAColor GetFillColor() const
    {
        return m_fillColor;
    }

    RGBAColor GetLineColor() const
    {
        return m_lineColor;
    }

    unsigned int GetThickness() const
    {
        return m_thickness;
    }

    void Draw(ICanvas& canvas)
    {
        if (m_shapeViewStrategy)
        {
            m_shapeViewStrategy->Draw(canvas, m_frame, m_fillColor, m_lineColor, m_thickness);
        }
    }

private:
    std::string m_id;
    std::shared_ptr<IShapeViewStrategy> m_shapeViewStrategy;
    RectD m_frame;
    ShapeType m_shapeType;
    RGBAColor m_fillColor;
    RGBAColor m_lineColor;
    unsigned int m_thickness;
};

#endif //LAB10_SHAPEVIEW_H
