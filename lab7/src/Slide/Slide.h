#ifndef LAB7_SLIDE_H
#define LAB7_SLIDE_H

#include "ISlide.h"
#include "../Shape/GroupShape.h"

class Slide : public ISlide {
public:
    Slide(double width, double height, const std::shared_ptr<GroupShape> &shapes)
            : m_width(width),
              m_height(height),
              m_shapes(shapes) {
    }

    [[nodiscard]] double GetWidth() const override {
        return m_width;
    }

    [[nodiscard]] double GetHeight() const override {
        return m_height;
    }

    [[nodiscard]] IShapes &GetShapes() override {
        return *m_shapes;
    }

    void Draw(gfx::ICanvas &canvas) const override {
        m_shapes->Draw(canvas);
    }

private:
    double m_width;
    double m_height;
    std::shared_ptr<GroupShape> m_shapes;
};

#endif //LAB7_SLIDE_H
