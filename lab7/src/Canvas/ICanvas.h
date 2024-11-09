#ifndef INC_1_1_ICANVAS_H
#define INC_1_1_ICANVAS_H

#include <string>
#include <cstdint>

namespace gfx
{
    class ICanvas
    {
    public:
        // TODO убрать Setы
        virtual void SetLineColor(uint32_t color) = 0;

        virtual void BeginFill(uint32_t color) = 0;

        virtual void EndFill() = 0;

        virtual void DrawPolygon(const std::vector<std::pair<double, double>>& vertices) = 0;

        virtual void DrawEllipse(double cx, double cy, double rx, double ry) = 0;

        virtual ~ICanvas() = default;
    };
}

#endif //INC_1_1_ICANVAS_H