#ifndef LAB10_SHAPE_H
#define LAB10_SHAPE_H

#pragma once
#include <iostream>
#include <memory>
#include <boost/signals2.hpp>
#include "../Common/ShapeType.h"
#include "../Common/UUID.h"
#include "../Common/Rect.h"
#include "LineStyle.h"
#include "FillStyle.h"

class Shape
{
public:
    inline static const RectD DEFAULT_FRAME = { 200, 200, 100, 100 };

    explicit Shape(ShapeType type, const RectD& frame = DEFAULT_FRAME)
        :
            m_id(GenerateUUID()),
            m_type(type),
            m_frame(frame),
            m_lineStyle(std::make_shared<LineStyle>()),
            m_fillStyle(std::make_shared<FillStyle>())
    {}

    [[nodiscard]] const std::string &GetId() const
    {
        return m_id;
    }

    [[nodiscard]] ShapeType GetType() const
    {
        return m_type;
    }

    [[nodiscard]] const std::shared_ptr<LineStyle> &GetLineStyle() const
    {
        return m_lineStyle;
    }

    [[nodiscard]] const std::shared_ptr<FillStyle> &GetFillStyle() const
    {
        return m_fillStyle;
    }

    [[nodiscard]] const RectD &GetFrame() const
    {
        return m_frame;
    }

    void SetFrame(const RectD& frame)
    {
        m_frame = frame;
        m_frameChanged(frame);
    }

    void DoOnFrameChanged(const std::function<void(const RectD&)>& handler)
    {
        m_frameChanged.connect(handler);
    }

private:

    std::string m_id;
    ShapeType m_type;
    std::shared_ptr<LineStyle> m_lineStyle;
    std::shared_ptr<FillStyle> m_fillStyle;
    RectD m_frame;
    boost::signals2::signal<void(const RectD&)> m_frameChanged;
};

#endif //LAB10_SHAPE_H
