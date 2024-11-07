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
        return m_frame;
    }

    void SetFrame(const RectD & rect) override
    {
        m_frame = rect;
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
    }

private:
    std::unordered_map<size_t , std::shared_ptr<IShape>> m_shapes;
    RectD m_frame{};
    Style m_outlineStyle;
    Style m_fillStyle;
};

#endif //LAB7_GROUPSHAPE_H
