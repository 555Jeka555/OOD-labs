#ifndef LAB7_SHAPE_H
#define LAB7_SHAPE_H

#include <optional>
#include "IShape.h"

class Shape : public IShape {
public:
    Shape(const RectD &frame,
          std::unique_ptr<IStyle> outlineStyle,
          std::unique_ptr<IStyle> fillStyle
    )
        :   m_outlineStyle(std::move(outlineStyle)),
            m_fillStyle(std::move(fillStyle))
    {
        m_frame = std::optional<RectD>(frame);
    }

    [[nodiscard]] std::optional<RectD> GetFrame() const override
    {
        return m_frame;
    }

    void SetFrame(const std::optional<RectD> &rect) override {
        m_frame = rect;
    }

    IStyle &GetOutlineStyle() override {
        return *m_outlineStyle;
    }

    const IStyle &GetOutlineStyle() const override {
        return *m_outlineStyle;
    }

    IStyle &GetFillStyle() override {
        return *m_fillStyle;
    }

    const IStyle &GetFillStyle() const override {
        return *m_fillStyle;
    }

    std::shared_ptr<IGroupShape> GetGroup() override
    {
        return nullptr;
    }

    std::shared_ptr<const IGroupShape> GetGroup() const override
    {
        return nullptr;
    }

private:
    std::optional<RectD> m_frame{};
    std::unique_ptr<IStyle> m_outlineStyle;
    std::unique_ptr<IStyle> m_fillStyle;
};

#endif //LAB7_SHAPE_H
