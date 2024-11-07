#ifndef LAB7_GROUPSHAPE_H
#define LAB7_GROUPSHAPE_H

#include <unordered_map>
#include "IGroupShape.h"
#include "Style/Style.h"

class GroupShape : public IGroupShape
{
public:
    constexpr static std::string typeStart = "group_start";
    constexpr static std::string typeEnd = "group_end";

    GroupShape()
            : m_outlineStyle(0xFFFFFFFF),
              m_fillStyle(0xFFFFFFFF)
    {
    }

    RectD GetFrame() const override
    {
        if (m_shapes.empty())
        {
            return {0, 0, 0, 0};
        }

        double left = std::numeric_limits<double>::max();
        double top = std::numeric_limits<double>::max();
        double right = std::numeric_limits<double>::lowest();
        double bottom = std::numeric_limits<double>::lowest();

        for (const auto &pair: m_shapes)
        {
            RectD frame = pair.second->GetFrame();
            left = std::min(left, frame.left);
            top = std::min(top, frame.top);
            right = std::max(right, frame.left + frame.width);
            bottom = std::max(bottom, frame.top + frame.height);
        }

        return {left, top, right - left, bottom - top};
    }

    void SetFrame(const RectD & rect) override
    {
        auto [left, top, width, height] = GetFrame();
        const double scaleX = rect.width / width;
        const double scaleY = rect.height / height;

        for (const auto &pair: m_shapes)
        {
            const RectD shapeFrame = pair.second->GetFrame();
            const double newLeft = rect.left + (shapeFrame.left - left) * scaleX;
            const double newTop = rect.top + (shapeFrame.top - top) * scaleY;
            const double newWidth = shapeFrame.width * scaleX;
            const double newHeight = shapeFrame.height * scaleY;
            pair.second->SetFrame({newLeft, newTop, newWidth, newHeight});
        }
    }

    IStyle & GetOutlineStyle() override
    {
        return m_outlineStyle;
    }

    const IStyle & GetOutlineStyle() const override
    {
        return m_outlineStyle;
    }

    IStyle & GetFillStyle() override
    {
        return m_fillStyle;
    }

    const IStyle & GetFillStyle() const override
    {
        return m_fillStyle;
    }

    void Draw(gfx::ICanvas &canvas) const override
    {
        for (size_t i = 0; i < GetShapesCount(); ++i)
        {
            auto shape = GetShapeAtIndex(i);
            if (shape)
            {
                shape->Draw(canvas);
            }
        }
    }

    size_t GetShapesCount()const override
    {
        return m_shapes.size();
    }

    void InsertShape(const std::shared_ptr<IShape> & shape, size_t position = std::numeric_limits<size_t>::max()) override
    {
        m_shapes.insert({position, shape});
    }

    std::shared_ptr<IShape> GetShapeAtIndex(size_t index) const override
    {
        return m_shapes.at(index);
    }

    void RemoveShapeAtIndex(size_t index) override
    {
        auto it = m_shapes.find(index);
        if (it != m_shapes.end()) {
            m_shapes.erase(it);
        }
    }

private:
    std::unordered_map<size_t , std::shared_ptr<IShape>> m_shapes;
    Style m_outlineStyle;
    Style m_fillStyle;
};

#endif //LAB7_GROUPSHAPE_H
