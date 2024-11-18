#ifndef LAB7_GROUPSHAPE_H
#define LAB7_GROUPSHAPE_H

#include <map>
#include "Style/Style.h"
#include "Style/GroupStyle.h"
#include "IShape.h"

class GroupShape : public IGroupShape, public std::enable_shared_from_this<GroupShape>
{
public:
    constexpr static std::string typeStart = "group_start";
    constexpr static std::string typeEnd = "group_end";

    GroupShape()
    {

    }

    [[nodiscard]] std::optional<RectD> GetFrame() const override
    {
        if (m_shapes.empty())
        {
            // TODO nullopt так как можно удалть из
            return std::nullopt; //  std::optional<RectD>({0, 0, 0, 0});
        }

        double left = std::numeric_limits<double>::max();
        double top = std::numeric_limits<double>::max();
        double right = std::numeric_limits<double>::lowest();
        double bottom = std::numeric_limits<double>::lowest();

        for (const auto &pair: m_shapes)
        {
            std::optional<RectD> frame = pair.second->GetFrame();
            if (frame == std::nullopt)
            {
                continue;
            }

            left = std::min(left, frame.value().left);
            top = std::min(top, frame.value().top);
            right = std::max(right, frame.value().left + frame.value().width);
            bottom = std::max(bottom, frame.value().top + frame.value().height);
        }

        return std::optional<RectD>({left, top, right - left, bottom - top});
    }

    void SetFrame(const std::optional<RectD> & rect) override  // пусть не опшион
    {
        if (rect == std::nullopt)
        {
            return;
        }

        auto [left, top, width, height] = GetFrame().value();
        const double scaleX = rect.value().width / width;
        const double scaleY = rect.value().height / height;

        for (const auto &pair: m_shapes)
        {
            std::optional<RectD> shapeFrame = pair.second->GetFrame();
            if (shapeFrame == std::nullopt)
            {
                continue;
            }

            const double newLeft = rect.value().left + (shapeFrame.value().left - left) * scaleX;
            const double newTop = rect.value().top + (shapeFrame.value().top - top) * scaleY;
            const double newWidth = shapeFrame.value().width * scaleX;
            const double newHeight = shapeFrame.value().height * scaleY;
            pair.second->SetFrame(std::optional<RectD>({newLeft, newTop, newWidth, newHeight}));
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
