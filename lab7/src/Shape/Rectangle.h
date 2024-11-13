#ifndef LAB7_RECTANGLE_H
#define LAB7_RECTANGLE_H

#include "IShape.h"
#include "Shape.h"

class Rectangle : public Shape
{
public:
    constexpr static std::string type = "rectangle";

    Rectangle(
            const RectD &frame,
            std::unique_ptr<IStyle> outlineStyle,
            std::unique_ptr<IStyle> fillStyle
    ): Shape(frame, std::move(outlineStyle), std::move(fillStyle))
    {
    }

    void Draw(gfx::ICanvas &canvas) const final override {
        const IStyle &outlineStyle = GetOutlineStyle();
        const IStyle &fillStyle = GetFillStyle();

        if (fillStyle.IsEnabled() && fillStyle.GetColor().has_value())
        {
            canvas.BeginFill(fillStyle.GetColor().value());
        }

        if (outlineStyle.IsEnabled() && outlineStyle.GetColor().has_value())
        {
            canvas.SetLineColor(outlineStyle.GetColor().value());
        }
        else
        {
            canvas.SetLineColor({});
        }

        auto [left, top, width, height] = GetFrame().value();

        const std::vector<std::pair<double, double>> vertices = {
                {left, top},
                {left + width, top},
                {left + width, top + height},
                {left, top + height}
        };
        canvas.DrawPolygon(vertices);

        canvas.EndFill();
    }
};

#endif //LAB7_RECTANGLE_H
