#ifndef LAB7_SLIDE_H
#define LAB7_SLIDE_H

#include "ISlide.h"
#include "../Shape/GroupShape.h"

class Slide : public ISlide {
public:
    explicit Slide(const std::shared_ptr<GroupShape> &shapes)
            : m_background(0xFFFFFFFF),
              m_shapes(shapes) {
    }

    double GetWidth() const override {
        return 800;
    }

    double GetHeight() const override {
        return 600;
    }

    [[nodiscard]] IShapes &GetShapes() override {
        return *m_shapes;
    }

    size_t GetShapesCount() const {
        return m_shapes->GetShapesCount();
    }

    std::shared_ptr<IShape> GetShapeAtIndex(size_t index) {
        return m_shapes->GetShapeAtIndex(index);
    }

    void RemoveShapeAtIndex(size_t index) {
        m_shapes->RemoveShapeAtIndex(index);
    }

    RGBAColor GetBackgroundColor() const {
        return m_background;
    }

    void SetBackgroundColor(RGBAColor color) {
        m_background = color;
    }

    void Draw(gfx::ICanvas &canvas) const override {
        m_shapes->Draw(canvas);
    }

private:
    std::shared_ptr<GroupShape> m_shapes;
    RGBAColor m_background;
};

#endif //LAB7_SLIDE_H
