#ifndef LAB10_SHAPEAPP_H
#define LAB10_SHAPEAPP_H

#pragma once

#include <memory>
#include <boost/signals2.hpp>
#include "../../Model/Shape.h"

class ShapeApp {
public:
    explicit ShapeApp(const std::shared_ptr<Shape>& shape) : m_shape(shape), m_frame(shape->GetFrame()) {
        m_shape->DoOnFrameChanged([&, this](const RectD &frame) {
            m_frame = frame;
            m_frameChanged(frame);
        });
    }

    [[nodiscard]] std::string GetId() const {
        return m_shape->GetId();
    }

    [[nodiscard]] ShapeType GetType() const
    {
        return m_shape->GetType();
    }

    [[nodiscard]] std::shared_ptr<Shape> GetShape() const
    {
        return m_shape;
    }

    [[nodiscard]] RectD GetFrame() const
    {
        return m_frame;
    }

    void SetFrame(const RectD &frame)
    {
        m_frame = frame;
        m_frameChanged(m_frame);
    }

    [[nodiscard]] const std::shared_ptr<LineStyle>& GetLineColor() const
    {
        return m_shape->GetLineStyle();
    }

    [[nodiscard]] const std::shared_ptr<FillStyle>& GetFillColor() const
    {
        return m_shape->GetFillStyle();
    }

    void DoOnFrameChanged(const std::function<void(const RectD&)>& handler)
    {
        m_frameChanged.connect(handler);
    }

private:
    RectD m_frame;
    std::shared_ptr<Shape> m_shape;
    boost::signals2::signal<void(const RectD&)> m_frameChanged;
};

#endif //LAB10_SHAPEAPP_H
