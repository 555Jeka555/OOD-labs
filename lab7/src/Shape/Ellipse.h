#ifndef LAB7_ELLIPSE_H
#define LAB7_ELLIPSE_H

#include "IShape.h"
#include "Shape.h"

class Ellipse : public Shape
{
public:
    constexpr static std::string type = "ellipse";

    Ellipse(const RectD &frame,
            std::unique_ptr<IStyle> outlineStyle,
            std::unique_ptr<IStyle> fillStyle
    )
            : Shape(frame, std::move(outlineStyle), std::move(fillStyle))
    {
    }

    void Draw(gfx::ICanvas &canvas) const override
    {
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
            canvas.SetLineColor(0xFFFFFFFF);
        }

        auto frame = GetFrame();
        double cx = frame.left + frame.width / 2;
        const double cy = frame.top + frame.height / 2;
        const double rx = frame.width / 2;
        const double ry = frame.height / 2;
        canvas.DrawEllipse(cx, cy, rx, ry);

        canvas.EndFill();
    }
};

#endif //LAB7_ELLIPSE_H
