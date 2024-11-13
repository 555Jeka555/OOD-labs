#ifndef LAB7_GROUPSHAPE_H
#define LAB7_GROUPSHAPE_H

#include <map>
#include "IGroupShape.h"
#include "Style/Style.h"
#include "Style/GroupStyle.h"

class GroupShape : public IGroupShape, public std::enable_shared_from_this<GroupShape>
{
public:
    constexpr static std::string typeStart = "group_start";
    constexpr static std::string typeEnd = "group_end";

    GroupShape()
    {

    }

    RectD GetFrame() const override
    {
        if (m_shapes.empty())
        {
            // TODO nullopt так как можно удалть из
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
        return *m_outlineStyle;
    }

    const IStyle & GetOutlineStyle() const override
    {
        return *m_outlineStyle;
    }

    IStyle & GetFillStyle() override
    {
        return *m_fillStyle;
    }

    const IStyle & GetFillStyle() const override
    {
        return *m_fillStyle;
    }

    void Draw(gfx::ICanvas &canvas) const override
    {
        for (const auto &pair: m_shapes)
        {
            if (pair.second)
            {
                pair.second->Draw(canvas);
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
        m_fillStyle->InsertStyle(shape->GetFillStyle(), position);
        m_outlineStyle->InsertStyle(shape->GetOutlineStyle(), position);
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
            m_fillStyle->RemoveStyleAtIndex(index);
            m_outlineStyle->RemoveStyleAtIndex(index);
        }
    }

    std::shared_ptr<IGroupShape> GetGroup() override
    {
        return shared_from_this();
    }

    std::shared_ptr<const IGroupShape> GetGroup() const override
    {
        return shared_from_this();
    }

private:
    std::map<size_t, std::shared_ptr<IShape>> m_shapes;
    std::unique_ptr<IGroupStyle> m_outlineStyle = std::make_unique<GroupStyle>();
    std::unique_ptr<IGroupStyle> m_fillStyle = std::make_unique<GroupStyle>();
};

#endif //LAB7_GROUPSHAPE_H
