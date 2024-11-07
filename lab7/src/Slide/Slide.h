#ifndef LAB7_SLIDE_H
#define LAB7_SLIDE_H

#include "ISlide.h"
#include "../Shape/GroupShape.h"

class Slide : public ISlide {
public:
    explicit Slide(double width, double height, const std::shared_ptr<GroupShape> &shapes)
        :   m_background(0xFFFFFFFF),
            m_width(width),
            m_height(height),
            m_shapes(shapes)
    {
    }

    [[nodiscard]] double GetWidth() const override
    {
        return m_width;
    }

    [[nodiscard]] double GetHeight() const override
    {
        return m_height;
    }

    [[nodiscard]] IShapes &GetShapes() override
    {
        return *m_shapes;
    }

    [[nodiscard]] size_t GetShapesCount() const
    {
        return m_shapes->GetShapesCount();
    }

    std::shared_ptr<IShape> GetShapeAtIndex(size_t index)
    {
        return m_shapes->GetShapeAtIndex(index);
    }

    void RemoveShapeAtIndex(size_t index)
    {
        m_shapes->RemoveShapeAtIndex(index);
    }

    [[nodiscard]] RGBAColor GetBackgroundColor() const
    {
        return m_background;
    }

    void SetBackgroundColor(RGBAColor color)
    {
        m_background = color;
    }

    void Draw(gfx::ICanvas &canvas) const override
    {
        m_shapes->Draw(canvas);
    }

private:
    double m_width;
    double m_height;
    std::shared_ptr<GroupShape> m_shapes;
    RGBAColor m_background;
};

#endif //LAB7_SLIDE_H
